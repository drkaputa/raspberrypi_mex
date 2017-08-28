// Dr. Kaputa
// Rochester Institute of Technology

#define S_FUNCTION_NAME berryMex 
#define S_FUNCTION_LEVEL 2
#include "simstruc.h"
#ifndef  MATLAB_MEX_FILE 
  #include <unistd.h>
  #include <math.h>
  #include <signal.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <fcntl.h>
  #include <string.h>
  #include <time.h>
  #include "sensor.c"
#endif 

int  accRaw[3];
int  gyrRaw[3];
int  magRaw[3];

static void mdlInitializeSizes(SimStruct *S){
  #ifndef  MATLAB_MEX_FILE 
    enableIMU();
  #endif 
  //ssPrintf("mdlInitializeSizes\n");
  ssSetNumSFcnParams(S, 0);
  if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
      return; /* Parameter mismatch reported by the Simulink engine*/
  }

  if (!ssSetNumInputPorts(S, 0)) return;
  if (!ssSetNumOutputPorts(S, 9)) return;
  ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 1, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 2, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 3, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 4, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 5, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 6, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 7, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 8, DYNAMICALLY_SIZED);

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
  real_T *xAccel = ssGetOutputPortRealSignal(S,0);
  real_T *yAccel = ssGetOutputPortRealSignal(S,1);
  real_T *zAccel = ssGetOutputPortRealSignal(S,2);
  real_T *xGyro = ssGetOutputPortRealSignal(S,3);
  real_T *yGyro = ssGetOutputPortRealSignal(S,4);
  real_T *zGyro = ssGetOutputPortRealSignal(S,5);
  real_T *mag1 = ssGetOutputPortRealSignal(S,6);
  real_T *mag2 = ssGetOutputPortRealSignal(S,7);
  real_T *mag3 = ssGetOutputPortRealSignal(S,8);
  
  int_T width = ssGetOutputPortWidth(S,0);

  #ifndef  MATLAB_MEX_FILE 
    // running on HW
    //printf("linux\n");
    readACC(accRaw);
    readGYR(gyrRaw);
    readMAG(magRaw);
    
    // accel is +- 6 G for 16 bit
    *xAccel = 0.00018310546875 * (real_T)accRaw[0];
    *yAccel = 0.00018310546875 * (real_T)accRaw[1];
    *zAccel = 0.00018310546875 * (real_T)accRaw[2];
    
    // gyro is +- 2000 deg/sec for 16 bit.  
    *xGyro = 0.06103515625 * (real_T)gyrRaw[0];
    *yGyro = 0.06103515625 * (real_T)gyrRaw[1];
    *zGyro = 0.06103515625 * (real_T)gyrRaw[2];
    
    // mag is +- 12 gauss for 16 bit
    *mag1 = 0.0003662109375 * (real_T)magRaw[0];
    *mag2 = 0.0003662109375 * (real_T)magRaw[1];
    *mag3 = 0.0003662109375 * (real_T)magRaw[2];
    
  #else
    // running on pc
    //ssPrintf("windows\n");
    *xAccel = 0;
    *yAccel = 0;
    *zAccel = 0;
    *xGyro = 0;
    *yGyro = 0;
    *zGyro = 0;
    *mag1 = 0;
    *mag2 = 0;
    *mag3 = 0;
  #endif 
}

static void mdlTerminate(SimStruct *S){
 /*  fclose(imuFile); */
}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c" /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif