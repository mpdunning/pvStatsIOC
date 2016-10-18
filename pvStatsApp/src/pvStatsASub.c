 /* Collection of aSub subroutines...
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <dbDefs.h>
//#include <alarm.h>
#include <registryFunction.h>
//#include "subRecord.h"
#include "aSubRecord.h"
#include <epicsExport.h>
#include <math.h>
#include <stdlib.h>

//#define SIZE(x)               (sizeof(x)/sizeof(x[0]))
#define MINMAX_0 1000.0

//typedef unsigned char byte;
//typedef unsigned short word;
//typedef unsigned int uint;


static double average(int arrLen, double *arr);
static double stdev(int arrLen, double *arr, double ave);
static double stdevPercent(double ave, double std);


static long asStats(aSubRecord *pr){
/*------------------------------------------------------------------------------
 * Do some stats
 *----------------------------------------------------------------------------*/
    double *stats1=(double*)pr->a;
    int    *statsLen1=(int*)pr->b;
    double *stats2=(double*)pr->c;
    int    *statsLen2=(int*)pr->d;
    double *stats3=(double*)pr->e;
    int    *statsLen3=(int*)pr->f;
    double *stats4=(double*)pr->g;
    int    *statsLen4=(int*)pr->h;

    double *ave1=(double*)pr->vala;
    double *std1=(double*)pr->valb;
    double *stdPer1=(double*)pr->valc;
    double *ave2=(double*)pr->vald;
    double *std2=(double*)pr->vale;
    double *stdPer2=(double*)pr->valf;
    double *ave3=(double*)pr->valg;
    double *std3=(double*)pr->valh;
    double *stdPer3=(double*)pr->vali;
    double *ave4=(double*)pr->valj;
    double *std4=(double*)pr->valk;
    double *stdPer4=(double*)pr->vall;

    *ave1=average(*statsLen1,stats1);
    *std1=stdev(*statsLen1,stats1,*ave1);
    *stdPer1=stdevPercent(*ave1,*std1);

    *ave2=average(*statsLen2,stats2);
    *std2=stdev(*statsLen2,stats2,*ave2);
    *stdPer2=stdevPercent(*ave2,*std2);

    *ave3=average(*statsLen3,stats3);
    *std3=stdev(*statsLen3,stats3,*ave3);
    *stdPer3=stdevPercent(*ave3,*std3);

    *ave4=average(*statsLen4,stats4);
    *std4=stdev(*statsLen4,stats4,*ave4);
    *stdPer4=stdevPercent(*ave4,*std4);

//printf("ave1=%f, ave2=%f, ave3=%f\n",*ave1,*ave2,*ave3);
//printf("std1=%f, std2=%f, std3=%f\n",*std1,*std2,*std3);
//printf("stdPer1=%f, stdPer2=%f, stdPer3=%f\n\n",*stdPer1,*stdPer2,*stdPer3);

    return(0);
}

static long asScope(aSubRecord *pr){
/*------------------------------------------------------------------------------
 * Do some stats
 *----------------------------------------------------------------------------*/
    double *scopeWf=(double*)pr->a;
    //int    scopeWfLen=(int)pr->noa;
    double *scaleVert=(double*)pr->b;
    double *scaleHor=(double*)pr->c;
    double *posVert=(double*)pr->d;
    int    *lim1=(int*)pr->e;
    int    *lim2=(int*)pr->f;
    //double *scopeWfOffset=(double*)pr->g;
    double *vertOffset=(double*)pr->h;

    double *minVolts=(double*)pr->vala;
    double *maxVolts=(double*)pr->valb;
    double *meanVolts=(double*)pr->valc;
    double *integral=(double*)pr->vald;
    double *integralScaled=(double*)pr->vale;

    int i;
    double min=MINMAX_0,max=-MINMAX_0;
    *integral=0.0;
    for (i=*lim1-1; i<*lim2; ++i) {
        scopeWf[i]-=*posVert;
        //scopeWf[i]-=scopeWfOffset[i];
        scopeWf[i]-=(*vertOffset/(*scaleVert));
        scopeWf[i]*=(*scaleVert);
        *integral+=scopeWf[i];
        if (min > scopeWf[i]) min=scopeWf[i];
        if (max < scopeWf[i]) max=scopeWf[i];
    }
    *minVolts=(min);
    *maxVolts=(max);
    *meanVolts=(*lim1==*lim2)?0:(*integral/(abs((double)*lim1-(double)*lim2)));
    *integralScaled=*meanVolts*(*scaleHor);
    //printf("lim1=%d, lim2=%d, scaleHor=%f, posVert=%f\n", *lim1,*lim2,*scaleHor,*posVert);
    //printf("min=%f, max=%f, mean=%f\n", *minVolts,*maxVolts,*meanVolts);
    //printf("integral=%f, integralScaled=%f, meanVolts=%f\n", *integral,*integralScaled,*meanVolts);

    return(0);
}

/**************************************************************************/

static double average(int arrLen, double *arr) {
/* Function to find average */
    int i;
    double ave, sum=0.0;
    for (i=0; i<arrLen; ++i) {
        sum+=arr[i];
    }
    ave=sum/((double)arrLen);
    //printf("ave=%f\n", ave);
    return(ave);
}

static double stdev(int arrLen, double *arr, double ave) {
/* Function to find standard deviation */
    int i;
    double std, sumSq=0.0;
    for (i=0; i<arrLen; ++i) {
        sumSq+=(arr[i] - ave)*(arr[i] - ave);
    }
    std=sqrt(sumSq/((double)(arrLen)));
    //std=(arrLen==0)?0:(sqrt(sumSq/((double)(arrLen))));
    return(std);
}

static double stdevPercent(double ave, double std) {
/* Function to find percent standard deviation */
    double stdPer, delta=0.0001;
    //stdPer = (fabs(ave) > delta && fabs(std) < delta) ? (std/(ave))*100.0 : 0.0;
    stdPer = (fabs(ave) > delta) ? fabs(std/(ave))*100.0 : 0.0;
    return(stdPer);
}


/**************************************************************************/

epicsRegisterFunction(asStats);
epicsRegisterFunction(asScope);

