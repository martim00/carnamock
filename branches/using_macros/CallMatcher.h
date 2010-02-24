#pragma once
#ifndef INCLUDED_CALLMATCHER_H
#define INCLUDED_CALLMATCHER_H

#include "NullType.h"
#include "ValueHolder.h"
#include "Matcher.h"
#include <boost/shared_ptr.hpp>
#include "IRegistry.h"


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
   virtual ~CallMatcherBase() {}
};


template <class ReturnType>
class CallMatcher<ReturnType> : public CallMatcherBase<CallMatcher<ReturnType>>
{
public:
	CallMatcher(IRegistry &_registry) : registry(_registry) {}

	CallMatcher &Times(size_t times)
	{
		for (unsigned i= 0; i < times; i++) {
			try {
				registry.GetNextCall()->Verified(true);
			} catch (std::runtime_error&)
			{
            std::stringstream ss;
            ss << "Expectation do metodo " <<  registry.MethodName() << "falhou no numero de vezes\n";
            ss << "Era(m) esperada(s) " << times << " vez(es).\n";
            ss << "Fora(m) chamada(s) " << registry.GetTimesCalled() << " vez(es).\n";

				std::runtime_error e(ss.str());
				throw e;
			}
		}
		return *this;
	}

private:
	IRegistry &registry;
};

template <class ReturnType, class Param1>
class CallMatcher<ReturnType, Param1> : public CallMatcherBase<CallMatcher<ReturnType, Param1>>
{
public:
	CallMatcher(IRegistry &_registry) : registry(_registry), parameterWasSetted(false) {}

	CallMatcher &Times(size_t times)
	{
		Call<ReturnType, Param1> *call= NULL;
		for (unsigned i= 0; i < times; i++) {

			try {
				call= dynamic_cast<Call<ReturnType, Param1> *>(registry.GetNextCall());
			} catch (std::runtime_error&) {
				registry.SetResult(new TimesIncorrect(registry.TimesVerified(), registry.GetTimesCalled()));
				break;
			}

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
		return *this;
	}

	CallMatcher &WithParams(Matcher<Param1> &p1)
	{
		matcher1= &p1;
		parameterWasSetted= true;
		return *this;
	}

private:
	IRegistry &registry;
	bool parameterWasSetted;
	Matcher<Param1> *matcher1;
};

//2 arity

template <class ReturnType, class Param1, class Param2>
class CallMatcher<ReturnType, Param1, Param2> : public CallMatcherBase<CallMatcher<ReturnType, Param1, Param2>>
{
public:
	CallMatcher(IRegistry &_registry) 
		: registry(_registry), parameterWasSetted(false) {}

	CallMatcher &Times(size_t times)
	{
		Call<ReturnType, Param1, Param2> *call= NULL;
		for (unsigned i= 0; i < times; i++) {
			try {
				call= registry.GetNextCall();
				if (parameterWasSetted) {
					if (*matcher1 == call->GetParam1() && *matcher2 == call->GetParam2()) {
						call->Verified(true);	
					} else {
						std::runtime_error e("expectation falhou");
						throw e;
					}					
				}					
				
			} catch (std::runtime_error&)
			{
				//todo: setar log no registry para que nao precise verificar no destructor.

				registry.VerifyOnDestructor(false);
            std::stringstream ss;
            ss << "Expectation do metodo " <<  registry.MethodName() << "falhou no numero de vezes\n";
            ss << "Era(m) esperada(s) " << times << " vez(es).\n";
            ss << "Fora(m) chamada(s) " << registry.GetTimesCalled() << " vez(es).\n";

            std::runtime_error e(ss.str());
            throw e;
			}
		}
		return *this;
	}

	CallMatcher &WithParams(Matcher<Param1> &p1, Matcher<Param2> &p2)
	{
		matcher1= &p1;
		matcher2= &p2;
		parameterWasSetted= true;
		return *this;
	}

private:
	IRegistry &registry;

	bool parameterWasSetted;
	Matcher<Param1> *matcher1;
	Matcher<Param2> *matcher2;
};


//3 arity

template <class ReturnType, class Param1, class Param2, class Param3>
class CallMatcher<ReturnType, Param1, Param2, Param3> : public CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3>>
{
public:
	CallMatcher(IRegistry &_registry) 
		: registry(_registry), parameterWasSetted(false) {}

	CallMatcher &Times(size_t times)
	{
		Call<ReturnType, Param1, Param2, Param3> *call= NULL;
		for (unsigned i= 0; i < times; i++) {
			try {
				call= registry.GetNextCall();
				if (parameterWasSetted) {
					if (*matcher1 == call->GetParam1() && *matcher2 == call->GetParam2() && *matcher3 == call->GetParam3()) 
					{
						call->Verified(true);
					} else {
						std::runtime_error e("expectation falhou");
						throw e;
					}					
				}					
				
			} catch (std::runtime_error&)
			{
				//todo: setar log no registry para que nao precise verificar no destructor.

				registry.VerifyOnDestructor(false);
            std::stringstream ss;
            ss << "Expectation do metodo " <<  registry.MethodName() << "falhou no numero de vezes\n";
            ss << "Era(m) esperada(s) " << times << " vez(es).\n";
            ss << "Fora(m) chamada(s) " << registry.GetTimesCalled() << " vez(es).\n";

            std::runtime_error e(ss.str());
            throw e;
			}
		}
		return *this;
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
	IRegistry &registry;

	bool parameterWasSetted;
	Matcher<Param1> *matcher1;
	Matcher<Param2> *matcher2;
	Matcher<Param3> *matcher3;
};

//4 arity

template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
class CallMatcher<ReturnType, Param1, Param2, Param3, Param4> : public CallMatcherBase<CallMatcher<ReturnType, Param1, Param2, Param3, Param4>>
{
public:
	CallMatcher(IRegistry &_registry) 
		: registry(_registry), parameterWasSetted(false) {}

	CallMatcher &Times(size_t times)
	{
		Call<ReturnType, Param1, Param2, Param3, Param4> *call= NULL;
		for (unsigned i= 0; i < times; i++) {
			try {
				call= registry.GetNextCall();
				if (parameterWasSetted) {
					if (*matcher1 == call->GetParam1() 
						&& *matcher2 == call->GetParam2() 
						&& *matcher3 == call->GetParam3()
						&& *matcher4 == call->GetParam4()) 
					{
						call->Verified(true);	
					} else {
						std::runtime_error e("expectation falhou");
						throw e;
					}					
				}					
				
			} catch (std::runtime_error&)
			{
				//todo: setar log no registry para que nao precise verificar no destructor.

				registry.VerifyOnDestructor(false);
            std::stringstream ss;
            ss << "Expectation do metodo " <<  registry.MethodName() << "falhou no numero de vezes\n";
            ss << "Era esperado " << times << " vez(es).\n";
            ss << "Foi chamado " << registry.GetTimesCalled() << " vez(es).\n";

            std::runtime_error e(ss.str());
            throw e;
			}
		}
		return *this;
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
	IRegistry &registry;

	bool parameterWasSetted;
	Matcher<Param1> *matcher1;
	Matcher<Param2> *matcher2;
	Matcher<Param3> *matcher3;
	Matcher<Param4> *matcher4;
};

//
////5 arity
//
//template <class ReturnType, class Param1, class Param2, class Param3, class Param4, class Param5>
//class CallMatcher<ReturnType, Param1, Param2, Param3, Param4, Param5>
//{
//public:
//	CallMatcher(CallRegistry<ReturnType, Param1, Param2, Param3, Param4, Param5> &_registry) 
//		: registry(_registry), parameterWasSetted(false) {}
//
//	CallMatcher &Times(size_t times)
//	{
//		Call<ReturnType, Param1, Param2, Param3, Param4, Param5> *call= NULL;
//		for (unsigned i= 0; i < times; i++) {
//			try {
//				call= registry.GetNextCall();
//				if (parameterWasSetted) {
//					if (
//						*matcher1 == call->GetParam1() 
//						&& *matcher2 == call->GetParam2() 
//						&& *matcher3 == call->GetParam3()
//						&& *matcher4 == call->GetParam4()
//						&& *matcher5 == call->GetParam5()
//					) 
//					{
//						call->Verified(true);	
//					} else {
//						std::runtime_error e("expectation falhou");
//						throw e;
//					}					
//				}					
//				
//			} catch (std::runtime_error&)
//			{
//				//todo: setar log no registry para que nao precise verificar no destructor.
//
//				registry.VerifyOnDestructor(false);
//				std::runtime_error e("expectation falhou no numero de vezes");
//				throw e;
//			}
//		}
//		return *this;
//	}
//
//	CallMatcher &WithParams(Matcher<Param1> &p1, Matcher<Param2> &p2, Matcher<Param3> &p3, Matcher<Param4> &p4, Matcher<Param5> &p5)
//	{
//		matcher1= &p1;
//		matcher2= &p2;
//		matcher3= &p3;
//		matcher4= &p4;
//		matcher5= &p5;
//		parameterWasSetted= true;
//		return *this;
//	}
//
//private:
//	CallRegistry<ReturnType, Param1, Param2, Param3, Param4, Param5> &registry;
//
//	bool parameterWasSetted;
//	Matcher<Param1> *matcher1;
//	Matcher<Param2> *matcher2;
//	Matcher<Param3> *matcher3;
//	Matcher<Param4> *matcher4;
//	Matcher<Param5> *matcher5;
//};

#endif 