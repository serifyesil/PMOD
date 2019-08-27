/** HW Runtime Sampling Control -*- C++ -*-
 * @file
 * @section License
 *
 * Galois, a framework to exploit amorphous data-parallelism in irregular
 * programs.
 *
 * Copyright (C) 2011, The University of Texas at Austin. All rights reserved.
 * UNIVERSITY EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES CONCERNING THIS
 * SOFTWARE AND DOCUMENTATION, INCLUDING ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR ANY PARTICULAR PURPOSE, NON-INFRINGEMENT AND WARRANTIES OF
 * PERFORMANCE, AND ANY WARRANTY THAT MIGHT OTHERWISE ARISE FROM COURSE OF
 * DEALING OR USAGE OF TRADE.  NO WARRANTY IS EITHER EXPRESS OR IMPLIED WITH
 * RESPECT TO THE USE OF THE SOFTWARE OR DOCUMENTATION. Under no circumstances
 * shall University be liable for incidental, special, indirect, direct or
 * consequential damages or loss of profits, interruption of business, or
 * related expenses which may arise from use of Software or Documentation,
 * including but not limited to those resulting from defects in Software and/or
 * Documentation, or loss or inaccuracy of data of any kind.
 *
 * @author Andrew Lenharth <andrewl@lenharth.org>
 */
#ifndef GALOIS_RUNTIME_SAMPLING_H
#define GALOIS_RUNTIME_SAMPLING_H


#ifdef GALOIS_USE_PAPI
extern "C" {
#include "/home/syesil2/tools/papi-5.6.0/include/papi.h"
#include "/home/syesil2/tools/papi-5.6.0/include/papiStdEventDefs.h"
}
#include "SamplingCommon.h"
#include <stdlib.h>
#include <time.h>

#define RND_RANGE 1000000
#define RATIO 250000
#define DIVIDER 4


// namespace papi{
extern bool isInit;
extern bool isSampling;
extern __thread int papiEventSet ;

// #define NUM_EVENTS 2
// static int papiEvents[2] = {PAPI_L3_TCA,PAPI_L3_TCM};
// static const char* papiNames[2] = {"L3_ACCESSES","L3_MISSES"};


#ifdef LST_PROF
#define NUM_EVENTS 2
static int papiEvents[NUM_EVENTS] = {PAPI_TOT_INS, PAPI_LST_INS}; //PAPI_LST_INS
static const char* papiNames[NUM_EVENTS] = {"INS_COUNT",  "LST_INS"};//"LST_INS",
#endif
#ifdef L1D_PROF
#define NUM_EVENTS 2
static int papiEvents[NUM_EVENTS] = {PAPI_TOT_INS, PAPI_L1_DCM}; //PAPI_LST_INS
static const char* papiNames[NUM_EVENTS] = {"INS_COUNT",  "L1D_MISSES"};//"LST_INS",
#endif
#ifdef L1I_PROF
#define NUM_EVENTS 3
static int papiEvents[NUM_EVENTS] = {PAPI_TOT_INS, PAPI_L1_ICA, PAPI_L1_ICM};
static const char* papiNames[NUM_EVENTS] = {"INS_COUNT", "L1I_ACCESSES", "L1I_MISSES"};
#endif
#ifdef L2_PROF
#define NUM_EVENTS 3
static int papiEvents[NUM_EVENTS] = {PAPI_TOT_INS, PAPI_L2_TCM, PAPI_L2_TCA};
static const char* papiNames[NUM_EVENTS] = {"INS_COUNT", "L2_MISSES", "L2_ACCESSES"};
#endif
#ifdef L3_PROF
#define NUM_EVENTS 3
static int papiEvents[NUM_EVENTS] = {PAPI_TOT_INS, PAPI_L3_TCM, PAPI_L3_TCA};
static const char* papiNames[NUM_EVENTS] = {"INS_COUNT", "L3_MISSES", "L3_ACCESSES"};
#endif
// #define NUM_EVENTS 3
// static int papiEvents[NUM_EVENTS] = {PAPI_L1_ICA, PAPI_L2_TCM, PAPI_L3_TCM};
// static const char* papiNames[NUM_EVENTS] = {"L1_INS_ACCESS", "L2_MISSES","L3_MISSES"};

// #define NUM_EVENTS 2
// static int papiEvents[NUM_EVENTS] = {PAPI_L2_TCM, PAPI_L2_TCA};
// static const char* papiNames[NUM_EVENTS] = {"L2_MISSES", "L2_ACCESSES"};


// #define NUM_EVENTS 3
// static int papiEvents[NUM_EVENTS] = {PAPI_LST_INS, PAPI_L2_TCM, PAPI_L2_TCA};//PAPI_L1_ICA,
// static const char* papiNames[NUM_EVENTS] = {"LST_INS","L2_MISSES", "L2_ACCESSES"};//"L1_INS_ACCESS",

// #define NUM_EVENTS 2
// static int papiEvents[NUM_EVENTS] = {PAPI_L1_DCM, PAPI_LST_INS};
// static const char* papiNames[NUM_EVENTS] = {"L1D_MISSES", "LST_INS"};


// #define NUM_EVENTS 3
// static int papiEvents[NUM_EVENTS] = {PAPI_L1_ICA, PAPI_L2_TCM, PAPI_L3_TCM};
// static const char* papiNames[NUM_EVENTS] = {"L1_INS_ACCESS", "L2_MISSES","L3_MISSES"};

extern bool isEventSetInit;


// static int papiEvents[2] = {PAPI_TOT_INS, PAPI_TOT_CYC};
// static const char* papiNames[2] = {"Instructions", "Cycles"};

//static int papiEvents[2] = {PAPI_L1_DCM, PAPI_TOT_CYC};
//static const char* papiNames[2] = {"L1DCMCounter", "CyclesCounter"};
// }
#endif

namespace Galois {
namespace Runtime {

void beginSampling();
void endSampling();
void beginThreadSampling();
void endThreadSampling();

}
} // end namespace Galois

#endif
