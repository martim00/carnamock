#pragma once
#ifndef INCLUDED_CALLREGISTRY_H
#define INCLUDED_CALLREGISTRY_H

#include "Call.h"
#include "NullType.h"
#include "CallAction.h"
#include "CallMatcher.h"
#include "ActionBuilder.h"
#include "TypeTraits.h"

#include "IRegistry.h"
#include "no_cref.h"

template <class ReturnType=nulltype
, class Param1=nulltype
, class Param2=nulltype
, class Param3=nulltype
, class Param4=nulltype
, class Param5=nulltype> 
class CallRegistry;

template <class ReturnType>
class CallRegistry<ReturnType> : public IRegistry
{
public:
   typedef CallRegistry<ReturnType> Type;
   typedef Call<ReturnType> CallType;
   typedef carnamock::is_void<ReturnType> IsVoidReturn;
	
	virtual ~CallRegistry()	{}

	ReturnType Execute()
	{
      this->AddCall(new Call<ReturnType>());
      if (!actions.empty()) {
         CallAction<ReturnType> *actionDerived= dynamic_cast<CallAction<ReturnType>*>(actions[0]);
         if (!IsVoidReturn::result) {
            return actionDerived->Execute();
         } else {
            actionDerived->Execute();
         }
      }

      if (!IsVoidReturn::result) {
         return ReturnType();
      }
      /*std::runtime_error e("You must set some action");
      throw e;*/
      
      //return ReturnType();
	}

   typename CallMatcherBase<CallMatcher<ReturnType> >::Ptr Expect()
   {
      return CallMatcherBase<CallMatcher<ReturnType> >::Ptr(new CallMatcher<ReturnType>(*this));
   }

   typename ActionBuilderBase<ActionBuilder<ReturnType> >::Ptr WhenCall()
   {
      return ActionBuilderBase<ActionBuilder<ReturnType> >::Ptr(new ActionBuilder<ReturnType>(*this));
   }  
};

template <class ReturnType, class P1>
class CallRegistry<ReturnType, P1> : public IRegistry
{
public:
   typedef typename no_cref<P1>::type Param1;
   typedef CallRegistry<ReturnType, Param1> Type;
   typedef Call<ReturnType, Param1> CallType;
   typedef carnamock::is_void<ReturnType> IsVoidReturn;
   
   virtual ~CallRegistry() {}

   typename CallMatcherBase<CallMatcher<ReturnType, Param1> >::Ptr Expect()
   {
      return CallMatcherBase<CallMatcher<ReturnType, Param1> >::Ptr(new CallMatcher<ReturnType, Param1>(*this));
   }

   typename ActionBuilderBase<ActionBuilder<ReturnType, Param1> >::Ptr WhenCall()
   {
      return ActionBuilderBase<ActionBuilder<ReturnType, Param1> >::Ptr(new ActionBuilder<ReturnType, Param1>(*this));
   }

	ReturnType Execute(Param1 p1)
	{
      this->AddCall(new Call<ReturnType, Param1>(p1));
		for (unsigned i= 0; i < actions.size(); i++)
		{
			CallAction<ReturnType, Param1> *action= dynamic_cast<CallAction<ReturnType, Param1>*>(actions[i]);

			if (action->KnowsThat(p1)) {
				GetNextCall()->Verified(true);
            if (!IsVoidReturn::result) 
				   return action->Execute(p1);
            else 
               action->Execute(p1);
			}
			continue;
		}
      if (!IsVoidReturn::result)
		   return ReturnType();
	}
};

//2 arity

template <class ReturnType, class P1, class P2>
class CallRegistry<ReturnType, P1, P2> : public IRegistry
{
public:
   typedef typename no_cref<P1>::type Param1;
   typedef typename no_cref<P2>::type Param2;

   typedef CallRegistry<ReturnType, Param1, Param2> Type;
   typedef Call<ReturnType, Param1, Param2> CallType;
   typedef carnamock::is_void<ReturnType> IsVoidReturn;

	virtual ~CallRegistry() {}

   typename CallMatcherBase<CallMatcher<ReturnType, Param1, Param2> >::Ptr Expect()
   {
      return CallMatcherBase<CallMatcher<ReturnType, Param1, Param2> >::Ptr(new CallMatcher<ReturnType, Param1, Param2>(*this));
   }

   typename ActionBuilderBase<ActionBuilder<ReturnType, Param1, Param2> >::Ptr WhenCall()
   {
      return ActionBuilderBase<ActionBuilder<ReturnType, Param1, Param2> >::Ptr(new ActionBuilder<ReturnType, Param1, Param2>(*this));
   }

   ReturnType Execute(Param1 p1, Param2 p2)
	{
      this->AddCall(new Call<ReturnType, Param1, Param2>(p1, p2));
		for (unsigned i= 0; i < actions.size(); i++)
		{
			CallAction<ReturnType, Param1, Param2> *action= 
            dynamic_cast<CallAction<ReturnType, Param1, Param2>*>(actions[i]);

			if (action->KnowsThat(p1, p2)) {
				//GetNextCall()->Verified(true);
            if (!IsVoidReturn::result)
				   return action->Execute(p1, p2);
            else 
               action->Execute(p1, p2);
			}
			continue;
		}
      if (!IsVoidReturn::result)
		   return ReturnType();
	}
};

//3 arity

template <class ReturnType, class Param1, class Param2, class Param3>
class CallRegistry<ReturnType, Param1, Param2, Param3> : public IRegistry
{
public:
   typedef CallRegistry<ReturnType, Param1, Param2, Param3> Type;
   typedef Call<ReturnType, Param1, Param2, Param3> CallType;
   typedef carnamock::is_void<ReturnType> IsVoidReturn;

	virtual ~CallRegistry() {}

   typename CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3> >::Ptr Expect()
   {
      return CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3> >::Ptr(new CallMatcher<ReturnType, Param1, Param2, Param3>(*this));
   }

   typename ActionBuilderBase<ActionBuilder<ReturnType, Param1, Param2, Param3> >::Ptr WhenCall()
   {
      return ActionBuilderBase<ActionBuilder<ReturnType, Param1, Param2, Param3> >::Ptr(new ActionBuilder<ReturnType, Param1, Param2, Param3>(*this));
   }

   ReturnType Execute(Param1 p1, Param2 p2, Param3 p3)
	{
      this->AddCall(new Call<ReturnType, Param1, Param2, Param3>(p1, p2, p3));
		for (unsigned i= 0; i < actions.size(); i++)
		{
			CallAction<ReturnType, Param1, Param2, Param3> *action= 
            dynamic_cast<CallAction<ReturnType, Param1, Param2, Param3> *>(actions[i]);

			if (action->KnowsThat(p1, p2, p3)) {
				GetNextCall()->Verified(true);
            if (!IsVoidReturn::result)
				   return action->Execute(p1, p2, p3);
            else 
               action->Execute(p1, p2, p3);
			}
			continue;
		}
      if (!IsVoidReturn::result)
		   return ReturnType();
	}	
};

//4 arity

template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
class CallRegistry<ReturnType, Param1, Param2, Param3, Param4> : public IRegistry
{
public:
   typedef CallRegistry<ReturnType, Param1, Param2, Param3, Param4> Type;
   typedef Call<ReturnType, Param1, Param2, Param3, Param4> CallType;
   typedef carnamock::is_void<ReturnType> IsVoidReturn;

	virtual ~CallRegistry() {}

   typename CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3, Param4> >::Ptr Expect()
   {
      return CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3, Param4> >::Ptr(new CallMatcher<ReturnType, Param1, Param2, Param3, Param4>);
   }

   typename ActionBuilderBase<ActionBuilder<ReturnType, Param1, Param2, Param3, Param4> >::Ptr WhenCall()
   {
      return ActionBuilderBase<ActionBuilder<ReturnType, Param1, Param2, Param3, Param4> >::Ptr(new ActionBuilder<ReturnType, Param1, Param2, Param3, Param4>(*this));
   }

   ReturnType Execute(Param1 p1, Param2 p2, Param3 p3, Param4 p4)
   {
      this->AddCall(new Call<ReturnType, Param1, Param2, Param3, Param4>(p1, p2, p3, p4));
		for (unsigned i= 0; i < actions.size(); i++)
		{
			CallAction<ReturnType, Param1, Param2, Param3, Param4> *action= 
            dynamic_cast<CallAction<ReturnType, Param1, Param2, Param3, Param4> *>(actions[i]);

			if (action->KnowsThat(p1, p2, p3, p4)) {
				GetNextCall()->Verified(true);
            if (!IsVoidReturn::result)
				   return action->Execute(p1, p2, p3, p4);
            else 
               action->Execute(p1, p2, p3, p4);
			}
			continue;
		}
      if (!IsVoidReturn::result)
		   return ReturnType();
	}	
};
//
////5 arity
//
//template <class ReturnType, class Param1, class Param2, class Param3, class Param4, class Param5>
//class CallRegistry<ReturnType, Param1, Param2, Param3, Param4, Param5> : public IRegistry
//{
//public:
//	CallRegistry(const std::string &methodName) : IRegistry(methodName), actualCall(0), verifyOnDestructor(true) {}
//	virtual ~CallRegistry()
//	{
//		MockMixin::GetRegistry<ReturnType, Param1, Param2, Param3, Param4, Param5>().erase(methodName);
//
//		if (!AllCallsVerified() && verifyOnDestructor)
//		{
//			std::runtime_error e("Nem todas as expectations foram aceitas");
//			throw e;
//		}
//	}
//
//	void AddAction(CallAction<ReturnType, Param1, Param2, Param3, Param4, Param5> *action)
//	{	
//		actions.push_back(action);
//	}
//
//	void VerifyOnDestructor(bool verify)
//	{
//		verifyOnDestructor= verify;
//	}
//
//	bool AllCallsVerified()
//	{
//		if (effectiveCalls.empty()) return true;
//		return (effectiveCalls[effectiveCalls.size()-1]->Verified());
//	}
//
//	bool ExpectationsAccepted() const
//	{
//		return false;
//	}
//
//	Call<ReturnType, Param1, Param2, Param3, Param4, Param5> &AddCall(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)
//	{
//		Call<ReturnType, Param1, Param2, Param3, Param4, Param5> *call= 
//			new Call<ReturnType, Param1, Param2, Param3, Param4, Param5>(p1, p2, p3, p4, p5);
//		
//		effectiveCalls.push_back(call);
//		return *call;
//	}
//
//	ReturnType ExecuteDefaultAction(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)
//	{
//		for (unsigned i= 0; i < actions.size(); i++)
//		{
//			CallAction<ReturnType, Param1, Param2, Param3, Param4, Param5> *action= actions[i];
//
//			if (action->KnowsThat(p1, p2, p3, p4, p5)) {
//				GetNextCall()->Verified(true);
//				return action->Execute(p1, p2, p3, p4, p5);
//			}
//			continue;
//		}
//		return ReturnType();
//	}
//	std::vector<Call<ReturnType, Param1, Param2, Param3, Param4, Param5>* > &GetCalls()
//	{
//		return effectiveCalls;
//	}
//
//	Call<ReturnType, Param1, Param2, Param3, Param4, Param5> *GetNextCall()
//	{
//		if (effectiveCalls.size() <= actualCall) {
//			std::runtime_error e("Nao ha mais calls");
//			throw e;
//		}
//		else {
//			return effectiveCalls[actualCall++];
//		}
//	}	
//private:
//	std::vector<Call<ReturnType, Param1, Param2, Param3, Param4, Param5>* > effectiveCalls;
//	std::vector<CallAction<ReturnType, Param1, Param2, Param3, Param4, Param5>* > actions;
//
//	size_t actualCall;
//	bool verifyOnDestructor;
//};

#endif 