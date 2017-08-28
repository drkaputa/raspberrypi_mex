// Dr. Kaputa
// Rochester Institute of Technology

#define S_FUNCTION_NAME gpsMex 
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
  #include <gps.h>
  #include <math.h>
  
  int rc;
  struct timeval tv;
  struct gps_data_t gps_data_mex;
#endif 

static void mdlInitializeSizes(SimStruct *S){
  #ifndef  MATLAB_MEX_FILE 
    if ((rc = gps_open("localhost", "2947", &gps_data_mex)) == -1) {
      printf("code: %d, reason: %s\n", rc, gps_errstr(rc));
      return;
    }
    gps_stream(&gps_data_mex, WATCH_ENABLE | WATCH_JSON, NULL);
  #endif 
  //ssPrintf("mdlInitializeSizes\n");
  ssSetNumSFcnParams(S, 0);
  if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
      return; /* Parameter mismatch reported by the Simulink engine*/
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
    //ssPrintf("mdlInitializeSampleTimes\n");
    //ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetSampleTime(S, 0, .2);
    ssSetOffsetTime(S, 0, 0.0);
}

static void mdlOutputs(SimStruct *S, int_T tid){
  //ssPrintf("mdlOutputs\n");
  real_T *lat = ssGetOutputPortRealSignal(S,0);
  real_T *lon = ssGetOutputPortRealSignal(S,1);
  real_T *altitude = ssGetOutputPortRealSignal(S,2);

  #ifndef  MATLAB_MEX_FILE 
    // running on HW
    //printf("linux\n");
    
    if ((rc = gps_read(&gps_data_mex)) == -1) {
      printf("error occured reading gps data. code: %d, reason: %s\n", rc, gps_errstr(rc));
      } else {
        /* Display data from the GPS receiver. */
        if ((gps_data_mex.status == STATUS_FIX) && 
          (gps_data_mex.fix.mode == MODE_2D || gps_data_mex.fix.mode == MODE_3D) &&
              !isnan(gps_data_mex.fix.latitude) && 
              !isnan(gps_data_mex.fix.longitude) &&
              !isnan(gps_data_mex.fix.altitude)) {
              //gettimeofday(&tv, NULL);
              //printf("latitude: %f, longitude: %f, speed: %f, timestamp: %ld\n", gps_data_mex.fix.latitude, gps_data_mex.fix.longitude, gps_data_mex.fix.speed, tv.tv_sec);
              *lat = (real_T)gps_data_mex.fix.latitude;
              *lon = (real_T)gps_data_mex.fix.longitude;
              *altitude = (real_T)gps_data_mex.fix.altitude;
        } else {
          //printf("no GPS data available\n");
          *lat = (real_T)0;
          *lon = (real_T)0;
          *altitude = (real_T)0;
        }
      }
  #else
    // running on pc
    //ssPrintf("windows\n");
    *lat = 0;
    *lon = 0;
    *altitude = 0;
  #endif 
}

static void mdlTerminate(SimStruct *S){
  #ifndef  MATLAB_MEX_FILE 
    gps_stream(&gps_data_mex, WATCH_DISABLE, NULL);
    gps_close (&gps_data_mex);
  #endif 
}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c" /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif