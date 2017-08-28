// Dr. Kaputa
// Rochester Institute of Technology

#define S_FUNCTION_NAME ultrasoundMex
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
  #include <pigpio.h>
#endif 

#ifndef  MATLAB_MEX_FILE 
real_T distance1 = 0;
real_T distance2 = 0;

void aFunction(int gpio, int level, uint32_t tick){
  static uint32_t risingTime;
  
  if (level == 1){
    risingTime = tick;
  }
  else{
    distance1 = (tick - risingTime) * .017150;
  }

  //printf("GPIO %d became %d at %d\n", gpio, level, distance1);
}

#endif 

static void mdlInitializeSizes(SimStruct *S){
  #ifndef  MATLAB_MEX_FILE 
    gpioInitialise();
    gpioSetMode(25, PI_OUTPUT);
    gpioSetMode(8, PI_INPUT);       
    gpioSetISRFunc(8,EITHER_EDGE,0,aFunction);
  #endif 
  //ssPrintf("mdlInitializeSizes\n");
  ssSetNumSFcnParams(S, 0);
  if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
    return; /* Parameter mismatch reported by the Simulink engine*/
  }

  if (!ssSetNumInputPorts(S, 0)) return;
  if (!ssSetNumOutputPorts(S, 2)) return;
  ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 1, DYNAMICALLY_SIZED);
  
  ssSetNumSampleTimes(S, 1);

  /* Take care when specifying exception free code - see sfuntmpl.doc */
  ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S){
  //ssPrintf("mdlInitializeSampleTimes\n");
  //ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
  ssSetSampleTime(S, 0, .05);
  ssSetOffsetTime(S, 0, 0.0);
}

static void mdlOutputs(SimStruct *S, int_T tid){
  //ssPrintf("mdlOutputs\n");
  
  real_T *outputSiganl1 = ssGetOutputPortRealSignal(S,0);
  real_T *outputSiganl2 = ssGetOutputPortRealSignal(S,1);

  #ifndef  MATLAB_MEX_FILE 
    // running on HW
    gpioTrigger(25,20,1);
    *outputSiganl1 = distance1;
    *outputSiganl2 = distance2;
    //printf("linux\n");
  #else
    //ssPrintf("windows\n");
    *outputSiganl1 = 0;
    *outputSiganl2 = 0;
  #endif 
}

static void mdlTerminate(SimStruct *S){
}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c" /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif