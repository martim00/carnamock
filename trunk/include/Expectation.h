#pragma once
#ifndef INCLUDED_EXPECTATION_H
#define INCLUDED_EXPECTATION_H

#include <vector>
#include <boost/shared_ptr.hpp>

#include "Matcher.h"

namespace carnamock {

   class Call;
   class ResultType;

   /**
   *  Represents an expectation of a method call. Knows how to compare him with a Call.
   *  @see Call
   */ 
   class Expectation
   {
   public:
      ~Expectation() {}

      /**
      *  Compares the Expectation with a call.
      *  @return ResultType* the comparation's result
      *  @param Call * call to compare
      */ 
      ResultType* Compare(Call* call);

      /**
      *  Adds a parameter matcher to this expectation.
      *  Must be in the order of method parameters
      *  @param IMatcher * matcher
      */ 
      void AddParamMatcher(IMatcher *matcher);

   private:
      std::vector<boost::shared_ptr<IMatcher> > paramsMatcher;
   };

} //namespace carnamock

#endif //INCLUDED_EXPECTATION_H