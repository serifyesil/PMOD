/** OneInputGate implements the basic structure of a one input logic gate -*- C++ -*-
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
 * @author M. Amber Hassaan <ahassaan@ices.utexas.edu>
 */

#ifndef DES_BASE_ONE_INPUT_GATE_H_
#define DES_BASE_ONE_INPUT_GATE_H_

#include <string>
#include <sstream>

#include "comDefs.h"
#include "logicDefs.h"
#include "LogicFunctions.h"
#include "LogicGate.h"


namespace des {

struct OneInputGateTraits {
  static const size_t  N_OUT = 1;
  static const size_t  N_IN  = 1;
};

class OneInputGate: public BaseLogicGate<OneInputGateTraits::N_OUT, OneInputGateTraits::N_IN> {
private:
  typedef BaseLogicGate<OneInputGateTraits::N_OUT, OneInputGateTraits::N_IN> SuperTy;

protected:
  /**
   * a functor which computes an output LogicVal when
   * provided an input LogicVal
   */
  const OneInputFunc& func;

  /** The input name. */
  std::string inputName;

  /** The input val. */
  LogicVal inputVal;

public:
  /**
   * Instantiates a new one input gate.
   */
  OneInputGate (const OneInputFunc& func, const std::string& outputName, const std::string& inputName, const SimTime& delay = MIN_DELAY)
    : SuperTy (outputName, LOGIC_ZERO, delay), func (func), inputName (inputName) , inputVal (LOGIC_ZERO) {}


  virtual OneInputGate* makeClone () const {
    return new OneInputGate (*this);
  }


  /**
   * Applies the update to internal state e.g. change to some input. Must update the output
   * if the inputs have changed.
   */
  virtual void applyUpdate (const LogicUpdate& lu) {
    if (hasInputName (lu.getNetName ())) {
      inputVal = lu.getNetVal ();
    } else {
      SuperTy::netNameMismatch (lu);
    }

    this->outputVal = evalOutput ();
  }

  /**
    * Evaluate output based on the current state of the input
    *
    * @return the
    */
   virtual LogicVal evalOutput () const { return func (inputVal); }

   /**
    * @param net: name of a wire
    * @return true if has an input with the name equal to 'net'
    */
   virtual bool hasInputName (const std::string& net) const { return (inputName == net); }

   /**
    * @param inputName net name
    * @return index of the input matching the net name provided
    */
   virtual size_t getInputIndex (const std::string& inputName) const {
     if (this->inputName == (inputName)) {
       return 0; // since there is only one input
     }
     abort ();
     return -1; // error

   }



  /**
   * @return string representation
   */
  virtual std::string str () const {
    std::ostringstream ss;

    ss << func.str () <<  " output: " << outputName << " = " << outputVal << ", input: " << inputName << " = " << inputVal;
    return ss.str ();
  }

  /**
   * Gets the input name.
   *
   * @return the input name
   */
  const std::string& getInputName () const {
    return inputName;
  }

  /**
   * Sets the input name.
   *
   * @param inputName the new input name
   */
  void setInputName (const std::string& inputName) {
    this->inputName = inputName;
  }

  /**
   * Gets the input val.
   *
   * @return the input val
   */
  const LogicVal& getInputVal () const {
    return inputVal;
  }

  /**
   * Sets the input val.
   *
   * @param inputVal the new input val
   */
  void setInputVal (const LogicVal& inputVal) {
    this->inputVal = inputVal;
  }

};


} // namespace des

#endif
