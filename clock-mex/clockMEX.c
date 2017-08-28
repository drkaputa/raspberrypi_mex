// Dr. Kaputa
// Rochester Institute of Technology

#define S_FUNCTION_NAME clockMEX
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
  #define BILLION 1E9
  
  clock_t t1;
  clock_t t2;
  double time1,time2;
  // second way to do it
  struct timespec requestStart, requestEnd;
#endif 

static void mdlInitializeSizes(SimStruct *S){
  #ifndef  MATLAB_MEX_FILE 

  #endif 
  //ssPrintf("mdlInitializeSizes\n");
  ssSetNumSFcnParams(S, 0);
  if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
      return; /* Parameter mismatch reported by the Simulink engine*/
  }

  if (!ssSetNumInputPorts(S, 0)) return;
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

  real_T *updateRate = ssGetOutputPortRealSignal(S,0);;
  #ifndef  MATLAB_MEX_FILE 
    // running on HW
    //printf("linux\n");
    t2 = t1;
    t1 = clock();

    time2 = time1;
    
    clock_gettime(CLOCK_REALTIME, &requestStart);
    time1 = (real_T)(requestStart.tv_sec + (requestStart.tv_nsec/ BILLION));
    *updateRate = time1 - time2;
 
  #else
    // running on pc
    //ssPrintf("windows\n");
    *updateRate = 0;
  #endif 
}

static void mdlTerminate(SimStruct *S){

}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c" /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif