/** FIFO worklist -*- C++ -*-
 * @file
 * @section License
 *
 * Galois, a framework to exploit amorphous data-parallelism in irregular
 * programs.
 *
 * Copyright (C) 2013, The University of Texas at Austin. All rights reserved.
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
#ifndef GALOIS_WORKLIST_GLOBPQ_H
#define GALOIS_WORKLIST_GLOBPQ_H

#include "WLCompileCheck.h"


#ifdef GALOIS_USE_PAPI
#include "Galois/Runtime/Sampling.h"
extern "C" {
#include "/home/syesil2/tools/papi-5.6.0/include/papi.h"
#include "/home/syesil2/tools/papi-5.6.0/include/papiStdEventDefs.h"


}
#endif

namespace Galois {
namespace WorkList {

template<typename T = int, class PQT = LockFreeSkipList<DummyComparer<int>,int>, bool Concurrent = true>
//template<typename T, class PQT = LockFreeSkipList<DummyComparer<T>,T>, bool Concurrent = true>
struct GlobPQ : private boost::noncopyable {
  template<bool _concurrent>
  struct rethread { typedef GlobPQ<T, PQT, _concurrent> type; };

  template<typename _T>
  struct retype { typedef GlobPQ<_T, PQT, Concurrent> type; };

private:
  PQT pq; // tentative vertices


  // random number generation
  Runtime::PerThreadStorage<uint32_t> enqState;
  Runtime::PerThreadStorage<uint32_t> deqState;

  inline uint32_t xorshift32(uint32_t * state){
    uint32_t x = (*state);
    x ^= x << 13;
	  x ^= x >> 17;
	  x ^= x << 5; // see note below about this being a typo in Marsaglia
	  (*state) = x;
    return x;
  }

public:
  typedef T value_type;

#ifdef GALOIS_USE_PAPI
  static Galois::Statistic* enqEvent1;
  static Galois::Statistic* enqEvent2;
  static Galois::Statistic* enqEventNum1;
  static Galois::Statistic* enqEventNum2;

  static Galois::Statistic* deqEvent1;
  static Galois::Statistic* deqEvent2;
  static Galois::Statistic* deqEventNum1;
  static Galois::Statistic* deqEventNum2;


#if (NUM_EVENTS >2 )
  static Galois::Statistic* enqEvent3;
  static Galois::Statistic* deqEvent3;
  static Galois::Statistic* enqEventNum3;
  static Galois::Statistic* deqEventNum3;
#endif 
#if (NUM_EVENTS >3 )
  static Galois::Statistic* enqEvent4;
  static Galois::Statistic* deqEvent4;
  static Galois::Statistic* enqEventNum4;
  static Galois::Statistic* deqEventNum4;
#endif

#endif

  GlobPQ(){
    #ifdef GALOIS_USE_PAPI
    if(enqEvent1 == 0){
      std::string s = papiNames[0];
      std::string name = s+ "_enq";
      enqEvent1 = new Galois::Statistic(name);
      (*enqEvent1 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
    if(enqEvent2 == 0){
      std::string s = papiNames[1];
      std::string name = s+ "_enq";
      enqEvent2 = new Galois::Statistic(name);
      (*enqEvent2 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
    if(enqEventNum1 == 0){
      std::string s = papiNames[0];
      std::string name = s+ "_enq_num";
      enqEventNum1 = new Galois::Statistic(name);
      (*enqEventNum1 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
    if(enqEventNum2 == 0){
      std::string s = papiNames[1];
      std::string name = s+ "_enq_num";
      enqEventNum2 = new Galois::Statistic(name);
      (*enqEventNum2 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }

    if(deqEvent1 == 0){
      std::string s = papiNames[0];
      std::string name = s+ "_deq";
      deqEvent1 = new Galois::Statistic(name);
      (*deqEvent1 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
    if(deqEvent2 == 0){
      std::string s = papiNames[1];
      std::string name = s+ "_deq";
      deqEvent2 = new Galois::Statistic(name);
      (*deqEvent2 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
    if(deqEventNum1 == 0){
      std::string s = papiNames[0];
      std::string name = s+ "_deq_num";
      deqEventNum1 = new Galois::Statistic(name);
      (*deqEventNum1 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
    if(deqEventNum2 == 0){
      std::string s = papiNames[1];
      std::string name = s+ "_deq_num";
      deqEventNum2 = new Galois::Statistic(name);
      (*deqEventNum2 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
    

#if (NUM_EVENTS > 2)
    if(enqEvent3 == 0){
      std::string s = papiNames[2];
      std::string name = s+ "_enq";
      enqEvent3 = new Galois::Statistic(name);
      (*enqEvent3 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
    if(deqEvent3 == 0){
      std::string s = papiNames[2];
      std::string name = s+ "_deq";
      deqEvent3 = new Galois::Statistic(name);
      (*deqEvent3 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
    if(enqEventNum3 == 0){
      std::string s = papiNames[2];
      std::string name = s+ "_enq_num";
      enqEventNum3 = new Galois::Statistic(name);
      (*enqEventNum3 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
    if(deqEventNum3 == 0){
      std::string s = papiNames[2];
      std::string name = s+ "_deq_num";
      deqEventNum3 = new Galois::Statistic(name);
      (*deqEventNum3 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
#endif
    
#if (NUM_EVENTS>3)
    if(enqEvent4 == 0){
      std::string s = papiNames[3];
      std::string name = s+ "_enq";
      enqEvent4 = new Galois::Statistic(name);
      (*enqEvent4 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
    if(deqEvent4 == 0){
      std::string s = papiNames[3];
      std::string name = s+ "_deq";
      deqEvent4 = new Galois::Statistic(name);
      (*deqEvent4 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
    if(enqEventNum4 == 0){
      std::string s = papiNames[3];
      std::string name = s+ "_enq_num";
      enqEventNum4 = new Galois::Statistic(name);
      (*enqEventNum4 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
    if(deqEventNum4 == 0){
      std::string s = papiNames[3];
      std::string name = s+ "_deq_num";
      deqEventNum4 = new Galois::Statistic(name);
      (*deqEventNum4 )=0;
      // std::cout<<"Number of Pris statistics created\n";
    }
#endif    
#endif
  }

  ~GlobPQ(){
#ifdef GALOIS_USE_PAPI
    if(enqEvent1 != 0){
      delete enqEvent1 ;
     
    }
    if(enqEvent2 != 0){
      delete enqEvent2 ;
    }
    if(enqEventNum1 != 0){
      delete enqEventNum1 ;
    }
    if(enqEventNum2 != 0){
      delete enqEventNum2 ;
    }

    if(deqEvent1 != 0){
      delete deqEvent1 ;
    }
    if(deqEvent2 != 0){
      delete deqEvent2 ;
    }
    if(deqEventNum1 != 0){
      delete deqEventNum1 ;
    }
    if(deqEventNum2 != 0){
      delete deqEventNum2 ;
    }
    

#if (NUM_EVENTS > 2)
    if(enqEvent3 != 0){
      delete enqEvent3 ;
    }
    if(deqEvent3 != 0){
      delete deqEvent3 ;
    }
    if(enqEventNum3 != 0){
      delete enqEventNum3 ;
    }
    if(deqEventNum3 != 0){
      delete deqEventNum3 ;
    }
#endif
#if (NUM_EVENTS > 3)    
    if(enqEvent4 != 0){
      delete enqEvent4 ;
    }
    if(deqEvent4 != 0){
      delete deqEvent4 ;
    }
    if(enqEventNum4 != 0){
      delete enqEventNum4 ;
    }
    if(deqEventNum4 != 0){
      delete deqEventNum4 ;
    }
#endif    
#endif
  }

  void push(const value_type& val) {
 #ifdef GALOIS_USE_PAPI
    long_long values1[NUM_EVENTS];
    long_long values2[NUM_EVENTS];
    int num_counters=NUM_EVENTS;
    int a;
    unsigned int rand_num = xorshift32(enqState.getLocal())%DIVIDER;
    if( rand_num == 0 ){
    // if( papi::isEventSetInit ){
          // std::cout<<"-- "<<papi::isEventSetInit<<std::endl;

      a = PAPI_read(papiEventSet, values1);
      if( a != PAPI_OK){
        
        std::cout<<"error "<<PAPI_strerror(a)<<std::endl;
      }
    }
    // }
  #endif
    pq.push(val);
#ifdef GALOIS_USE_PAPI
    // if( papi::isEventSetInit ){
    if( rand_num == 0){
      a = PAPI_read(papiEventSet, values2);
      if( a != PAPI_OK){
        
        std::cout<<"error "<<PAPI_strerror(a)<<std::endl;
      }
      if(values1[0]<values2[0]){
        // assert((*enqEvent1)<=(*enqEvent1)+(values2[0]-values1[0]));

        (*enqEventNum1)+=1;
        (*enqEvent1) += (values2[0]-values1[0]);
      }
      if(values1[1]<values2[1]){
        // assert((*enqEvent2)<=(*enqEvent2)+(values2[1]-values1[1]));

        (*enqEventNum2)+=1;
        (*enqEvent2) += (values2[1]-values1[1]);
      }
    }
#if (NUM_EVENTS>2)
    if(values1[2]<values2[2]){
      // assert((*deqEvent1)<=(*deqEvent1)+(values2[0]-values1[0]));
      (*enqEventNum3)+=1;
      (*enqEvent3) += (values2[2]-values1[2]);
    }
#endif
#if (NUM_EVENTS>3)
    if(values1[3]<values2[3]){
      // assert((*deqEvent1)<=(*deqEvent1)+(values2[0]-values1[0]));
      (*enqEventNum4)+=1;
      (*enqEvent4) += (values2[3]-values1[3]);
    }
#endif
#endif
  }

  template<typename Iter>
  unsigned int push(Iter b, Iter e) {

    int npush;
    for (npush = 0; b != e; npush++)
      push(*b++);
    return npush;
  }

  template<typename RangeTy>
  unsigned int push_initial(const RangeTy& range) {
    auto rp = range.local_pair();
    return push(rp.first, rp.second);
  }

  Galois::optional<value_type> pop() {
#ifdef GALOIS_USE_PAPI

    long_long values1[NUM_EVENTS];
    long_long values2[NUM_EVENTS];
    int num_counters=NUM_EVENTS;
    int a;
    unsigned int rand_num = xorshift32(deqState.getLocal())%DIVIDER;
    if( rand_num == 0 ){
    // if( papi::isEventSetInit ){
          // std::cout<<"-- "<<papi::isEventSetInit<<std::endl;

      a = PAPI_read(papiEventSet, values1);
      if( a != PAPI_OK){
        
        std::cout<<"error "<<PAPI_strerror(a)<<std::endl;
      }
    }
    // }
  #endif
    Galois::optional<value_type> retval;
    value_type r;

    if (pq.try_pop(r))
      retval = r;
#ifdef GALOIS_USE_PAPI
    // if( papi::isEventSetInit ){
  if( rand_num == 0){
    a = PAPI_read(papiEventSet, values2);
    if( a != PAPI_OK){
      
      std::cout<<"error "<<PAPI_strerror(a)<<std::endl;
    }
    if(values1[0]<values2[0]){
      // assert((*deqEvent1)<=(*deqEvent1)+(values2[0]-values1[0]));
      (*deqEventNum1)+=1;
      (*deqEvent1) += (values2[0]-values1[0]);
    }
    if(values1[1]<values2[1]){
      // assert((*deqEvent2)<=(*deqEvent2)+(values2[1]-values1[1]));
      (*deqEventNum2)+=1;
      (*deqEvent2) += (values2[1]-values1[1]);
    }
  }
#if (NUM_EVENTS>2)
    if(values1[2]<values2[2]){
      // assert((*deqEvent1)<=(*deqEvent1)+(values2[0]-values1[0]));
      (*deqEventNum3)+=1;
      (*deqEvent3) += (values2[2]-values1[2]);
    }
#endif
#if (NUM_EVENTS>3)
    if(values1[3]<values2[3]){
      // assert((*deqEvent1)<=(*deqEvent1)+(values2[0]-values1[0]));
      (*deqEventNum4)+=1;
      (*deqEvent4) += (values2[3]-values1[3]);
    }
#endif
    // }
#endif
    return retval;
  }
};
GALOIS_WLCOMPILECHECK(GlobPQ)

#ifdef GALOIS_USE_PAPI
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::enqEvent1;
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::enqEvent2;
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::enqEventNum1;
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::enqEventNum2;
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::deqEvent1;
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::deqEvent2;
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::deqEventNum1;
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::deqEventNum2;



#if (NUM_EVENTS > 2)
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::enqEvent3;
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::deqEvent3;
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::enqEventNum3;
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::deqEventNum3;

#endif

#if (NUM_EVENTS>3)
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::enqEvent4;
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::deqEvent4;
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::enqEventNum4;
template<typename T , class PQT , bool Concurrent >
Statistic* GlobPQ<T, PQT, Concurrent>::deqEventNum4;
#endif
#endif

} // end namespace WorkList
} // end namespace Galois

#endif
