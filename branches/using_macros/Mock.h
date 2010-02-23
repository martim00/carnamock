#ifndef INCLUDED_MOCK_H
#define INCLUDED_MOCK_H

#include <vector>
#include <stdexcept>

#include "CallRegistry.h"
#include "Call.h"
#include "CallMatcher.h"
#include "ActionBuilder.h"
#include "no_cref.h"


class MockMixin 
{
//public:
//	typedef std::map<std::string, IRegistry*>::iterator CallIterator; 
//
//	virtual ~MockMixin() {
//		clearCalls();
//	} 
//	MockMixin() {} 
//
//	template <class ReturnType>
//	CallMatcher<ReturnType> *Expect(const std::string &methodName)
//	{
//		if (!alreadyExistsRegistryForMethod<ReturnType>(methodName)) {
//			GetRegistry<ReturnType>()[methodName]= new CallRegistry<ReturnType>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType>()[methodName];
//		}
//		return new CallMatcher<ReturnType>(*GetRegistry<ReturnType>()[methodName]);
//	}
//
//	template <class ReturnType, class Param1>
//	CallMatcher<ReturnType, typename no_cref<Param1>::type> *Expect(const std::string &methodName)
//	{
//		typedef no_cref<Param1>::type P1;
//		if (!alreadyExistsRegistryForMethod<ReturnType, P1>(methodName)) {
//			GetRegistry<ReturnType, P1>()[methodName]= new CallRegistry<ReturnType, P1>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType, P1>()[methodName];
//		}		
//		return new CallMatcher<ReturnType, P1>(*GetRegistry<ReturnType, P1>()[methodName]);
//	}
//
//	template <class ReturnType, class Param1, class Param2>
//	CallMatcher<ReturnType, typename no_cref<Param1>::type, typename no_cref<Param2>::type> *
//		Expect(const std::string &methodName)
//	{
//		typedef no_cref<Param1>::type P1;
//		typedef no_cref<Param2>::type P2;
//
//		if (!alreadyExistsRegistryForMethod<ReturnType, P1, P2>(methodName)) {
//			GetRegistry<ReturnType, P1, P2>()[methodName]= new CallRegistry<ReturnType, P1, P2>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType, P1, P2>()[methodName];
//		}		
//		return new CallMatcher<ReturnType, P1, P2>(*GetRegistry<ReturnType, P1, P2>()[methodName]);
//	}
//
//	
//	template <class ReturnType, class Param1, class Param2, class Param3>
//	CallMatcher<ReturnType
//		, typename no_cref<Param1>::type
//		, typename no_cref<Param2>::type
//		, typename no_cref<Param3>::type> *Expect(const std::string &methodName)
//	{
//		typedef no_cref<Param1>::type P1;
//		typedef no_cref<Param2>::type P2;
//		typedef no_cref<Param3>::type P3;
//
//		if (!alreadyExistsRegistryForMethod<ReturnType, P1, P2, P3>(methodName)) {
//			GetRegistry<ReturnType, P1, P2, P3>()[methodName]= new CallRegistry<ReturnType, P1, P2, P3>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType, P1, P2, P3>()[methodName];
//		}		
//		return new CallMatcher<ReturnType, P1, P2, P3>(*GetRegistry<ReturnType, P1, P2, P3>()[methodName]);
//	}
//
//	//4 arity
//
//	template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
//	CallMatcher<ReturnType
//		, typename no_cref<Param1>::type
//		, typename no_cref<Param2>::type
//		, typename no_cref<Param3>::type
//		, typename no_cref<Param4>::type> *Expect(const std::string &methodName)
//	{
//		typedef no_cref<Param1>::type P1;
//		typedef no_cref<Param2>::type P2;
//		typedef no_cref<Param3>::type P3;
//		typedef no_cref<Param4>::type P4;
//
//		if (!alreadyExistsRegistryForMethod<ReturnType, P1, P2, P3, P4>(methodName)) {
//			GetRegistry<ReturnType, P1, P2, P3, P4>()[methodName]= new CallRegistry<ReturnType, P1, P2, P3, P4>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType, P1, P2, P3, P4>()[methodName];
//		}		
//		return new CallMatcher<ReturnType, P1, P2, P3, P4>(*GetRegistry<ReturnType, P1, P2, P3, P4>()[methodName]);
//	}
//
//	//5 arity
//	template <class ReturnType, class Param1, class Param2, class Param3, class Param4, class Param5>
//	CallMatcher<ReturnType
//		, typename no_cref<Param1>::type
//		, typename no_cref<Param2>::type
//		, typename no_cref<Param3>::type
//		, typename no_cref<Param4>::type
//		, typename no_cref<Param5>::type> *Expect(const std::string &methodName)
//	{
//		typedef no_cref<Param1>::type P1;
//		typedef no_cref<Param2>::type P2;
//		typedef no_cref<Param3>::type P3;
//		typedef no_cref<Param4>::type P4;
//		typedef no_cref<Param5>::type P5;
//
//		if (!alreadyExistsRegistryForMethod<ReturnType, P1, P2, P3, P4, P5>(methodName)) {
//			GetRegistry<ReturnType, P1, P2, P3, P4, P5>()[methodName]= new CallRegistry<ReturnType, P1, P2, P3, P4, P5>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType, P1, P2, P3, P4, P5>()[methodName];
//		}		
//		return new CallMatcher<ReturnType, P1, P2, P3, P4, P5>(*GetRegistry<ReturnType, P1, P2, P3, P4, P5>()[methodName]);
//	}
//	
//	template <class ReturnType>
//	bool alreadyExistsRegistryForMethod(const std::string &methodName)
//	{
//		return GetRegistry<ReturnType>().find(methodName) != GetRegistry<ReturnType>().end();
//	}
//
//	template <class ReturnType, class P1>
//	bool alreadyExistsRegistryForMethod(const std::string &methodName)
//	{
//		return GetRegistry<ReturnType, P1>().find(methodName) != GetRegistry<ReturnType, P1>().end();
//	}
//
//	template <class ReturnType, class P1, class P2>
//	bool alreadyExistsRegistryForMethod(const std::string &methodName)
//	{
//		return GetRegistry<ReturnType, P1, P2>().find(methodName) != GetRegistry<ReturnType, P1, P2>().end();
//	}
//
//	template <class ReturnType, class P1, class P2, class P3>
//	bool alreadyExistsRegistryForMethod(const std::string &methodName)
//	{
//		return GetRegistry<ReturnType, P1, P2, P3>().find(methodName) != GetRegistry<ReturnType, P1, P2, P3>().end();
//	}
//
//	template <class ReturnType, class P1, class P2, class P3, class P4>
//	bool alreadyExistsRegistryForMethod(const std::string &methodName)
//	{
//		return GetRegistry<ReturnType, P1, P2, P3, P4>().find(methodName) != GetRegistry<ReturnType, P1, P2, P3, P4>().end();
//	}
//
//	template <class ReturnType, class P1, class P2, class P3, class P4, class P5>
//	bool alreadyExistsRegistryForMethod(const std::string &methodName)
//	{
//		return GetRegistry<ReturnType, P1, P2, P3, P4, P5>().find(methodName) != GetRegistry<ReturnType, P1, P2, P3, P4, P5>().end();
//	}
//
//	template <class ReturnType>
//	ReturnType registerCallForMethod(const std::string &methodName)
//	{
//		if (!alreadyExistsRegistryForMethod<ReturnType>(methodName)) {
//			this->GetRegistry<ReturnType>()[methodName]= new CallRegistry<ReturnType>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType>()[methodName];
//		}
//		this->GetRegistry<ReturnType>()[methodName]->AddCall(new Call<ReturnType>());
//
//		return this->GetRegistry<ReturnType>()[methodName]->ExecuteDefaultAction();
//	}
//
//	template <class ReturnType>
//	ReturnType registerCallForVoidMethod(const std::string &methodName)
//	{
//		if (!alreadyExistsRegistryForMethod<ReturnType>(methodName)) {
//			this->GetRegistry<ReturnType>()[methodName]= new CallRegistry<ReturnType>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType>()[methodName];
//		}
//		this->GetRegistry<ReturnType>()[methodName]->AddCall(new Call<ReturnType>);
//	}	
//	
//	//1 arity
//	template <class ReturnType, class Param1>
//	ReturnType registerCallForMethod(const std::string &methodName, Param1 p1)
//	{
//		typedef no_cref<Param1>::type P1;
//		if (!alreadyExistsRegistryForMethod<ReturnType, P1>(methodName)) {
//			this->GetRegistry<ReturnType, P1>()[methodName]= new CallRegistry<ReturnType, P1>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType, P1>()[methodName];
//		}
//		Call<ReturnType, P1> &call= this->GetRegistry<ReturnType, P1>()[methodName]->AddCall(p1);
//		
//		return this->GetRegistry<ReturnType, P1>()[methodName]->ExecuteDefaultAction(p1);
//	}
//
//	template <class ReturnType, class Param1>
//	ReturnType registerCallForVoidMethod(const std::string &methodName, Param1 p1)
//	{
//		typedef no_cref<Param1>::type P1;
//		if (!alreadyExistsRegistryForMethod<ReturnType, P1>(methodName)) {
//			this->GetRegistry<ReturnType, P1>()[methodName]= new CallRegistry<ReturnType, P1>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType, P1>()[methodName];
//		}
//		Call<ReturnType, P1> &call= this->GetRegistry<ReturnType, P1>()[methodName]->AddCall(p1);
//	}
//
//	//2 arity
//	template <class ReturnType, class P1, class P2>
//	CallRegistry<ReturnType, P1, P2> &GetRegistryForMethod(const std::string &methodName)
//	{
//		if (!alreadyExistsRegistryForMethod<ReturnType, P1, P2>(methodName)) {
//			this->GetRegistry<ReturnType, P1, P2>()[methodName]= new CallRegistry<ReturnType, P1, P2>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType, P1, P2>()[methodName];
//		}
//		return *this->GetRegistry<ReturnType, P1, P2>()[methodName];
//	}
//
//	template <class ReturnType, class Param1, class Param2>
//	ReturnType registerCallForMethod(const std::string &methodName, Param1 p1, Param2 p2)
//	{
//		typedef no_cref<Param1>::type P1;
//		typedef no_cref<Param2>::type P2;
//
//		CallRegistry<ReturnType, P1, P2> &registry= this->GetRegistryForMethod<ReturnType, P1, P2>(methodName);
//		Call<ReturnType, P1, P2> &call= registry.AddCall(p1, p2);
//		
//		return registry.ExecuteDefaultAction(p1, p2);
//	}
//
//	template <class ReturnType, class Param1, class Param2>
//	ReturnType registerCallForVoidMethod(const std::string &methodName, Param1 p1, Param2 p2)
//	{
//		typedef no_cref<Param1>::type P1;
//		typedef no_cref<Param2>::type P2;
//
//		CallRegistry<ReturnType, P1, P2> &registry= this->GetRegistryForMethod<ReturnType, P1, P2>(methodName);
//		Call<ReturnType, P1, P2> &call= registry.AddCall(p1, p2);
//	}
//
//	//3 arity
//	template <class ReturnType, class P1, class P2, class P3>
//	CallRegistry<ReturnType, P1, P2, P3> &GetRegistryForMethod(const std::string &methodName)
//	{
//		if (!alreadyExistsRegistryForMethod<ReturnType, P1, P2, P3>(methodName)) {
//			this->GetRegistry<ReturnType, P1, P2, P3>()[methodName]= new CallRegistry<ReturnType, P1, P2, P3>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType, P1, P2, P3>()[methodName];
//		}
//		return *this->GetRegistry<ReturnType, P1, P2, P3>()[methodName];
//	}
//
//	template <class ReturnType, class Param1, class Param2, class Param3>
//	ReturnType registerCallForMethod(const std::string &methodName, Param1 p1, Param2 p2, Param3 p3)
//	{
//		typedef no_cref<Param1>::type P1;
//		typedef no_cref<Param2>::type P2;
//		typedef no_cref<Param3>::type P3;
//
//		CallRegistry<ReturnType, P1, P2, P3> &registry= this->GetRegistryForMethod<ReturnType, P1, P2, P3>(methodName);
//		Call<ReturnType, P1, P2, P3> &call= registry.AddCall(p1, p2, p3);
//		
//		return registry.ExecuteDefaultAction(p1, p2, p3);
//	}
//
//   template <class ReturnType, class Param1, class Param2, class Param3>
//   ReturnType registerCallForVoidMethod(const std::string &methodName, Param1 p1, Param2 p2, Param3 p3)
//   {
//      typedef no_cref<Param1>::type P1;
//      typedef no_cref<Param2>::type P2;
//      typedef no_cref<Param3>::type P3;
//
//      CallRegistry<ReturnType, P1, P2, P3> &registry= this->GetRegistryForMethod<ReturnType, P1, P2, P3>(methodName);
//      Call<ReturnType, P1, P2, P3> &call= registry.AddCall(p1, p2, p3);
//   }
//
//
//	//4 arity
//	template <class ReturnType, class P1, class P2, class P3, class P4>
//	CallRegistry<ReturnType, P1, P2, P3, P4> &GetRegistryForMethod(const std::string &methodName)
//	{
//		if (!alreadyExistsRegistryForMethod<ReturnType, P1, P2, P3, P4>(methodName)) {
//			this->GetRegistry<ReturnType, P1, P2, P3, P4>()[methodName]= new CallRegistry<ReturnType, P1, P2, P3, P4>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType, P1, P2, P3, P4>()[methodName];
//		}
//		return *this->GetRegistry<ReturnType, P1, P2, P3, P4>()[methodName];
//	}
//
//	template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
//	ReturnType registerCallForMethod(const std::string &methodName, Param1 p1, Param2 p2, Param3 p3, Param4 p4)
//	{
//		typedef no_cref<Param1>::type P1;
//		typedef no_cref<Param2>::type P2;
//		typedef no_cref<Param3>::type P3;
//		typedef no_cref<Param4>::type P4;
//
//		CallRegistry<ReturnType, P1, P2, P3, P4> &registry= this->GetRegistryForMethod<ReturnType, P1, P2, P3, P4>(methodName);
//		Call<ReturnType, P1, P2, P3, P4> &call= registry.AddCall(p1, p2, p3, p4);
//		
//		return registry.ExecuteDefaultAction(p1, p2, p3, p4);
//	}
//
//   template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
//   ReturnType registerCallForVoidMethod(const std::string &methodName, Param1 p1, Param2 p2, Param3 p3, Param4 p4)
//   {
//      typedef no_cref<Param1>::type P1;
//      typedef no_cref<Param2>::type P2;
//      typedef no_cref<Param3>::type P3;
//      typedef no_cref<Param4>::type P4;
//
//      CallRegistry<ReturnType, P1, P2, P3, P4> &registry= this->GetRegistryForMethod<ReturnType, P1, P2, P3, P4>(methodName);
//      Call<ReturnType, P1, P2, P3, P4> &call= registry.AddCall(p1, p2, p3, p4);
//   }
//
//
//	//5 arity
//	template <class ReturnType, class P1, class P2, class P3, class P4, class P5>
//	CallRegistry<ReturnType, P1, P2, P3, P4, P5> &GetRegistryForMethod(const std::string &methodName)
//	{
//		if (!alreadyExistsRegistryForMethod<ReturnType, P1, P2, P3, P4, P5>(methodName)) {
//			this->GetRegistry<ReturnType, P1, P2, P3, P4, P5>()[methodName]= new CallRegistry<ReturnType, P1, P2, P3, P4, P5>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType, P1, P2, P3, P4, P5>()[methodName];
//		}
//		return *this->GetRegistry<ReturnType, P1, P2, P3, P4, P5>()[methodName];
//	}
//
//	template <class ReturnType, class Param1, class Param2, class Param3, class Param4, class Param5>
//	ReturnType registerCallForMethod(const std::string &methodName, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)
//	{
//		typedef no_cref<Param1>::type P1;
//		typedef no_cref<Param2>::type P2;
//		typedef no_cref<Param3>::type P3;
//		typedef no_cref<Param4>::type P4;
//		typedef no_cref<Param5>::type P5;
//
//		CallRegistry<ReturnType, P1, P2, P3, P4, P5> &registry= this->GetRegistryForMethod<ReturnType, P1, P2, P3, P4, P5>(methodName);
//		Call<ReturnType, P1, P2, P3, P4, P5> &call= registry.AddCall(p1, p2, p3, p4, p5);
//		
//		return registry.ExecuteDefaultAction(p1, p2, p3, p4, p5);
//	}
//
//   template <class ReturnType>
//   ActionBuilder<ReturnType> *WhenCall(const std::string &methodName)
//   {
//      if (!alreadyExistsRegistryForMethod<ReturnType>(methodName)) {
//         this->GetRegistry<ReturnType>()[methodName]= new CallRegistry<ReturnType>(methodName);
//         this->regReg[methodName]= this->GetRegistry<ReturnType>()[methodName];
//      }
//      return new ActionBuilder<ReturnType>(*this->GetRegistry<ReturnType>()[methodName]);
//   }
//
//	template <class ReturnType, class Param1>
//	ActionBuilder<ReturnType, typename no_cref<Param1>::type> *WhenCall(const std::string &methodName)
//	{
//		typedef no_cref<Param1>::type P1;
//		if (!alreadyExistsRegistryForMethod<ReturnType, P1>(methodName)) {
//			this->GetRegistry<ReturnType, P1>()[methodName]= new CallRegistry<ReturnType, P1>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType, P1>()[methodName];
//		}
//
//		return new ActionBuilder<ReturnType, P1>(*this->GetRegistry<ReturnType, P1>()[methodName]);
//	}
//
//	template <class ReturnType, class Param1, class Param2>
//	ActionBuilder<ReturnType
//		, typename no_cref<Param1>::type
//		, typename no_cref<Param2>::type> *WhenCall(const std::string &methodName)
//	{
//		typedef no_cref<Param1>::type P1;
//		typedef no_cref<Param2>::type P2;
//		if (!alreadyExistsRegistryForMethod<ReturnType, P1, P2>(methodName)) {
//			this->GetRegistry<ReturnType, P1, P2>()[methodName]= new CallRegistry<ReturnType, P1, P2>(methodName);
//			this->regReg[methodName]= this->GetRegistry<ReturnType, P1, P2>()[methodName];
//		}
//
//		return new ActionBuilder<ReturnType, P1, P2>(*this->GetRegistry<ReturnType, P1, P2>()[methodName]);
//	}
//
//   template <class ReturnType, class Param1, class Param2, class Param3>
//   ActionBuilder<ReturnType
//      , typename no_cref<Param1>::type
//      , typename no_cref<Param2>::type
//      , typename no_cref<Param3>::type> *WhenCall(const std::string &methodName)
//   {
//      typedef no_cref<Param1>::type P1;
//      typedef no_cref<Param2>::type P2;
//      typedef no_cref<Param3>::type P3;
//      if (!alreadyExistsRegistryForMethod<ReturnType, P1, P2, P3>(methodName)) {
//         this->GetRegistry<ReturnType, P1, P2, P3>()[methodName]= new CallRegistry<ReturnType, P1, P2, P3>(methodName);
//         this->regReg[methodName]= this->GetRegistry<ReturnType, P1, P2, P3>()[methodName];
//      }
//
//      return new ActionBuilder<ReturnType, P1, P2, P3>(*this->GetRegistry<ReturnType, P1, P2, P3>()[methodName]);
//   }
//
//
//	/*void Verify()
//	{
//		CallIterator it= Begin();
//		for (; it != End(); it++)
//			it->second->Verify();	
//	}	*/
//
//	CallIterator Begin()
//	{
//		return regReg.begin();
//	}
//
//	CallIterator End()
//	{
//		return regReg.end();
//	}
//
//protected:
//	void clearCalls()
//	{	
//		CallIterator it= Begin();
//		for (; it != End(); it++)
//			delete it->second;
//	
//		regReg.clear();
//	}
//
//public:
//
//	template <class ReturnType>
//	static std::map<std::string, CallRegistry<ReturnType>*> &GetRegistry()
//	{
//		static std::map<std::string, CallRegistry<ReturnType>*> registry;
//		return registry;
//	}
//
//	template <class ReturnType, class P1>
//	static std::map<std::string, CallRegistry<ReturnType, P1>*> &GetRegistry()
//	{
//		static std::map<std::string, CallRegistry<ReturnType, P1>*> registry;
//		return registry;
//	}
//
//	template <class ReturnType, class P1, class P2>
//	static std::map<std::string, CallRegistry<ReturnType, P1, P2>*> &GetRegistry()
//	{
//		static std::map<std::string, CallRegistry<ReturnType, P1, P2>*> registry;
//		return registry;
//	}
//
//	template <class ReturnType, class P1, class P2, class P3>
//	static std::map<std::string, CallRegistry<ReturnType, P1, P2, P3>*> &GetRegistry()
//	{
//		static std::map<std::string, CallRegistry<ReturnType, P1, P2, P3>*> registry;
//		return registry;
//	}
//
//	template <class ReturnType, class P1, class P2, class P3, class P4>
//	static std::map<std::string, CallRegistry<ReturnType, P1, P2, P3, P4>*> &GetRegistry()
//	{
//		static std::map<std::string, CallRegistry<ReturnType, P1, P2, P3, P4>*> registry;
//		return registry;
//	}
//
//	template <class ReturnType, class P1, class P2, class P3, class P4, class P5>
//	static std::map<std::string, CallRegistry<ReturnType, P1, P2, P3, P4, P5>*> &GetRegistry()
//	{
//		static std::map<std::string, CallRegistry<ReturnType, P1, P2, P3, P4, p5>*> registry;
//		return registry;
//	}
//
//protected:
//	std::map<std::string, IRegistry*> regReg;	
};


#endif 