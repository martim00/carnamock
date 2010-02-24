#ifndef INCLUDED_CALL_H
#define INCLUDED_CALL_H

#include "NullType.h"
#include "ResultType.h"

template <class ReturnType=nulltype
, class Param1=nulltype
, class Param2=nulltype
, class Param3=nulltype
, class Param4=nulltype
, class Param5=nulltype> 
class Call;

class ICall
{
public:	
   virtual ~ICall() {}
	ICall() : verified(false) {}
	bool Verified() const
	{
		return verified;
	}

	void Verified(bool wasVerified)
	{
		verified= wasVerified;
	}

   virtual ResultType *Compare(ICall &)= 0;

protected:
	bool verified;
};

template <class ReturnType>
class Call<ReturnType> : public ICall
{
public:
   ResultType *Compare(ICall &_call)
   {      
      return NULL;
   }
};

//1 arity
template <class ReturnType, class Param1>
class Call<ReturnType, Param1> : public ICall
{
	Param1 param1;
public:
	Call(Param1 p1) : param1(p1) {}

	Param1 GetParam1() 
	{
		return param1; 
	}

   ResultType *Compare(ICall &_call)
   {
      Call<ReturnType, Matcher<Param1>* > *call= 
         dynamic_cast<Call<ReturnType, Matcher<Param1>*>*>(&_call);
      if (*call->GetParam1() != param1)
         return new ParameterIncorrect(1, "Incorrect parameter");
      return NULL;
   }
};

//2 arity
template <class ReturnType, class Param1, class Param2>
class Call<ReturnType, Param1, Param2> : public ICall
{
	Param1 param1;
	Param2 param2;

public:
	Call(Param1 p1, Param2 p2) : param1(p1), param2(p2) {}

	Param1 GetParam1() 
	{
		return param1; 
	}
	Param2 GetParam2() 
	{
		return param2;
	}

   ResultType *Compare(ICall &_call)
   {
      Call<ReturnType, Matcher<Param1>*, Matcher<Param2>*> *call= 
         dynamic_cast<Call<ReturnType, Matcher<Param1>*, Matcher<Param2>*>*>(&_call);
      if (*call->GetParam1() != param1)
         return new ParameterIncorrect(1, "Incorrect parameter");
      if (*call->GetParam2() != param2)
         return new ParameterIncorrect(2, "Incorrect parameter");
      return NULL;
   }
};

//3 arity
template <class ReturnType, class Param1, class Param2, class Param3>
class Call<ReturnType, Param1, Param2, Param3> : public ICall
{
	Param1 param1;
	Param2 param2;
	Param3 param3;
public:
	Call(Param1 p1, Param2 p2, Param3 p3) 
		: param1(p1)
		, param2(p2)
		, param3(p3)
	{}

	Param1 GetParam1() 
	{
		return param1; 
	}
	Param2 GetParam2() 
	{
		return param2; 
	}
	Param3 GetParam3() 
	{
		return param3; 
	}

   ResultType *Compare(ICall &_call)
   {
      Call<ReturnType, Matcher<Param1>*, Matcher<Param2>*, Matcher<Param3>*> *call= 
         dynamic_cast<Call<ReturnType, Matcher<Param1>*, Matcher<Param2>*, Matcher<Param3>*>*>(&_call);
      if (*call->GetParam1() != param1)
         return new ParameterIncorrect(1, "Incorrect parameter");
      if (*call->GetParam2() != param2)
         return new ParameterIncorrect(2, "Incorrect parameter");
      if (*call->GetParam3() != param3)
         return new ParameterIncorrect(3, "Incorrect parameter");
      return NULL;
   }
};

//4 arity
template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
class Call<ReturnType, Param1, Param2, Param3, Param4> : public ICall
{
	Param1 param1;
	Param2 param2;
	Param3 param3;
	Param4 param4;
public:
	Call(Param1 p1, Param2 p2, Param3 p3, Param4 p4) 
		: param1(p1)
		, param2(p2)
		, param3(p3)
		, param4(p4) 
	{}

	Param1 GetParam1() 
	{
		return param1; 
	}
	Param2 GetParam2() 
	{
		return param2; 
	}
	Param3 GetParam3() 
	{
		return param3; 
	}
	Param4 GetParam4() 
	{
		return param4; 
	}

   ResultType *Compare(ICall &_call)
   {
      Call<ReturnType, Matcher<Param1>*, Matcher<Param2>*, Matcher<Param3>*, Matcher<Param4>*> *call= 
         dynamic_cast<Call<ReturnType, Matcher<Param1>*, Matcher<Param2>*, Matcher<Param3>*, Matcher<Param4>*>*>(&_call);
      if (*call->GetParam1() != param1)
         return new ParameterIncorrect(1, "Incorrect parameter");
      if (*call->GetParam2() != param2)
         return new ParameterIncorrect(2, "Incorrect parameter");
      if (*call->GetParam3() != param3)
         return new ParameterIncorrect(3, "Incorrect parameter");
      if (*call->GetParam4() != param4)
         return new ParameterIncorrect(4, "Incorrect parameter");
      return NULL;
   }
};
//
////5 arity
//template <class ReturnType, class Param1, class Param2, class Param3, class Param4, class Param5>
//class Call<ReturnType, Param1, Param2, Param3, Param4, Param5> : public ICall
//{
//	Param1 param1;
//	Param2 param2;
//	Param3 param3;
//	Param4 param4;
//	Param5 param5;
//public:
//	Call(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) 
//		: param1(p1)
//		, param2(p2)
//		, param3(p3)
//		, param4(p4) 
//		, param5(p5) 
//	{}
//
//	Param1 GetParam1() 
//	{
//		return param1; 
//	}
//	Param2 GetParam2() 
//	{
//		return param2; 
//	}
//	Param3 GetParam3() 
//	{
//		return param3; 
//	}
//	Param4 GetParam4() 
//	{
//		return param4; 
//	}
//	Param5 GetParam5() 
//	{
//		return param5; 
//	}
//};


//template <class ReturnType, class Param1>
//class Call<ReturnType, const Param1&> : public ICall
//{
//	Param1 param1;
//public:
//	Call(Param1 p1) : param1(p1) {}
//
//	/*Call<ReturnType, Param1>& WithParam(Param1 p1)
//	{
//		param1= p1;
//		return *this;
//	}	*/
//
//	Param1 GetParam1() 
//	{
//		return param1; 
//	}
//};


#endif 