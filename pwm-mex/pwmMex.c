// Dr. Kaputa
// Rochester Institute of Technology

#define S_FUNCTION_NAME pwmMex
#define S_FUNCTION_LEVEL 2
#include "simstruc.h"
#define ADDR_ARG   ssGetSFcnParam(S,0) 
#ifndef  MATLAB_MEX_FILE 
  #include <unistd.h>
  #include <math.h>
  #include <signal.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <fcntl.h>
  #include <string.h>
  #include <time.h>
  #include "linux/i2c-dev.h"
#endif 

#define PWM_ADDRESS           0x40

#define PCA9685_MODE1         0x0
#define PCA9685_PRESCALE      0xFE

#define LED0_ON_L             0xe
#define LED0_ON_H             0xf
#define LED0_OFF_L            0x10
#define LED0_OFF_H            0x11

#define LED1_ON_L             0x12
#define LED1_ON_H             0x13
#define LED1_OFF_L            0x14
#define LED1_OFF_H            0x15

#define LED15_ON_L             0x3a
#define LED15_ON_H             0x3b
#define LED15_OFF_L            0x3c
#define LED15_OFF_H            0x3d

#define LED14_ON_L             0x42
#define LED14_ON_H             0x43
#define LED14_OFF_L            0x44
#define LED14_OFF_H            0x45 


#ifndef  MATLAB_MEX_FILE 
int file;
char i2c_values[16];

void selectDevicePWM(int file, int addr){
  if (ioctl(file, I2C_SLAVE, addr) < 0) {
    printf("Failed to select I2C device.");
  }
}

void write8(char reg, char value){
  selectDevicePWM(file,PWM_ADDRESS);
  int result = i2c_smbus_write_byte_data(file, reg, value);
  if (result == -1){
    printf ("Failed to write byte to pwm chip.");
    exit(1);
  }
}

void write16(char reg, unsigned short value){
  selectDevicePWM(file,PWM_ADDRESS);
  int result;
  result = i2c_smbus_write_word_data(file, LED1_OFF_L, value);
  result = i2c_smbus_write_word_data(file, LED0_OFF_L, value);
  result = i2c_smbus_write_word_data(file, LED15_OFF_L, value);
  result = i2c_smbus_write_word_data(file, LED14_OFF_L, value);
  if (result == -1){
    printf ("Failed to write byte to pwm chip.");
    exit(1);
  }
}

void writeBlock(char reg, char *value){
  selectDevicePWM(file,PWM_ADDRESS);
  int result = i2c_smbus_write_block_data(file, reg, 16, value);
  if (result == -1){
    printf ("Failed to write byte to pwm chip.");
    exit(1);
  }
}

char read8(char reg){
  char data[1];
  selectDevicePWM(file,PWM_ADDRESS);
  int result = i2c_smbus_read_i2c_block_data(file, reg, 1, data);
  if (result != 1){
    printf("Failed to read byte from I2C.");
    exit(1);
  }
  return *data;
}

void reset(){
  write8(PCA9685_MODE1, 0x0); 
}

void setFrequency(float freq) {
  freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
  float prescaleval = 25000000;
  prescaleval /= 4096;
  prescaleval /= freq;
  prescaleval -= 1;

  char prescale = floor(prescaleval + 0.5);
  
  char oldmode = read8(PCA9685_MODE1);
  char newmode = (oldmode&0x7F) | 0x10; // sleep
  write8(PCA9685_MODE1, newmode); // go to sleep
  write8(PCA9685_PRESCALE, prescale); // set the prescaler
  write8(PCA9685_MODE1, oldmode);
  sleep(2);
  write8(PCA9685_MODE1, oldmode | 0xa1);  //  This sets the MODE1 register to turn on auto increment.
                                          // This is why the beginTransmission below was not working.
}

// for 200 Hz update
// 1 ms equates to 4096/5 ticks or 819 ticks split into two bytes.
// these bytes are 3 for high byte and 51 for low byte
// 2 ms equates to 4096/2.5 ticks or 1638 ticks split into two bytes.
// these bytes are 6 for high byte and 102 for low byte
void setPWM(char pin, real_T value){
  char high;
  char low;
  int iValue;
  
  // for 200 Hz
  // 4096 ticks per 5 ms so roughly 819 ticks per 1 ms.
  // 819 ticks divided by 100 for a 100 step resolution = 8 ticks per quanta
  // value of 0 = 1 ms [819]
  // value of 1 = 2 ms [1638]
  
  // for 100 Hz
  // 4096 ticks per 10 ms so roughly 410 ticks per 1 ms.
  // 410 ticks divided by 100 for a 100 step resolution = 4 ticks per quanta
  // value of 0 = 1 ms [410]
  // value of 1 = 2 ms [820]
  
  //iValue = (int)((value * 819 ) + 819);   200 hz
  iValue = (int)((value * 410 ) + 410); 
  
  high = iValue >> 8;
  if (iValue > 255){
    low = iValue - 256;
  }
  else{
    low = iValue;
  }
  
  if (pin == 1){
    write8(LED1_ON_L, 0);
    write8(LED1_ON_H, 0);
    write8(LED1_OFF_L, low);
    write8(LED1_OFF_H, high);
    //write16(LED1_OFF_L,(unsigned short)iValue);
    //writeBlock(LED0_ON_L,i2c_values);
  }
  else if (pin == 2){
    write8(LED0_ON_L, 0);
    write8(LED0_ON_H, 0);
    write8(LED0_OFF_L, low);
    write8(LED0_OFF_H, high);
    //write16(LED0_OFF_L,(unsigned short)iValue);
  }
  else if (pin == 3){
    write8(LED15_ON_L, 0);
    write8(LED15_ON_H, 0);
    write8(LED15_OFF_L, low);
    write8(LED15_OFF_H, high);  
    //write16(LED15_OFF_L,(unsigned short)iValue);
  }
  else if (pin == 4){
    write8(LED14_ON_L, 0);
    write8(LED14_ON_H, 0);
    write8(LED14_OFF_L, low);
    write8(LED14_OFF_H, high); 
    //write16(LED14_OFF_L,(unsigned short)iValue);
  }    
}

#endif

static void mdlInitializeSizes(SimStruct *S){
  #ifndef  MATLAB_MEX_FILE 
    int res, bus,  size;
    char *filename = "/dev/i2c-1";
    file = open(filename, O_RDWR);
    if (file<0) {
    ssPrintf("Unable to open I2C bus!");
      exit(1);
    }
  
    reset();
    setFrequency(100);  // period of 5 ms
    
    // basic initialization for PWM skew
    write8(LED1_ON_L, 0);
    write8(LED1_ON_H, 0);
    write8(LED0_ON_L, 0);
    write8(LED0_ON_H, 0);
    write8(LED15_ON_L, 0);
    write8(LED15_ON_H, 0);
    write8(LED14_ON_L, 0);
    write8(LED14_ON_H, 0);
  #endif 
  //ssPrintf("mdlInitializeSizes\n");
  ssSetNumSFcnParams(S, 1);
  if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
    return; /* Parameter mismatch reported by the Simulink engine*/
  }

  if (!ssSetNumInputPorts(S, 1)) return;
  ssSetInputPortWidth(S, 0, 1); // channel
  //ssSetInputPortWidth(S, 1, 1); // pwm
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortRequiredContiguous(S,0,1);
  if (!ssSetNumOutputPorts(S, 1)) return;
  ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
  
  ssSetNumSampleTimes(S, 1);

  /* Take care when specifying exception free code - see sfuntmpl.doc */
  ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S){
  //ssPrintf("mdlInitializeSampleTimes\n");
  //ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
  ssSetSampleTime(S, 0, .01);
  ssSetOffsetTime(S, 0, 0.0);
}

static void mdlOutputs(SimStruct *S, int_T tid){
  //ssPrintf("mdlOutputs\n");
  
  real_T *outputSiganl = ssGetOutputPortRealSignal(S,0);
  real_T const            *u;  
  
  int_T width = ssGetOutputPortWidth(S,0);

  u =  ssGetInputPortSignal(S,0);
  char            channel;
  channel = (char)(mxGetPr(ADDR_ARG)[0]);
  
  #ifndef  MATLAB_MEX_FILE 
    // running on HW
    setPWM(channel,u[0]);
    *outputSiganl = u[0];
    //printf("linux\n");
  #else
    //ssPrintf("windows\n");
    *outputSiganl = u[0];
  #endif 
}

static void mdlTerminate(SimStruct *S){
}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c" /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif