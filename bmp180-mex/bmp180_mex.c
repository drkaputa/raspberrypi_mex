// Dr. Kaputa
// Rochester Institute of Technology

#define S_FUNCTION_NAME bmp180_mex 
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
  #include "bmp180.c"
#endif 

void *bmp;

static void mdlInitializeSizes(SimStruct *S){
  #ifndef  MATLAB_MEX_FILE 
    char *i2c_device = "/dev/i2c-1";
    int address = 0x77;
    bmp = bmp180_init(address, i2c_device);
    bmp180_eprom_t eprom;
    bmp180_dump_eprom(bmp, &eprom);
    bmp180_set_oss(bmp, 3);   // this sets it to high accuracy mode
  #endif 
  //ssPrintf("mdlInitializeSizes\n");
  ssSetNumSFcnParams(S, 0);
  if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
      return; 
  }

  if (!ssSetNumInputPorts(S, 0)) return;
  if (!ssSetNumOutputPorts(S, 3)) return;
  ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 1, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 2, DYNAMICALLY_SIZED);

  ssSetNumSampleTimes(S, 1);

  /* Take care when specifying exception free code - see sfuntmpl.doc */
  ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S){
    ssSetSampleTime(S, 0, .1);
    ssSetOffsetTime(S, 0, 0.0);
}

static void mdlOutputs(SimStruct *S, int_T tid){
  //ssPrintf("mdlOutputs\n");
  real_T *temperature = ssGetOutputPortRealSignal(S,0);
  real_T *pressure = ssGetOutputPortRealSignal(S,1);
  real_T *altitude = ssGetOutputPortRealSignal(S,2);

  int_T width = ssGetOutputPortWidth(S,0);

  #ifndef  MATLAB_MEX_FILE 
    // running on HW
    //printf("linux\n");
    if(bmp != NULL){
      *temperature = (real_T)bmp180_temperature(bmp);
      *pressure = (real_T)bmp180_pressure(bmp);
      *altitude = (real_T)bmp180_altitude(bmp);
    }
  #else
    // running on pc
    //ssPrintf("windows\n");
    *temperature = 0;
    *pressure = 0;
    *altitude = 0;
  #endif 
}

static void mdlTerminate(SimStruct *S){
  #ifndef  MATLAB_MEX_FILE 
    bmp180_close(bmp);
  #endif 
}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c" /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif