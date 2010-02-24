#pragma once
#ifndef INCLUDED_CALLMATCHER_H
#define INCLUDED_CALLMATCHER_H

#include "NullType.h"
#include "Matcher.h"
#include <boost/shared_ptr.hpp>
#include "IRegistry.h"
#include "no_cref.h"


template <class ReturnType=nulltype
, class Param1=nulltype
, class Param2=nulltype
, class Param3= nulltype
, class Param4=nulltype
, class Param5=nulltype> 
class CallMatcher;

template <class Derived>
class CallMatcherBase
{
public:
   typedef boost::shared_ptr<Derived> Ptr;
   CallMatcherBase(IRegistry &_registry) : registry(_registry) {}
   virtual ~CallMatcherBase() {}

   void Times(size_t times)
   {
      ICall *icall= NULL;
      for (unsigned i= 0; i < times; i++) {
   
         registry.AddExpectation(createCallExpectation());

         /*int timesCalled= registry.GetTimesCalled();
         int actualCall= registry.GetActualCall();
         try {
            icall= registry.GetNextCall();
         } catch (std::runtime_error&) {
            registry.SetResult(new TimesIncorrect(registry.TimesVerified(), registry.GetTimesCalled()));
            break;
         }

         verifyParams(icall);*/
      }
   }

   virtual ICall *createCallExpectation()= 0;
   virtual void verifyParams(ICall *call)= 0;

protected:
   IRegistry &registry;
};


template <class ReturnType>
class CallMatcher<ReturnType> : public CallMatcherBase<CallMatcher<ReturnType> >
{
public:
   typedef Call<ReturnType> CallType;

	CallMatcher(IRegistry &_registry) 
      : CallMatcherBase<CallMatcher<ReturnType> >(_registry) {}

	ICall *createCallExpectation()
   {
      return new Call<ReturnType>();
   }

   void verifyParams(ICall *call) {
      call->Verified(true);
   }
};

template <class ReturnType, class Param1>
class CallMatcher<ReturnType, Param1> : public CallMatcherBase<CallMatcher<ReturnType, Param1> >
{
public:
	CallMatcher(IRegistry &_registry) 
      : CallMatcherBase<CallMatcher<ReturnType, Param1> >(_registry), parameterWasSetted(false) {}

   void verifyParams(ICall *icall)
   {
      Call<ReturnType, Param1> *call= 
         dynamic_cast<Call<ReturnType, Param1> *>(icall);

      if (parameterWasSetted) {
         if (*matcher1 != call->GetParam1()) {

            registry.SetResult(new ParameterIncorrect(1, matcher1->DescribeError()));
         }
         call->Verified(true);
      } else {
         std::runtime_error e("WithParams must be setted before Times");
         throw e;
      }
   }

   ICall *createCallExpectation()
   {
      return new Call<ReturnType, Matcher<Param1>* >(matcher1);
   }

	CallMatcher &WithParams(Matcher<Param1> &p1)
	{
		matcher1= &p1;
		parameterWasSetted= true;
		return *this;
	}

private:
	bool parameterWasSetted;
	Matcher<Param1> *matcher1;
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

   ICall *createCallExpectation()
   {
      return new Call<ReturnType, Matcher<Param1>*, Matcher<Param2>* >(matcher1, matcher2);
   }

   void verifyParams(ICall *icall)
   {
      Call<ReturnType, Param1, Param2> *call= 
         dynamic_cast<Call<ReturnType, Param1, Param2> *>(icall);

      if (parameterWasSetted) {
         if (*matcher1 != call->GetParam1()) {
            registry.SetResult(new ParameterIncorrect(1, matcher1->DescribeError()));
         } else if (*matcher2 != call->GetParam2()) {
            registry.SetResult(new ParameterIncorrect(2, matcher2->DescribeError()));
         }
         call->Verified(true);
      } else {
         std::runtime_error e("WithParams must be setted before Times");
         throw e;
      }
   }

	CallMatcher &WithParams(Matcher<Param1> &p1, Matcher<Param2> &p2)
	{
		matcher1= &p1;
		matcher2= &p2;
		parameterWasSetted= true;
		return *this;
	}

private:
	bool parameterWasSetted;
	Matcher<Param1> *matcher1;
	Matcher<Param2> *matcher2;
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

   ICall *createCallExpectation()
   {
      return new Call<ReturnType, Matcher<Param1>*, Matcher<Param2>*, Matcher<Param3>* >(
         matcher1, matcher2, matcher3);
   }

   void verifyParams(ICall *icall)
   {
      Call<ReturnType, Param1, Param2, Param3> *call= 
         dynamic_cast<Call<ReturnType, Param1, Param2, Param3> *>(icall);

      if (parameterWasSetted) {
         if (*matcher1 != call->GetParam1()) {
            registry.SetResult(new ParameterIncorrect(1, matcher1->DescribeError()));
         } else if (*matcher2 != call->GetParam2()) {
            registry.SetResult(new ParameterIncorrect(2, matcher2->DescribeError()));
         } else if (*matcher3 != call->GetParam3()) {
            registry.SetResult(new ParameterIncorrect(3, matcher3->DescribeError()));
         }
         call->Verified(true);
      } else {
         std::runtime_error e("WithParams must be setted before Times");
         throw e;
      }
   }

	CallMatcher &WithParams(Matcher<Param1> &p1, Matcher<Param2> &p2, Matcher<Param3> &p3)
	{
		matcher1= &p1;
		matcher2= &p2;
		matcher3= &p3;
		parameterWasSetted= true;
		return *this;
	}

private:
	bool parameterWasSetted;
	Matcher<Param1> *matcher1;
	Matcher<Param2> *matcher2;
	Matcher<Param3> *matcher3;
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

   void verifyParams(ICall *icall)
   {
      Call<ReturnType, Param1, Param2, Param3, Param4> *call= 
         dynamic_cast<Call<ReturnType, Param1, Param2, Param3, Param4> *>(icall);

      if (parameterWasSetted) {
         if (*matcher1 != call->GetParam1()) {
            registry.SetResult(new ParameterIncorrect(1, matcher1->DescribeError()));
         } else if (*matcher2 != call->GetParam2()) {
            registry.SetResult(new ParameterIncorrect(2, matcher2->DescribeError()));
         } else if (*matcher3 != call->GetParam3()) {
            registry.SetResult(new ParameterIncorrect(3, matcher3->DescribeError()));
         } else if (*matcher4 != call->GetParam4()) {
            registry.SetResult(new ParameterIncorrect(4, matcher4->DescribeError()));
         }
         call->Verified(true);
      } else {
         std::runtime_error e("WithParams must be setted before Times");
         throw e;
      }
   }

   ICall *createCallExpectation()
   {
      return new Call<ReturnType, Matcher<Param1>*, Matcher<Param2>*, Matcher<Param3>*, Matcher<Param4>*>
         (matcher1, matcher2, matcher3, matcher4);
   }

	CallMatcher &WithParams(Matcher<Param1> &p1, Matcher<Param2> &p2, Matcher<Param3> &p3, Matcher<Param4> &p4)
	{
		matcher1= &p1;
		matcher2= &p2;
		matcher3= &p3;
		matcher4= &p4;
		parameterWasSetted= true;
		return *this;
	}

private:
	bool parameterWasSetted;
	Matcher<Param1> *matcher1;
	Matcher<Param2> *matcher2;
	Matcher<Param3> *matcher3;
	Matcher<Param4> *matcher4;
};

#endif 