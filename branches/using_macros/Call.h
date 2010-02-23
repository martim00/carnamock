#ifndef INCLUDED_CALL_H
#define INCLUDED_CALL_H

#include "NullType.h"

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

protected:
	bool verified;
};

template <class ReturnType>
class Call<ReturnType> : public ICall
{
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