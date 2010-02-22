#ifndef INCLUDED_ACTIONBUILDER_H
#define INCLUDED_ACTIONBUILDER_H

#include "CallRegistry.h"
#include "NullType.h"

template <class ReturnType= nulltype, class Param1= nulltype, class Param2= nulltype, class Param3= nulltype, class Param4= nulltype, class Param5= nulltype> 
class ActionBuilder;

template <class ReturnType>
class ActionBuilder<ReturnType>
{
public:
	ActionBuilder(
		CallRegistry<ReturnType> &_reg
	) : registry(_reg), actualAction(new CallAction<ReturnType>()) {}	

	ActionBuilder<ReturnType> &AllwaysReturn(ReturnType returns)
	{
		actualAction->SetReturn(returns);
		registry.AddAction(actualAction);
		return *this;
	}

private:
	CallAction<ReturnType> *actualAction;
	CallRegistry<ReturnType> &registry;
};


template <class ReturnType, class Param1>
class ActionBuilder<ReturnType, Param1>
{
public:
	ActionBuilder(
		CallRegistry<ReturnType, Param1> &_reg
	) : registry(_reg), actualAction(new CallAction<ReturnType, Param1>()) 
	{
	}

	ActionBuilder<ReturnType, Param1> &WithParam(Matcher<Param1> &matcher)
	{
		actualAction->SetParam(matcher);
		return *this;
	}	

	ActionBuilder<ReturnType, Param1> &ThenReturn(ReturnType returns)
	{
		actualAction->SetReturn(returns);
		registry.AddAction(actualAction);
		return *this;
	}

private:
	CallAction<ReturnType, Param1> *actualAction;
	CallRegistry<ReturnType, Param1> &registry;
};

//2 arity

template <class ReturnType, class Param1, class Param2>
class ActionBuilder<ReturnType, Param1, Param2>
{
public:
	ActionBuilder(
		CallRegistry<ReturnType, Param1, Param2> &_reg
	) : registry(_reg), actualAction(new CallAction<ReturnType, Param1, Param2>()) 
	{
	}

	ActionBuilder<ReturnType, Param1, Param2> &WithParam(Matcher<Param1> &matcher1
		, Matcher<Param2> &matcher2)
	{
		actualAction->SetParam(matcher1, matcher2);
		return *this;
	}	

	ActionBuilder<ReturnType, Param1, Param2> &ThenReturn(ReturnType returns)
	{
		actualAction->SetReturn(returns);
		registry.AddAction(actualAction);
		return *this;
	}

private:
	CallAction<ReturnType, Param1, Param2> *actualAction;
	CallRegistry<ReturnType, Param1, Param2> &registry;
};

//3 arity

template <class ReturnType, class Param1, class Param2, class Param3>
class ActionBuilder<ReturnType, Param1, Param2, Param3>
{
public:
	ActionBuilder(
		CallRegistry<ReturnType, Param1, Param2, Param3> &_reg
	) : registry(_reg), actualAction(new CallAction<ReturnType, Param1, Param2, Param3>()) 
	{
	}

	ActionBuilder<ReturnType, Param1, Param2, Param3> &WithParam(Matcher<Param1> &matcher1
		, Matcher<Param2> &matcher2
		, Matcher<Param3> &matcher3)
	{
		actualAction->SetParam(matcher1, matcher2, matcher3);
		return *this;
	}	

	ActionBuilder<ReturnType, Param1, Param2, Param3> &ThenReturn(ReturnType returns)
	{
		actualAction->SetReturn(returns);
		registry.AddAction(actualAction);
		return *this;
	}

private:
	CallAction<ReturnType, Param1, Param2, Param3> *actualAction;
	CallRegistry<ReturnType, Param1, Param2, Param3> &registry;
};

//4 arity

template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
class ActionBuilder<ReturnType, Param1, Param2, Param3, Param4>
{
public:
	ActionBuilder(
		CallRegistry<ReturnType, Param1, Param2, Param3, Param4> &_reg
	) : registry(_reg), actualAction(new CallAction<ReturnType, Param1, Param2, Param3, Param4>()) 
	{
	}

	ActionBuilder<ReturnType, Param1, Param2, Param3, Param4> &WithParam(
		Matcher<Param1> &matcher1
		, Matcher<Param2> &matcher2
		, Matcher<Param3> &matcher3
		, Matcher<Param4> &matcher4
		)
	{
		actualAction->SetParam(matcher1, matcher2, matcher3, matcher4);
		return *this;
	}	

	ActionBuilder<ReturnType, Param1, Param2, Param3, Param4> &ThenReturn(ReturnType returns)
	{
		actualAction->SetReturn(returns);
		registry.AddAction(actualAction);
		return *this;
	}

private:
	CallAction<ReturnType, Param1, Param2, Param3, Param4> *actualAction;
	CallRegistry<ReturnType, Param1, Param2, Param3, Param4> &registry;
};
//
////5 arity
//
//template <class ReturnType, class Param1, class Param2, class Param3, class Param4, class Param5>
//class ActionBuilder<ReturnType, Param1, Param2, Param3, Param4, Param5>
//{
//public:
//	ActionBuilder(
//		CallRegistry<ReturnType, Param1, Param2, Param3, Param4, Param5> &_reg
//	) : registry(_reg), actualAction(new CallAction<ReturnType, Param1, Param2, Param3, Param4, Param5>()) 
//	{
//	}
//
//	ActionBuilder<ReturnType, Param1, Param2, Param3, Param4, Param5> &WithParam(
//		Matcher<Param1> &matcher1
//		, Matcher<Param2> &matcher2
//		, Matcher<Param3> &matcher3
//		, Matcher<Param4> &matcher4
//		, Matcher<Param5> &matcher5
//		)
//	{
//		actualAction->SetParam(matcher1, matcher2, matcher3, matcher4);
//		return *this;
//	}	
//
//	ActionBuilder<ReturnType, Param1, Param2, Param3, Param4, Param5> &ThenReturn(ReturnType returns)
//	{
//		actualAction->SetReturn(returns);
//		registry.AddAction(actualAction);
//		return *this;
//	}
//
//private:
//	CallAction<ReturnType, Param1, Param2, Param3, Param4, Param5> *actualAction;
//	CallRegistry<ReturnType, Param1, Param2, Param3, Param4, Param5> &registry;
//};

#endif 