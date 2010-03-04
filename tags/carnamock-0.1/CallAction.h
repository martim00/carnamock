#ifndef INCLUDED_CALLACTION_H
#define INCLUDED_CALLACTION_H

#include "Matcher.h"

template <class ReturnType= nulltype
, class Param1= nulltype
, class Param2= nulltype
, class Param3=nulltype
, class Param4=nulltype
, class Param5=nulltype> 
class CallAction;

template <class ReturnType>
class CallAction<ReturnType>
{
	ReturnType returns;
public:
	ReturnType Execute()
	{
		return returns;
	}

	ReturnType GetReturn() { return returns; }

	void SetReturn(ReturnType _returns)
	{
		returns= _returns;
	}
};

template <>
class CallAction<void>
{
public:	
	void Execute()
	{
	}
};


template <class ReturnType, class Param1>
class CallAction<ReturnType, Param1>
{
	ReturnType returns;
	Matcher<Param1> *matcher;
public:	
	bool KnowsThat(Param1 p1)
	{
		return (*matcher == p1);
	}

	ReturnType Execute(Param1 p1)
	{
		return returns;
	}

	void SetParam(Matcher<Param1> &p1)
	{
		matcher= &p1;
	}

	void SetReturn(ReturnType _returns)
	{
		returns= _returns;
	}
};


template <class Param1>
class CallAction<void, Param1>
{
	Matcher<Param1> *matcher;
public:	
	bool KnowsThat(Param1 p1)
	{
		return (*matcher == p1);
	}

	void Execute(Param1 p1)
	{
	}

	void SetParam(Matcher<Param1> &p1)
	{
		matcher= &p1;
	}
};


//2 arity

template <class ReturnType, class Param1, class Param2>
class CallAction<ReturnType, Param1, Param2>
{
	ReturnType returns;
	Matcher<Param1> *matcher1;
	Matcher<Param2> *matcher2;
public:	
	bool KnowsThat(Param1 p1, Param2 p2)
	{
		return (*matcher1 == p1) && (*matcher2 == p2);
	}

	ReturnType Execute(Param1 p1, Param2 p2)
	{
		return returns;
	}

	void SetParam(Matcher<Param1> &p1, Matcher<Param2> &p2)
	{
		matcher1= p1.Clone();
		matcher2= p2.Clone();
	}

	void SetReturn(ReturnType _returns)
	{
		returns= _returns;
	}
};

template <class Param1, class Param2>
class CallAction<void, Param1, Param2>
{
	Matcher<Param1> *matcher1;
	Matcher<Param2> *matcher2;
public:	
	bool KnowsThat(Param1 p1, Param2 p2)
	{
		return (*matcher1 == p1) && (*matcher2 == p2);
	}

	void Execute(Param1 p1, Param2 p2)
	{
	}

	void SetParam(Matcher<Param1> &p1, Matcher<Param2> &p2)
	{
		matcher1= p1.Clone();
		matcher2= p2.Clone();
	}
};


//3 arity

template <class ReturnType, class Param1, class Param2, class Param3>
class CallAction<ReturnType, Param1, Param2, Param3>
{
	ReturnType returns;
	Matcher<Param1> *matcher1;
	Matcher<Param2> *matcher2;
	Matcher<Param3> *matcher3;
public:	
	bool KnowsThat(Param1 p1, Param2 p2, Param3 p3)
	{
		return (*matcher1 == p1) && (*matcher == p2) && (*matcher3 == p3);
	}

	ReturnType Execute(Param1 p1, Param2 p2, Param3 p3)
	{
		return returns;
	}

	void SetParam(Matcher<Param1> &p1, Matcher<Param2> &p2, Matcher<Param3> &p3)
	{
		matcher1= &p1;
		matcher2= &p2;
		matcher3= &p3;
	}

	void SetReturn(ReturnType _returns)
	{
		returns= _returns;
	}
};

//4 arity

template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
class CallAction<ReturnType, Param1, Param2, Param3, Param4>
{
	ReturnType returns;
	Matcher<Param1> *matcher1;
	Matcher<Param2> *matcher2;
	Matcher<Param3> *matcher3;
	Matcher<Param4> *matcher4;
public:	
	bool KnowsThat(Param1 p1, Param2 p2, Param3 p3, Param4 p4)
	{
		return (*matcher1 == p1) && (*matcher == p2) && (*matcher3 == p3) && (*matcher4 == p4);
	}

	ReturnType Execute(Param1 p1, Param2 p2, Param3 p3, Param4 p4)
	{
		return returns;
	}

	void SetParam(Matcher<Param1> &p1, Matcher<Param2> &p2, Matcher<Param3> &p3, Matcher<Param4> &p4)
	{
		matcher1= &p1;
		matcher2= &p2;
		matcher3= &p3;
		matcher4= &p4;
	}

	void SetReturn(ReturnType _returns)
	{
		returns= _returns;
	}
};
//
////5 arity
//
//template <class ReturnType, class Param1, class Param2, class Param3, class Param4, class Param5>
//class CallAction<ReturnType, Param1, Param2, Param3, Param4, Param5>
//{
//	ReturnType returns;
//	Matcher<Param1> *matcher1;
//	Matcher<Param2> *matcher2;
//	Matcher<Param3> *matcher3;
//	Matcher<Param4> *matcher4;
//	Matcher<Param5> *matcher5;
//public:	
//	bool KnowsThat(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)
//	{
//		return (*matcher1 == p1) && (*matcher == p2) && (*matcher3 == p3) && (*matcher4 == p4) && (*matcher5 == p5);
//	}
//
//	ReturnType Execute(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)
//	{
//		return returns;
//	}
//
//	void SetParam(Matcher<Param1> &p1, Matcher<Param2> &p2, Matcher<Param3> &p3, Matcher<Param4> &p4, Matcher<Param5> p5)
//	{
//		matcher1= &p1;
//		matcher2= &p2;
//		matcher3= &p3;
//		matcher4= &p4;
//		matcher5= &p5;
//	}
//
//	void SetReturn(ReturnType _returns)
//	{
//		returns= _returns;
//	}
//};

//
//template <class ReturnType, class Param1>
//class CallAction<ReturnType, Param1&>
//{
//	Param1 param1;
//	ReturnType returns;
//public:
//
//	Param1 GetParam() { return param1; }
//	ReturnType GetReturn() { return returns; }
//	void SetParam(Param1 p1)
//	{
//		param1= p1;
//	}
//
//	void SetReturn(ReturnType _returns)
//	{
//		returns= _returns;
//	}
//};


#endif