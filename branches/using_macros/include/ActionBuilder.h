#ifndef INCLUDED_ACTIONBUILDER_H
#define INCLUDED_ACTIONBUILDER_H

#include "IRegistry.h"
#include "NullType.h"

namespace carnamock {

template <class ReturnType= nulltype, class Param1= nulltype, class Param2= nulltype, class Param3= nulltype, class Param4= nulltype, class Param5= nulltype> 
class ActionBuilder;


template <class Derived>
class ActionBuilderBase 
{
public:
   typedef boost::shared_ptr<Derived> Ptr;
   virtual ~ActionBuilderBase() {}
};

// 0 arity
template <class ReturnType>
class ActionBuilder<ReturnType> : public ActionBuilderBase<ActionBuilder<ReturnType> >
{
public:
	ActionBuilder(
		IRegistry &_reg
	) : registry(_reg), actualAction(new CallAction<ReturnType>()) {}	

	ActionBuilder<ReturnType> &AllwaysReturn(ReturnType returns)
	{
		actualAction->SetReturn(returns);
		registry.AddAction(actualAction);
		return *this;
	}

   ActionBuilder<ReturnType> &AllwaysExecute(boost::function0<ReturnType> func)
   {
      actualAction->SetFunction(func);
      registry.AddAction(actualAction);
      return *this;
   }
private:
	CallAction<ReturnType> *actualAction;
	IRegistry &registry;
};

template <>
class ActionBuilder<void> : public ActionBuilderBase<ActionBuilder<void> >
{
public:
   ActionBuilder(
      IRegistry &_reg
      ) : registry(_reg), actualAction(new CallAction<void>()) {}	

   ActionBuilder<void> &AllwaysExecute(boost::function0<void> func)
   {
      actualAction->SetFunction(func);
      registry.AddAction(actualAction);
      return *this;
   }
private:
   CallAction<void> *actualAction;
   IRegistry &registry;
};

//1 arity

template <class ReturnType, class Param1>
class ActionBuilder<ReturnType, Param1> : public ActionBuilderBase<ActionBuilder<ReturnType, Param1> >
{
public:
	ActionBuilder(
		IRegistry &_reg
	) : registry(_reg), actualAction(new CallAction<ReturnType, Param1>()) 
	{
	}

	ActionBuilder<ReturnType, Param1> &WithParam(hamcrest::matcher<Param1> &matcher)
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

   ActionBuilder<ReturnType, Param1> &ThenExecute(boost::function1<ReturnType, Param1> func)
   {
      actualAction->SetFunction(func);
      registry.AddAction(actualAction);
      return *this;
   }

private:
	CallAction<ReturnType, Param1> *actualAction;
	IRegistry &registry;
};

template <class Param1>
class ActionBuilder<void, Param1> : public ActionBuilderBase<ActionBuilder<void, Param1> >
{
public:
   ActionBuilder(
      IRegistry &_reg
      ) : registry(_reg), actualAction(new CallAction<void, Param1>()) 
   {
   }

   ActionBuilder<void, Param1> &WithParam(hamcrest::matcher<Param1> &matcher)
   {
      actualAction->SetParam(matcher);
      return *this;
   }

   ActionBuilder<void, Param1> &ThenExecute(boost::function1<void, Param1> func)
   {
      actualAction->SetFunction(func);
      registry.AddAction(actualAction);
      return *this;
   }

private:
   CallAction<void, Param1> *actualAction;
   IRegistry &registry;
};

//2 arity

template <class ReturnType, class Param1, class Param2>
class ActionBuilder<ReturnType, Param1, Param2> 
   : public ActionBuilderBase<ActionBuilder<ReturnType, Param1, Param2> >
{
public:
	ActionBuilder(
		IRegistry &_reg
	) : registry(_reg), actualAction(new CallAction<ReturnType, Param1, Param2>()) 
	{
	}

	ActionBuilder<ReturnType, Param1, Param2> &WithParam(hamcrest::matcher<Param1> &matcher1
		, hamcrest::matcher<Param2> &matcher2)
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

   ActionBuilder<ReturnType, Param1, Param2> &ThenExecute(
      boost::function2<ReturnType, Param1, Param2> func)
   {
      actualAction->SetFunction(func);
      registry.AddAction(actualAction);
      return *this;
   }

private:
	CallAction<ReturnType, Param1, Param2> *actualAction;
	IRegistry &registry;
};

template <class Param1, class Param2>
class ActionBuilder<void, Param1, Param2> 
   : public ActionBuilderBase<ActionBuilder<void, Param1, Param2> >
{
public:
   ActionBuilder(
      IRegistry &_reg
      ) : registry(_reg), actualAction(new CallAction<void, Param1, Param2>()) 
   {
   }

   ActionBuilder<void, Param1, Param2> &WithParam(hamcrest::matcher<Param1> &matcher1
      , hamcrest::matcher<Param2> &matcher2)
   {
      actualAction->SetParam(matcher1, matcher2);
      return *this;
   }	   

   ActionBuilder<void, Param1, Param2> &ThenExecute(
      boost::function2<void, Param1, Param2> func)
   {
      actualAction->SetFunction(func);
      registry.AddAction(actualAction);
      return *this;
   }

private:
   CallAction<void, Param1, Param2> *actualAction;
   IRegistry &registry;
};

//3 arity

template <class ReturnType, class Param1, class Param2, class Param3>
class ActionBuilder<ReturnType, Param1, Param2, Param3>
   : public ActionBuilderBase<ActionBuilder<ReturnType, Param1, Param2, Param3> >
{
public:
	ActionBuilder(
		IRegistry &_reg
	) : registry(_reg), actualAction(new CallAction<ReturnType, Param1, Param2, Param3>()) 
	{
	}

	ActionBuilder<ReturnType, Param1, Param2, Param3> &WithParam(hamcrest::matcher<Param1> &matcher1
		, hamcrest::matcher<Param2> &matcher2
		, hamcrest::matcher<Param3> &matcher3)
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

   ActionBuilder<ReturnType, Param1, Param2, Param3> &ThenExecute(
      boost::function3<ReturnType, Param1, Param2, Param3> func)
   {
      actualAction->SetFunction(func);
      registry.AddAction(actualAction);
      return *this;
   }

private:
	CallAction<ReturnType, Param1, Param2, Param3> *actualAction;
	IRegistry &registry;
};


template <class Param1, class Param2, class Param3>
class ActionBuilder<void, Param1, Param2, Param3>
   : public ActionBuilderBase<ActionBuilder<void, Param1, Param2, Param3> >
{
public:
   ActionBuilder(
      IRegistry &_reg
      ) : registry(_reg), actualAction(new CallAction<ReturnType, Param1, Param2, Param3>()) {}

   ActionBuilder<void, Param1, Param2, Param3> &WithParam(hamcrest::matcher<Param1> &matcher1
      , hamcrest::matcher<Param2> &matcher2
      , hamcrest::matcher<Param3> &matcher3)
   {
      actualAction->SetParam(matcher1, matcher2, matcher3);
      return *this;
   }	

   ActionBuilder<void, Param1, Param2, Param3> &ThenExecute(
      boost::function3<void, Param1, Param2, Param3> func)
   {
      actualAction->SetFunction(func);
      registry.AddAction(actualAction);
      return *this;
   }

private:
   CallAction<void, Param1, Param2, Param3> *actualAction;
   IRegistry &registry;
};

//4 arity

template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
class ActionBuilder<ReturnType, Param1, Param2, Param3, Param4>
   : public ActionBuilderBase<ActionBuilder<ReturnType, Param1, Param2, Param3, Param4> >
{
public:
	ActionBuilder(
		IRegistry &_reg
	) : registry(_reg), actualAction(new CallAction<ReturnType, Param1, Param2, Param3, Param4>()) 
	{
	}

	ActionBuilder<ReturnType, Param1, Param2, Param3, Param4> &WithParam(
		hamcrest::matcher<Param1> &matcher1
		, hamcrest::matcher<Param2> &matcher2
		, hamcrest::matcher<Param3> &matcher3
		, hamcrest::matcher<Param4> &matcher4
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

   ActionBuilder<ReturnType, Param1, Param2, Param3, Param4> &ThenExecute(
      boost::function4<ReturnType, Param1, Param2, Param3, Param4> func)
   {
      actualAction->SetFunction(func);
      registry.AddAction(actualAction);
      return *this;
   }

private:
	CallAction<ReturnType, Param1, Param2, Param3, Param4> *actualAction;
	IRegistry &registry;
};


template <class Param1, class Param2, class Param3, class Param4>
class ActionBuilder<void, Param1, Param2, Param3, Param4>
   : public ActionBuilderBase<ActionBuilder<void, Param1, Param2, Param3, Param4> >
{
public:
   ActionBuilder(
      IRegistry &_reg
      ) : registry(_reg), actualAction(new CallAction<void, Param1, Param2, Param3, Param4>()) 
   {
   }

   ActionBuilder<void, Param1, Param2, Param3, Param4> &WithParam(
      hamcrest::matcher<Param1> &matcher1
      , hamcrest::matcher<Param2> &matcher2
      , hamcrest::matcher<Param3> &matcher3
      , hamcrest::matcher<Param4> &matcher4
      )
   {
      actualAction->SetParam(matcher1, matcher2, matcher3, matcher4);
      return *this;
   }	

   ActionBuilder<void, Param1, Param2, Param3, Param4> &ThenExecute(
      boost::function4<void, Param1, Param2, Param3, Param4> func)
   {
      actualAction->SetFunction(func);
      registry.AddAction(actualAction);
      return *this;
   }

private:
   CallAction<void, Param1, Param2, Param3, Param4> *actualAction;
   IRegistry &registry;
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
//		hamcrest::matcher<Param1> &matcher1
//		, hamcrest::matcher<Param2> &matcher2
//		, hamcrest::matcher<Param3> &matcher3
//		, hamcrest::matcher<Param4> &matcher4
//		, hamcrest::matcher<Param5> &matcher5
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

} // namespace carnamock

#endif 