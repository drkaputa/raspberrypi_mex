// Dr. Kaputa
// Rochester Institute of Technology

#define S_FUNCTION_NAME ds4Mex 
#define S_FUNCTION_LEVEL 2
#include "simstruc.h"
#ifndef  MATLAB_MEX_FILE 
  #include "SDL.h"
  #include "stdio.h"
#endif 

void* joy;

static void mdlInitializeSizes(SimStruct *S){
  #ifndef  MATLAB_MEX_FILE 
    SDL_Init(SDL_INIT_JOYSTICK);
    // 0 for ds4drv
    // 1 hidraw
    SDL_Joystick* joystick = SDL_JoystickOpen(0);
    joy = joystick;
  #endif 
  //ssPrintf("mdlInitializeSizes\n");
  ssSetNumSFcnParams(S, 0);
  if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
      return; /* Parameter mismatch reported by the Simulink engine*/
  }

  if (!ssSetNumInputPorts(S, 0)) return;
  if (!ssSetNumOutputPorts(S, 10)) return;
  ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 1, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 2, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 3, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 4, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 5, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 6, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 7, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 8, DYNAMICALLY_SIZED);
  ssSetOutputPortWidth(S, 9, DYNAMICALLY_SIZED);

  ssSetNumSampleTimes(S, 1);

  /* Take care when specifying exception free code - see sfuntmpl.doc */
  ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S){
  //ssPrintf("mdlInitializeSampleTimes\n");
  //ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
  ssSetSampleTime(S, 0, .01);  // 200 Hz
  ssSetOffsetTime(S, 0, 0.0);
}

static void mdlOutputs(SimStruct *S, int_T tid){
  //ssPrintf("mdlOutputs\n");
  real_T *throttle = ssGetOutputPortRealSignal(S,0);
  real_T *yaw = ssGetOutputPortRealSignal(S,1);
  real_T *pitch = ssGetOutputPortRealSignal(S,2);
  real_T *roll = ssGetOutputPortRealSignal(S,3);
  real_T *square = ssGetOutputPortRealSignal(S,4);
  real_T *ex = ssGetOutputPortRealSignal(S,5);
  real_T *circle = ssGetOutputPortRealSignal(S,6);
  real_T *triangle = ssGetOutputPortRealSignal(S,7);
  real_T *trigger = ssGetOutputPortRealSignal(S,8);
  real_T *mode = ssGetOutputPortRealSignal(S,9);
  
  int_T width = ssGetOutputPortWidth(S,0);

  #ifndef  MATLAB_MEX_FILE 
    // running on HW
    //printf("linux\n");
    // 1/32768 = 0..000030517578125
    // range is 0 to 1 as the lower max is set to 0.  Need to divide by an extra 2 and offset .5
    *throttle = (-0.0000152587890625 * SDL_JoystickGetAxis(joy, 1)) + .5;
    *yaw = 0.000030517578125 * SDL_JoystickGetAxis(joy, 0);
    *pitch = 0.000030517578125 * SDL_JoystickGetAxis(joy, 5);
    *roll = 0.000030517578125 * SDL_JoystickGetAxis(joy, 2);

    *trigger = SDL_JoystickGetButton(joy, 7);
    *mode = SDL_JoystickGetButton(joy, 6);
    *square = SDL_JoystickGetButton(joy, 0);
    *ex = SDL_JoystickGetButton(joy, 1);
    *circle = SDL_JoystickGetButton(joy, 2);
    *triangle = SDL_JoystickGetButton(joy, 3);
  
    SDL_JoystickUpdate();
  #else
    // running on PC
    //ssPrintf("windows\n");
    *throttle = 0;
    *yaw = 0;
    *pitch = 0;
    *roll = 0;
    *square = 0;
    *ex = 0;
    *circle = 0;
    *triangle = 0;
    *trigger = 0;
    *mode = 0;
  #endif 
}

static void mdlTerminate(SimStruct *S){
}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c" /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif