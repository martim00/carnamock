#ifndef INCLUDED_CALLMATCHER_H
#define INCLUDED_CALLMATCHER_H

#include "NullType.h"
#include "ValueHolder.h"


template <class ReturnType=nulltype
, class Param1=nulltype
, class Param2=nulltype
, class Param3= nulltype
, class Param4=nulltype
, class Param5=nulltype> 
class CallMatcher;

template <class ReturnType>
class CallMatcher<ReturnType>
{
public:
	CallMatcher(CallRegistry<ReturnType> &_registry) : registry(_registry) {}

	CallMatcher &Times(size_t times)
	{
		for (unsigned i= 0; i < times; i++) {
			try {
				registry.GetNextCall()->Verified(true);
			} catch (std::runtime_error&)
			{
				std::runtime_error e("expectation falhou no numero de vezes");
				throw e;
			}
		}
		return *this;
	}

private:
	CallRegistry<ReturnType> &registry;
};

template <class ReturnType, class Param1>
class CallMatcher<ReturnType, Param1>
{
public:
	CallMatcher(CallRegistry<ReturnType, Param1> &_registry) : registry(_registry), parameterWasSetted(false) {}

	CallMatcher &Times(size_t times)
	{
		Call<ReturnType, Param1> *call= NULL;
		for (unsigned i= 0; i < times; i++) {
			try {
				call= registry.GetNextCall();
				if (parameterWasSetted) {
					if (*matcher1 != call->GetParam1() /*!= param1->GetValue()*/) {
						std::runtime_error e("expectation falhou");
						throw e;
					}
					call->Verified(true);
				}					
				
			} catch (std::runtime_error&)
			{
				//todo: setar log no registry para que nao precise verificar no destructor.

				registry.VerifyOnDestructor(false);
				std::runtime_error e("expectation falhou no numero de vezes");
				throw e;
			}
		}
		return *this;
	}

	CallMatcher &WithParams(Matcher<Param1> &p1)
	{
		//param1= new ValueHolder<Param1>(p1);
		/*actualParameter= &p1;*/
		matcher1= &p1;
		parameterWasSetted= true;
		return *this;
	}

private:
	CallRegistry<ReturnType, Param1> &registry;

	bool parameterWasSetted;
	//Param1 &actualParameter;
	//ValueHolder<Param1> *param1;
	Matcher<Param1> *matcher1;
};

//2 arity

template <class ReturnType, class Param1, class Param2>
class CallMatcher<ReturnType, Param1, Param2>
{
public:
	CallMatcher(CallRegistry<ReturnType, Param1, Param2> &_registry) 
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
				std::runtime_error e("expectation falhou no numero de vezes");
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
	CallRegistry<ReturnType, Param1, Param2> &registry;

	bool parameterWasSetted;
	Matcher<Param1> *matcher1;
	Matcher<Param2> *matcher2;
};


//3 arity

template <class ReturnType, class Param1, class Param2, class Param3>
class CallMatcher<ReturnType, Param1, Param2, Param3>
{
public:
	CallMatcher(CallRegistry<ReturnType, Param1, Param2, Param3> &_registry) 
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
				std::runtime_error e("expectation falhou no numero de vezes");
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
	CallRegistry<ReturnType, Param1, Param2, Param3> &registry;

	bool parameterWasSetted;
	Matcher<Param1> *matcher1;
	Matcher<Param2> *matcher2;
	Matcher<Param3> *matcher3;
};

//4 arity

template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
class CallMatcher<ReturnType, Param1, Param2, Param3, Param4>
{
public:
	CallMatcher(CallRegistry<ReturnType, Param1, Param2, Param3, Param4> &_registry) 
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
				std::runtime_error e("expectation falhou no numero de vezes");
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
	CallRegistry<ReturnType, Param1, Param2, Param3, Param4> &registry;

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