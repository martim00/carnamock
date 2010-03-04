#pragma once
#ifndef INCLUDED_CALLMATCHER_H
#define INCLUDED_CALLMATCHER_H

#include "NullType.h"
#include "Matcher.h"
#include <boost/shared_ptr.hpp>
#include "IRegistry.h"

#include <hamcrest/core/hc_matcher.h>

template <class ReturnType=nulltype
, class Param1=nulltype
, class Param2=nulltype
, class Param3= nulltype
, class Param4=nulltype
, class Param5=nulltype> 
class CallMatcher;

namespace carnamock {

//curiosly recurring template pattern
//need to make Ptr
template <class Derived>
class CallMatcherBase
{
public:
   typedef boost::shared_ptr<Derived> Ptr;
   CallMatcherBase(IRegistry &_registry) : registry(_registry) {}
   virtual ~CallMatcherBase() {}

   void Times(std::size_t times)
   {
      ICall *icall= NULL;
      for (unsigned i= 0; i < times; i++)    
         registry.AddExpectation(createCallExpectation_hc());
      
   }
   virtual Expectation *createCallExpectation_hc()= 0;   

protected:
   IRegistry &registry;
};


template <class ReturnType>
class CallMatcher<ReturnType> : public CallMatcherBase<CallMatcher<ReturnType> >
{
public:
	CallMatcher(IRegistry &_registry) 
      : CallMatcherBase<CallMatcher<ReturnType> >(_registry) {}

   Expectation *createCallExpectation_hc()
   {
      return new Expectation();
   } 
};

template <class ReturnType, class Param1>
class CallMatcher<ReturnType, Param1> : public CallMatcherBase<CallMatcher<ReturnType, Param1> >
{
public:
	CallMatcher(IRegistry &_registry) 
      : CallMatcherBase<CallMatcher<ReturnType, Param1> >(_registry), parameterWasSetted(false) {}


	Expectation *createCallExpectation_hc()
   {
		Expectation *exp= new Expectation();
		exp->AddParamMatcher(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(hc_matcher1));
		return exp;
   }

	CallMatcher &WithParams(hamcrest::matcher<Param1> &p1)
	{
		hc_matcher1= p1.copy();
		parameterWasSetted= true;
		return *this;
	}

private:
	bool parameterWasSetted;
	hamcrest::matcher<Param1> *hc_matcher1;
};

//2 arity

template <class ReturnType, class Param1, class Param2>
class CallMatcher<ReturnType, Param1, Param2> 
   : public CallMatcherBase<CallMatcher<ReturnType, Param1, Param2> >
{
public:
	CallMatcher(IRegistry &_registry) 
		: CallMatcherBase<CallMatcher<ReturnType, Param1, Param2> >(_registry)
      , parameterWasSetted(false) {}

   Expectation *createCallExpectation_hc()
   {
      Expectation *exp= new Expectation();
      exp->AddParamMatcher(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(hc_matcher1));
      exp->AddParamMatcher(new IMatcherWrapper<hamcrest::matcher<Param2>, Param2>(hc_matcher2));
      return exp;
   }

   CallMatcher &WithParams(hamcrest::matcher<Param1> &p1, hamcrest::matcher<Param2> &p2)
   {
      hc_matcher1= p1.copy();
      hc_matcher2= p2.copy();
      parameterWasSetted= true;
      return *this;
   }

private:
	bool parameterWasSetted;
   hamcrest::matcher<Param1> *hc_matcher1;
   hamcrest::matcher<Param2> *hc_matcher2;


};

//3 arity

template <class ReturnType, class Param1, class Param2, class Param3>
class CallMatcher<ReturnType, Param1, Param2, Param3> 
   : public CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3> >
{
public:
	CallMatcher(IRegistry &_registry) 
		: CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3> >(_registry)
      , parameterWasSetted(false) {}

   Expectation *createCallExpectation_hc()
   {
      Expectation *exp= new Expectation();
      exp->AddParamMatcher(matcher1);
      exp->AddParamMatcher(matcher2);
      exp->AddParamMatcher(matcher3);
      return exp;
   }

	CallMatcher &WithParams(hamcrest::matcher<Param1> &p1, hamcrest::matcher<Param2> &p2, hamcrest::matcher<Param3> &p3)
	{
		matcher1= p1.copy();
		matcher2= p2.copy();
		matcher3= p3.copy();
		parameterWasSetted= true;
		return *this;
	}

private:
	bool parameterWasSetted;
   hamcrest::matcher<Param1> *matcher1;
   hamcrest::matcher<Param2> *matcher2;
   hamcrest::matcher<Param3> *matcher3;
};

//4 arity

template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
class CallMatcher<ReturnType, Param1, Param2, Param3, Param4> 
   : public CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3, Param4> >
{
public:
	CallMatcher(IRegistry &_registry) 
		: CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3, Param4> >(_registry)
      , parameterWasSetted(false) {}   

   Expectation *createCallExpectation_hc()
   {
      Expectation *exp= new Expectation();
      exp->AddParamMatcher(matcher1);
      exp->AddParamMatcher(matcher2);
      exp->AddParamMatcher(matcher3);
      return exp;
   }

   CallMatcher &WithParams(
      hamcrest::matcher<Param1> &p1, 
      hamcrest::matcher<Param2> &p2, 
      hamcrest::matcher<Param3> &p3, 
      hamcrest::matcher<Param4> &p4
      )
	{
		matcher1= p1.copy();
		matcher2= p2.copy();
		matcher3= p3.copy();
		matcher4= p4.copy();
		parameterWasSetted= true;
		return *this;
	}

private:
	bool parameterWasSetted;
   hamcrest::matcher<Param1> *matcher1;
	hamcrest::matcher<Param2> *matcher2;
	hamcrest::matcher<Param3> *matcher3;
	hamcrest::matcher<Param4> *matcher4;
};

} //namespace carnamock

#endif 