// Dr. Kaputa
// Rochester Institute of Technology

#define S_FUNCTION_NAME fileMex
#define S_FUNCTION_LEVEL 2
#include "simstruc.h"
#define ADDR_ARG   ssGetSFcnParam(S,0) 
#ifndef  MATLAB_MEX_FILE 
  #include <stdio.h>
#endif 

FILE *myFile00;
FILE *myFile01;
FILE *myFile02;
FILE *myFile03;
FILE *myFile04;
FILE *myFile05;
FILE *myFile06;
FILE *myFile07;
FILE *myFile08;
FILE *myFile09;
FILE *myFile10;
FILE *myFile11;
FILE *myFile12;
FILE *myFile13;
FILE *myFile14;
FILE *myFile15;
FILE *myFile16;
FILE *myFile17;
FILE *myFile18;
FILE *myFile19;
FILE *myFile20;
FILE *myFile21;
FILE *myFile22;
FILE *myFile23;
FILE *myFile24;
FILE *myFile25;
FILE *myFile26;
FILE *myFile27;
FILE *myFile28;
FILE *myFile29;
FILE *myFile30;
FILE *myFile31;
FILE *myFile32;
FILE *myFile33;
FILE *myFile34;
FILE *myFile35;
FILE *myFile36;
FILE *myFile37;
FILE *myFile38;
FILE *myFile39;
FILE *myFile40;

static void mdlInitializeSizes(SimStruct *S){
  //ssPrintf("mdlInitializeSizes\n");
  ssSetNumSFcnParams(S, 1);
  if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
    return; /* Parameter mismatch reported by the Simulink engine*/
  }

  if (!ssSetNumInputPorts(S, 1)) return;
  ssSetInputPortWidth(S, 0, 1); // channel
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortRequiredContiguous(S,0,1);
  if (!ssSetNumOutputPorts(S, 1)) return;
  ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
  
  ssSetNumSampleTimes(S, 1);

  /* Take care when specifying exception free code - see sfuntmpl.doc */
  ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
  
  #ifndef  MATLAB_MEX_FILE
    char name[26] = "/piShare/data/run/file_xx";
    int msb = 23;
    int lsb = 24;
    char number;
    number = (char)(mxGetPr(ADDR_ARG)[0]);

    switch (number){
      case 0:
        name[msb] = 48;
        name[lsb] = 48;
        myFile00=fopen(name,"wb");
        break;
      case 1:
        name[msb] = 48;
        name[lsb] = 49;
        myFile01=fopen(name,"wb");
        break;
      case 2:
        name[msb] = 48;
        name[lsb] = 50;
        myFile02=fopen(name,"wb");
        break;
      case 3:
        name[msb] = 48;
        name[lsb] = 51;
        myFile03=fopen(name,"wb");
        break;
      case 4:
        name[msb] = 48;
        name[lsb] = 52;
        myFile04=fopen(name,"wb");
        break;
      case 5:
        name[msb] = 48;
        name[lsb] = 53;
        myFile05=fopen(name,"wb");
        break;
      case 6:
        name[msb] = 48;
        name[lsb] = 54;
        myFile06=fopen(name,"wb");
        break;
      case 7:
        name[msb] = 48;
        name[lsb] = 55;
        myFile07=fopen(name,"wb");
        break;
      case 8:
        name[msb] = 48;
        name[lsb] = 56;
        myFile08=fopen(name,"wb");
        break;
      case 9:
        name[msb] = 48;
        name[lsb] = 57;
        myFile09=fopen(name,"wb");
        break;
      case 10:
        name[msb] = 49;
        name[lsb] = 48;
        myFile10=fopen(name,"wb");
        break;
      case 11:
        name[msb] = 49;
        name[lsb] = 49;
        myFile11=fopen(name,"wb");
        break;
      case 12:
        name[msb] = 49;
        name[lsb] = 50;
        myFile12=fopen(name,"wb");
        break;
      case 13:
        name[msb] = 49;
        name[lsb] = 51;
        myFile13=fopen(name,"wb");
        break;
      case 14:
        name[msb] = 49;
        name[lsb] = 52;
        myFile14=fopen(name,"wb");
        break;
      case 15:
        name[msb] = 49;
        name[lsb] = 53;
        myFile15=fopen(name,"wb");
        break;
      case 16:
        name[msb] = 49;
        name[lsb] = 54;
        myFile16=fopen(name,"wb");
        break;
      case 17:
        name[msb] = 49;
        name[lsb] = 55;
        myFile17=fopen(name,"wb");
        break;
      case 18:
        name[msb] = 49;
        name[lsb] = 56;
        myFile18=fopen(name,"wb");
        break;
      case 19:
        name[msb] = 49;
        name[lsb] = 57;
        myFile19=fopen(name,"wb");
        break;
      case 20:
        name[msb] = 50;
        name[lsb] = 48;
        myFile20=fopen(name,"wb");
        break;
        
        
      case 21:
        name[msb] = 50;
        name[lsb] = 49;
        myFile21=fopen(name,"wb");
        break;
      case 22:
        name[msb] = 50;
        name[lsb] = 50;
        myFile22=fopen(name,"wb");
        break;
      case 23:
        name[msb] = 50;
        name[lsb] = 51;
        myFile23=fopen(name,"wb");
        break;
      case 24:
        name[msb] = 50;
        name[lsb] = 52;
        myFile24=fopen(name,"wb");
        break;
      case 25:
        name[msb] = 50;
        name[lsb] = 53;
        myFile25=fopen(name,"wb");
        break;
      case 26:
        name[msb] = 50;
        name[lsb] = 54;
        myFile26=fopen(name,"wb");
        break;
      case 27:
        name[msb] = 50;
        name[lsb] = 55;
        myFile27=fopen(name,"wb");
        break;
      case 28:
        name[msb] = 50;
        name[lsb] = 56;
        myFile28=fopen(name,"wb");
        break;
      case 29:
        name[msb] = 50;
        name[lsb] = 57;
        myFile29=fopen(name,"wb");
        break;
      case 30:
        name[msb] = 51;
        name[lsb] = 48;
        myFile30=fopen(name,"wb");
        break;
      case 31:
        name[msb] = 51;
        name[lsb] = 49;
        myFile31=fopen(name,"wb");
        break;
      case 32:
        name[msb] = 51;
        name[lsb] = 50;
        myFile32=fopen(name,"wb");
        break;
      case 33:
        name[msb] = 51;
        name[lsb] = 51;
        myFile33=fopen(name,"wb");
        break;
      case 34:
        name[msb] = 51;
        name[lsb] = 52;
        myFile34=fopen(name,"wb");
        break;
      case 35:
        name[msb] = 51;
        name[lsb] = 53;
        myFile35=fopen(name,"wb");
        break;
      case 36:
        name[msb] = 51;
        name[lsb] = 54;
        myFile36=fopen(name,"wb");
        break;
      case 37:
        name[msb] = 51;
        name[lsb] = 55;
        myFile37=fopen(name,"wb");
        break;
      case 38:
        name[msb] = 51;
        name[lsb] = 56;
        myFile38=fopen(name,"wb");
        break;
      case 39:
        name[msb] = 51;
        name[lsb] = 57;
        myFile39=fopen(name,"wb");
        break;
      case 40:
        name[msb] = 52;
        name[lsb] = 48;
        myFile40=fopen(name,"wb");
        break;
    }
  #endif 
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
  float value;
  int_T width = ssGetOutputPortWidth(S,0);

  u =  ssGetInputPortSignal(S,0);

  value = (float)u[0];
  
  #ifndef  MATLAB_MEX_FILE
    // running on HW
    char number;
    number = (char)(mxGetPr(ADDR_ARG)[0]);

    switch (number){
      case 0:
        fwrite(&value, sizeof(float), 1, myFile00);
        break;
      case 1:
        fwrite(&value, sizeof(float), 1, myFile01);
        break;
      case 2:
        fwrite(&value, sizeof(float), 1, myFile02);
        break;
      case 3:
        fwrite(&value, sizeof(float), 1, myFile03);
        break;
      case 4:
        fwrite(&value, sizeof(float), 1, myFile04);
        break;
      case 5:
        fwrite(&value, sizeof(float), 1, myFile05);
        break;
      case 6:
        fwrite(&value, sizeof(float), 1, myFile06);
        break;
      case 7:
        fwrite(&value, sizeof(float), 1, myFile07);
        break;
      case 8:
        fwrite(&value, sizeof(float), 1, myFile08);
        break;
      case 9:
        fwrite(&value, sizeof(float), 1, myFile09);
        break;
      case 10:
        fwrite(&value, sizeof(float), 1, myFile10);
        break;
      case 11:
        fwrite(&value, sizeof(float), 1, myFile11);
        break;
      case 12:
        fwrite(&value, sizeof(float), 1, myFile12);
        break;     
      case 13:
        fwrite(&value, sizeof(float), 1, myFile13);
        break;  
      case 14:
        fwrite(&value, sizeof(float), 1, myFile14);
        break;  
      case 15:
        fwrite(&value, sizeof(float), 1, myFile15);
        break;  
      case 16:
        fwrite(&value, sizeof(float), 1, myFile16);
        break;  
      case 17:
        fwrite(&value, sizeof(float), 1, myFile17);
        break;  
      case 18:
        fwrite(&value, sizeof(float), 1, myFile18);
        break;  
      case 19:
        fwrite(&value, sizeof(float), 1, myFile19);
        break;  
      case 20:
        fwrite(&value, sizeof(float), 1, myFile20);
        break;   
      case 21:
        fwrite(&value, sizeof(float), 1, myFile21);
        break;
      case 22:
        fwrite(&value, sizeof(float), 1, myFile22);
        break;
      case 23:
        fwrite(&value, sizeof(float), 1, myFile23);
        break;
      case 24:
        fwrite(&value, sizeof(float), 1, myFile24);
        break;
      case 25:
        fwrite(&value, sizeof(float), 1, myFile25);
        break;
      case 26:
        fwrite(&value, sizeof(float), 1, myFile26);
        break;
      case 27:
        fwrite(&value, sizeof(float), 1, myFile27);
        break;
      case 28:
        fwrite(&value, sizeof(float), 1, myFile28);
        break;
      case 29:
        fwrite(&value, sizeof(float), 1, myFile29);
        break;
      case 30:
        fwrite(&value, sizeof(float), 1, myFile30);
        break;
      case 31:
        fwrite(&value, sizeof(float), 1, myFile31);
        break;
      case 32:
        fwrite(&value, sizeof(float), 1, myFile32);
        break;     
      case 33:
        fwrite(&value, sizeof(float), 1, myFile33);
        break;  
      case 34:
        fwrite(&value, sizeof(float), 1, myFile34);
        break;  
      case 35:
        fwrite(&value, sizeof(float), 1, myFile35);
        break;  
      case 36:
        fwrite(&value, sizeof(float), 1, myFile36);
        break;  
      case 37:
        fwrite(&value, sizeof(float), 1, myFile37);
        break;  
      case 38:
        fwrite(&value, sizeof(float), 1, myFile38);
        break;  
      case 39:
        fwrite(&value, sizeof(float), 1, myFile39);
        break;  
      case 40:
        fwrite(&value, sizeof(float), 1, myFile40);
        break;         
    }

    *outputSiganl = u[0];
    //printf("linux\n");
  #else
    //ssPrintf("windows\n");
    *outputSiganl = u[0];
  #endif 
}

static void mdlTerminate(SimStruct *S){
  fclose(myFile00);
  fclose(myFile01);
  fclose(myFile02);
  fclose(myFile03);
  fclose(myFile04);
  fclose(myFile05);
  fclose(myFile06);
  fclose(myFile07);
  fclose(myFile08);
  fclose(myFile09);
  fclose(myFile10);
  fclose(myFile11);
  fclose(myFile12);
  fclose(myFile13);
  fclose(myFile14);
  fclose(myFile15);
  fclose(myFile16);
  fclose(myFile17);
  fclose(myFile18);
  fclose(myFile19);
  fclose(myFile20);
  fclose(myFile21);
  fclose(myFile22);
  fclose(myFile23);
  fclose(myFile24);
  fclose(myFile25);
  fclose(myFile26);
  fclose(myFile27);
  fclose(myFile28);
  fclose(myFile29);
  fclose(myFile30);
  fclose(myFile31);
  fclose(myFile32);
  fclose(myFile33);
  fclose(myFile34);
  fclose(myFile35);
  fclose(myFile36);
  fclose(myFile37);
  fclose(myFile38);
  fclose(myFile39);
  fclose(myFile40);
}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c" /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif