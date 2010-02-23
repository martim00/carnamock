#pragma once
#ifndef INCLUDED_CALLREGISTRY_H
#define INCLUDED_CALLREGISTRY_H

#include "Call.h"
#include "NullType.h"
#include "CallAction.h"
#include "CallMatcher.h"

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
class CallRegistry<ReturnType> : public IRegistry/*<CallRegistry<ReturnType>>*/
{
public:
   typedef CallRegistry<ReturnType> Type;
   typedef Call<ReturnType> CallType;   
	
	virtual ~CallRegistry()
	{
		/*MockMixin::GetRegistry<ReturnType>().erase(methodName);
		if (!AllCallsVerified())
		{
			std::runtime_error e("Nem todas as expectations do metodo "+methodName+" foram aceitas");
			throw e;
		}*/
	}

	//bool AllCallsVerified()
	//{
	//	if (effectiveCalls.empty()) return true;
	//	return (effectiveCalls[effectiveCalls.size()-1]->Verified());
	//}

	/*void AddCall()
	{
		Call<ReturnType> *call= new Call<ReturnType>();
		effectiveCalls.push_back(call);
	}*/   

	ReturnType Execute()
	{
      this->AddCall(new Call<ReturnType>());
      if (!actions.empty()) {
         CallAction<ReturnType> *actionDerived= dynamic_cast<CallAction<ReturnType>*>(actions[0]);
         return actionDerived->Execute();
      }
      //TODO: logar isso..
      return ReturnType();
	}

   typename CallMatcherBase<CallMatcher<ReturnType>>::Ptr Expect()
   {
      return CallMatcherBase<CallMatcher<ReturnType> >::Ptr(new CallMatcher<ReturnType>(*this));
   }

	/*Call<ReturnType> *GetNextCall()
	{
		if (effectiveCalls.size() <= actualCall) {
			std::runtime_error e("Nao ha mais calls");
			throw e;
		}
		else {
			return effectiveCalls[actualCall++];
		}
	}*/

private:
	//std::vector<Call<ReturnType>* > effectiveCalls;
   //CallAction<ReturnType>* action;	
};

template <class ReturnType, class P1>
class CallRegistry<ReturnType, P1> : public IRegistry/*<CallRegistry<ReturnType, Param1>>*/
{
public:
   typedef typename no_cref<P1>::type Param1;
   typedef CallRegistry<ReturnType, Param1> Type;
   typedef Call<ReturnType, Param1> CallType;
   

   
	virtual ~CallRegistry() 
   {
		/*MockMixin::GetRegistry<ReturnType, Param1>().erase(methodName);

		if (!AllCallsVerified() && verifyOnDestructor)
		{
			std::runtime_error e("Nem todas as expectations do metodo "+methodName+" foram aceitas");
			throw e;
		}*/
	}

   typename CallMatcherBase<CallMatcher<ReturnType, Param1> >::Ptr Expect()
   {
      return CallMatcherBase<CallMatcher<ReturnType, Param1> >::Ptr(new CallMatcher<ReturnType, Param1>(*this));
   }

	/*void AddAction(CallAction<ReturnType, Param1> *action)
	{	
		actions.push_back(action);
	}*/

	/*bool AllCallsVerified()
	{
		if (effectiveCalls.empty()) return true;
		return (effectiveCalls[effectiveCalls.size()-1]->Verified());
	}*/

	//Call<ReturnType, Param1> &AddCall(Param1 p1)
	//{
	//	Call<ReturnType, Param1> *call= new Call<ReturnType, Param1>(p1);
	//	
	//	effectiveCalls.push_back(call);
	//	return *call;
	//}   

	ReturnType Execute(Param1 p1)
	{
      this->AddCall(new Call<ReturnType, Param1>(p1));
		for (unsigned i= 0; i < actions.size(); i++)
		{
			CallAction<ReturnType, Param1> *action= dynamic_cast<CallAction<ReturnType, Param1>*>(actions[i]);

			if (action->KnowsThat(p1)) {
				GetNextCall()->Verified(true);
				return action->Execute(p1);
			}
			continue;
		}
		return ReturnType();
	}
	/*std::vector<Call<ReturnType, Param1>* > &GetCalls()
	{
		return effectiveCalls;
	}

	Call<ReturnType, Param1> *GetNextCall()
	{
		if (effectiveCalls.size() <= actualCall) {
			std::runtime_error e("Nao ha mais calls");
			throw e;
		}
		else {
			return effectiveCalls[actualCall++];
		}
	}	
   size_t GetTimesCalled() { return effectiveCalls.size(); }
private:
	std::vector<Call<ReturnType, Param1>* > effectiveCalls;*/
	//std::vector<CallAction<ReturnType, Param1>* > actions;

	//size_t actualCall;
	/*bool verifyOnDestructor;*/
};

//2 arity

template <class ReturnType, class Param1, class Param2>
class CallRegistry<ReturnType, Param1, Param2> : public IRegistry/*<CallRegistry<ReturnType, Param1, Param2>>*/
{
public:
   typedef CallRegistry<ReturnType, Param1, Param2> Type;
   typedef Call<ReturnType, Param1, Param2> CallType;

	virtual ~CallRegistry()
	{
	/*	MockMixin::GetRegistry<ReturnType, Param1, Param2>().erase(methodName);

		if (!AllCallsVerified() && verifyOnDestructor)
		{
         std::stringstream ss;
         ss << "Nem todas as expectations do metodo " << methodName <<  "foram aceitas\n";
			std::runtime_error e(ss.str());
			throw e;
		}*/
	}

   typename CallMatcherBase<CallMatcher<ReturnType, Param1, Param2> >::Ptr Expect()
   {
      return CallMatcherBase<CallMatcher<ReturnType, Param1, Param2> >::Ptr(new CallMatcher<ReturnType, Param1, Param2>);
   }

	/*void AddAction(CallAction<ReturnType, Param1, Param2> *action)
	{	
		actions.push_back(action);
	}

	bool AllCallsVerified()
	{
		if (effectiveCalls.empty()) return true;
		return (effectiveCalls[effectiveCalls.size()-1]->Verified());
	}

	Call<ReturnType, Param1, Param2> &AddCall(Param1 p1, Param2 p2)
	{
		Call<ReturnType, Param1, Param2> *call= new Call<ReturnType, Param1, Param2>(p1, p2);
		
		effectiveCalls.push_back(call);
		return *call;
	}*/

   ReturnType Execute(Param1 p1, Param2 p2)
	{
      this->AddCall(new Call<ReturnType, Param1, Param2>(p1, p2));
		for (unsigned i= 0; i < actions.size(); i++)
		{
			CallAction<ReturnType, Param1, Param2> *action= dynamic_cast<CallAction<ReturnType, Param1, Param2>*>(actions[i]);

			if (action->KnowsThat(p1, p2)) {
				GetNextCall()->Verified(true);
				return action->Execute(p1, p2);
			}
			continue;
		}
		return ReturnType();
	}
	/*std::vector<Call<ReturnType, Param1, Param2>* > &GetCalls()
	{
		return effectiveCalls;
	}

	Call<ReturnType, Param1, Param2> *GetNextCall()
	{
		if (effectiveCalls.size() <= actualCall) {
			std::runtime_error e("Nao ha mais calls");
			throw e;
		}
		else {
			return effectiveCalls[actualCall++];
		}
	}	
   size_t GetTimesCalled() { return effectiveCalls.size(); }
private:
	std::vector<Call<ReturnType, Param1, Param2>* > effectiveCalls;*/
	//std::vector<CallAction<ReturnType, Param1, Param2>* > actions;

	/*size_t actualCall;
	bool verifyOnDestructor;*/
};

//3 arity

template <class ReturnType, class Param1, class Param2, class Param3>
class CallRegistry<ReturnType, Param1, Param2, Param3> : public IRegistry/*<CallRegistry<ReturnType, Param1, Param2, Param3>>*/
{
public:
   typedef CallRegistry<ReturnType, Param1, Param2, Param3> Type;
   typedef Call<ReturnType, Param1, Param2, Param3> CallType;

	virtual ~CallRegistry()
	{
		/*MockMixin::GetRegistry<ReturnType, Param1, Param2, Param3>().erase(methodName);

		if (!AllCallsVerified() && verifyOnDestructor)
		{
         std::runtime_error e("Nem todas as expectations do metodo "+methodName+" foram aceitas");
			throw e;
		}*/
	}

   typename CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3> >::Ptr Expect()
   {
      return CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3> >::Ptr(new CallMatcher<ReturnType, Param1, Param2, Param3>);
   }

	/*void AddAction(CallAction<ReturnType, Param1, Param2, Param3> *action)
	{	
		actions.push_back(action);
	}*/

	/*void VerifyOnDestructor(bool verify)
	{
		verifyOnDestructor= verify;
	}*/

	/*bool AllCallsVerified()
	{
		if (effectiveCalls.empty()) return true;
		return (effectiveCalls[effectiveCalls.size()-1]->Verified());
	}

	Call<ReturnType, Param1, Param2, Param3> &AddCall(Param1 p1, Param2 p2, Param3 p3)
	{
		Call<ReturnType, Param1, Param2, Param3> *call= new Call<ReturnType, Param1, Param2, Param3>(p1, p2, p3);
		
		effectiveCalls.push_back(call);
		return *call;
	}*/

   ReturnType Execute(Param1 p1, Param2 p2, Param3 p3)
	{
      this->AddCall(new Call<ReturnType, Param1, Param2, Param3>(p1, p2, p3));
		for (unsigned i= 0; i < actions.size(); i++)
		{
			CallAction<ReturnType, Param1, Param2, Param3> *action= 
            dynamic_cast<CallAction<ReturnType, Param1, Param2, Param3> *>(actions[i]);

			if (action->KnowsThat(p1, p2, p3)) {
				GetNextCall()->Verified(true);
				return action->Execute(p1, p2, p3);
			}
			continue;
		}
		return ReturnType();
	}
	/*std::vector<Call<ReturnType, Param1, Param2, Param3>* > &GetCalls()
	{
		return effectiveCalls;
	}

	Call<ReturnType, Param1, Param2, Param3> *GetNextCall()
	{
		if (effectiveCalls.size() <= actualCall) {
			std::runtime_error e("Nao ha mais calls");
			throw e;
		}
		else {
			return effectiveCalls[actualCall++];
		}
	}	
   size_t GetTimesCalled() { return effectiveCalls.size(); }
private:
	std::vector<Call<ReturnType, Param1, Param2, Param3>* > effectiveCalls;*/
	//std::vector<CallAction<ReturnType, Param1, Param2, Param3>* > actions;

	/*size_t actualCall;
	bool verifyOnDestructor;*/
};

//4 arity

template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
class CallRegistry<ReturnType, Param1, Param2, Param3, Param4> : public IRegistry/*<CallRegistry<ReturnType, Param1, Param2, Param3, Param4>>*/
{
public:
   typedef CallRegistry<ReturnType, Param1, Param2, Param3, Param4> Type;
   typedef Call<ReturnType, Param1, Param2, Param3, Param4> CallType;

	virtual ~CallRegistry()
	{
		/*MockMixin::GetRegistry<ReturnType, Param1, Param2, Param3, Param4>().erase(methodName);

		if (!AllCallsVerified() && verifyOnDestructor)
		{
			std::runtime_error e("Nem todas as expectations do metodo "+methodName+" foram aceitas");
			throw e;
		}*/
	}

   typename CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3, Param4> >::Ptr Expect()
   {
      return CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3, Param4> >::Ptr(new CallMatcher<ReturnType, Param1, Param2, Param3, Param4>);
   }

	/*void AddAction(CallAction<ReturnType, Param1, Param2, Param3, Param4> *action)
	{	
		actions.push_back(action);
	}

	void VerifyOnDestructor(bool verify)
	{
		verifyOnDestructor= verify;
	}*/

	/*bool AllCallsVerified()
	{
		if (effectiveCalls.empty()) return true;
		return (effectiveCalls[effectiveCalls.size()-1]->Verified());
	}

	Call<ReturnType, Param1, Param2, Param3, Param4> &AddCall(Param1 p1, Param2 p2, Param3 p3, Param4 p4)
	{
		Call<ReturnType, Param1, Param2, Param3, Param4> *call= new Call<ReturnType, Param1, Param2, Param3, Param4>(p1, p2, p3, p4);
		
		effectiveCalls.push_back(call);
		return *call;
	}*/


   ReturnType Execute(Param1 p1, Param2 p2, Param3 p3, Param4 p4)
   {
      this->AddCall(new Call<ReturnType, Param1, Param2, Param3, Param4>(p1, p2, p3, p4));
		for (unsigned i= 0; i < actions.size(); i++)
		{
			CallAction<ReturnType, Param1, Param2, Param3, Param4> *action= actions[i];

			if (action->KnowsThat(p1, p2, p3, p4)) {
				GetNextCall()->Verified(true);
				return action->Execute(p1, p2, p3, p4);
			}
			continue;
		}
		return ReturnType();
	}
	/*std::vector<Call<ReturnType, Param1, Param2, Param3, Param4>* > &GetCalls()
	{
		return effectiveCalls;
	}

	Call<ReturnType, Param1, Param2, Param3, Param4> *GetNextCall()
	{
		if (effectiveCalls.size() <= actualCall) {
			std::runtime_error e("Nao ha mais calls");
			throw e;
		}
		else {
			return effectiveCalls[actualCall++];
		}
	}	
   size_t GetTimesCalled() { return effectiveCalls.size(); }
private:
	std::vector<Call<ReturnType, Param1, Param2, Param3, Param4>* > effectiveCalls;*/
	//std::vector<CallAction<ReturnType, Param1, Param2, Param3, Param4>* > actions;

	/*size_t actualCall;
	bool verifyOnDestructor;*/
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