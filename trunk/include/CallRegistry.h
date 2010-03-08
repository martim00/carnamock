#pragma once
#ifndef INCLUDED_CALLREGISTRY_H
#define INCLUDED_CALLREGISTRY_H

#include "Call.h"
#include "NullType.h"
#include "CallAction.h"
#include "ExpectationBuilder.h"
#include "ActionBuilder.h"
#include "TypeTraits.h"

#include "IRegistry.h"
#include "FunctionTraits.h"

namespace carnamock {

template <class ReturnType=nulltype
, class Param1=nulltype
, class Param2=nulltype
, class Param3=nulltype
, class Param4=nulltype
, class Param5=nulltype
, class Param6=nulltype
, class Param7=nulltype
, class Param8=nulltype
, class Param9=nulltype
, class Param10=nulltype>
class CallRegistry;


template <class ReturnType>
class CallRegistry<ReturnType> : public IRegistry
{
public:
   enum { NrParams= 0 };

   typedef FunctionTraits<ReturnType> RegistryTraits;
   typedef CallRegistry<ReturnType> Type;
	
	virtual ~CallRegistry()	{}

	ReturnType Execute()
	{
      this->AddCall(new Call());
      if (!actions.empty()) {
         CallAction<RegistryTraits> *actionDerived= 
				dynamic_cast<CallAction<RegistryTraits>*>(actions[0].get());

         if (!RegistryTraits::IsVoidReturn::result) {
            return actionDerived->Execute();
         } else {
            actionDerived->Execute();
         }
      }

      if (!RegistryTraits::IsVoidReturn::result) {
         return ReturnType();
      }
	}

	typename ExpectationBuilder<Type>::Ptr Expect()
   {
      return ExpectationBuilder<Type>::Ptr(new ExpectationBuilder<Type>(*this));
   }

   typename ActionBuilder<Type, ReturnType, NrParams>::Ptr WhenCall()
   {
      return ActionBuilder<Type>::Ptr(new ActionBuilder<Type>(*this));
   }
};

template <class ReturnType, class P1>
class CallRegistry<ReturnType, P1> : public IRegistry
{
public:
   typedef typename no_cref<P1>::type Param1;
   typedef FunctionTraits<ReturnType, Param1> RegistryTraits;
	typedef CallRegistry<ReturnType, P1> Type;
   enum { NrParams= 1};
   
   virtual ~CallRegistry() {}

	typename ExpectationBuilder<Type>::Ptr Expect()
   {
      return ExpectationBuilder<Type>::Ptr(new ExpectationBuilder<Type>(*this));
   }

   typename ActionBuilder<Type, ReturnType, NrParams>::Ptr WhenCall()
   {
      return ActionBuilder<Type>::Ptr(new ActionBuilder<Type>(*this));
   }

	ReturnType Execute(typename RegistryTraits::Param1 p1)
	{
		Call *call= new Call();
		call->AddParam(new ValueHolder<Param1>(p1));
		this->AddCall(call);

		for (unsigned i= 0; i < actions.size(); i++)
		{
			CallAction<RegistryTraits> *action= dynamic_cast<CallAction<RegistryTraits>*>(actions[i].get());

         std::vector<IValueHolder*> params;
         params.push_back(new ValueHolder<Param1>(p1));

			if (action->KnowsThat(params)) {
            if (!RegistryTraits::IsVoidReturn::result) 
				   return action->Execute(p1);
            else 
               action->Execute(p1);
			}
			continue;
		}
      if (!RegistryTraits::IsVoidReturn::result)
		   return ReturnType();
	}	
};

//2 arity

template <class ReturnType, class P1, class P2>
class CallRegistry<ReturnType, P1, P2> : public IRegistry
{
public:
   typedef FunctionTraits<ReturnType, typename no_cref<P1>::type, typename no_cref<P2>::type> RegistryTraits;

   typedef typename no_cref<P1>::type Param1;
   typedef typename no_cref<P2>::type Param2;

	enum { NrParams= 2 };

	typedef CallRegistry<ReturnType, P1, P2> Type;

	virtual ~CallRegistry() {}   

	typename ExpectationBuilder<Type>::Ptr Expect()
   {
      return ExpectationBuilder<Type>::Ptr(new ExpectationBuilder<Type>(*this));
   }

   typename ActionBuilder<Type, ReturnType, NrParams>::Ptr WhenCall()
   {
      return ActionBuilder<Type>::Ptr(new ActionBuilder<Type>(*this));
   }


   ReturnType Execute(typename RegistryTraits::Param1 p1, typename RegistryTraits::Param2 p2)
	{
		Call *call= new Call();
		call->AddParam(new ValueHolder<Param1>(p1));
		call->AddParam(new ValueHolder<Param2>(p2));
		this->AddCall(call);
		for (unsigned i= 0; i < actions.size(); i++)
		{
			CallAction<RegistryTraits> *action= 
            dynamic_cast<CallAction<RegistryTraits>*>(actions[i].get());
         
         std::vector<IValueHolder*> params;
         params.push_back(new ValueHolder<Param1>(p1));
         params.push_back(new ValueHolder<Param2>(p2));

			if (action->KnowsThat(params)) {
            if (!RegistryTraits::IsVoidReturn::result)
				   return action->Execute(p1, p2);
            else 
               action->Execute(p1, p2);
			}
			continue;
		}
      if (!RegistryTraits::IsVoidReturn::result)
		   return ReturnType();
	}
};

//3 arity

template <class ReturnType, class P1, class P2, class P3>
class CallRegistry<ReturnType, P1, P2, P3> : public IRegistry
{
public:
   typedef FunctionTraits<ReturnType
      , typename no_cref<P1>::type
      , typename no_cref<P2>::type
      , typename no_cref<P3>::type> RegistryTraits;

	typedef typename no_cref<P1>::type Param1;
   typedef typename no_cref<P2>::type Param2;
	typedef typename no_cref<P3>::type Param3;
	enum { NrParams= 3 };

   typedef CallRegistry<ReturnType, Param1, Param2, Param3> Type;

	virtual ~CallRegistry() {}

	typename ExpectationBuilder<Type>::Ptr Expect()
   {
      return ExpectationBuilder<Type>::Ptr(new ExpectationBuilder<Type>(*this));
   }   

   typename ActionBuilder<Type, ReturnType, NrParams>::Ptr WhenCall()
   {
      return ActionBuilder<Type>::Ptr(new ActionBuilder<Type>(*this));
   }

   ReturnType Execute(
        typename RegistryTraits::Param1 p1
      , typename RegistryTraits::Param2 p2
      , typename RegistryTraits::Param3 p3)
	{
      Call *call= new Call();
      call->AddParam(new ValueHolder<Param1>(p1));
      call->AddParam(new ValueHolder<Param2>(p2));
      call->AddParam(new ValueHolder<Param3>(p3));
      this->AddCall(call);

		for (unsigned i= 0; i < actions.size(); i++)
		{
			CallAction<RegistryTraits> *action= 
            dynamic_cast<CallAction<RegistryTraits> *>(actions[i].get());

			if (action->KnowsThat(p1, p2, p3)) {
            if (!RegistryTraits::IsVoidReturn::result)
				   return action->Execute(p1, p2, p3);
            else 
               action->Execute(p1, p2, p3);
			}
			continue;
		}
      if (!RegistryTraits::IsVoidReturn::result)
		   return ReturnType();
	}	
};

//4 arity

template <class ReturnType, class P1, class P2, class P3, class P4>
class CallRegistry<ReturnType, P1, P2, P3, P4> : public IRegistry
{
public:
	typedef typename no_cref<P1>::type Param1;
   typedef typename no_cref<P2>::type Param2;
	typedef typename no_cref<P3>::type Param3;
	typedef typename no_cref<P4>::type Param4;
   enum { NrParams= 4 };

   typedef FunctionTraits<ReturnType
      , typename no_cref<P1>::type
      , typename no_cref<P2>::type
      , typename no_cref<P3>::type
      , typename no_cref<P4>::type> RegistryTraits;

   typedef CallRegistry<ReturnType, Param1, Param2, Param3, Param4> Type;

	virtual ~CallRegistry() {}

	typename ExpectationBuilder<Type>::Ptr Expect()
   {
      return ExpectationBuilder<Type>::Ptr(new ExpectationBuilder<Type>(*this));
   }

   typename ActionBuilder<Type, ReturnType, NrParams>::Ptr WhenCall()
   {
      return ActionBuilder<Type>::Ptr(new ActionBuilder<Type>(*this));
   }

   ReturnType Execute(Param1 p1, Param2 p2, Param3 p3, Param4 p4)
   {
      Call *call= new Call();
      call->AddParam(new ValueHolder<Param1>(p1));
      call->AddParam(new ValueHolder<Param2>(p2));
      call->AddParam(new ValueHolder<Param3>(p3));
      call->AddParam(new ValueHolder<Param4>(p4));
      this->AddCall(call);

		for (unsigned i= 0; i < actions.size(); i++)
		{
			CallAction<RegistryTraits> *action= 
            dynamic_cast<RegistryTraits> *>(actions[i].get());

			if (action->KnowsThat(p1, p2, p3, p4)) {
            if (!RegistryTraits::IsVoidReturn::result)
				   return action->Execute(p1, p2, p3, p4);
            else 
               action->Execute(p1, p2, p3, p4);
			}
			continue;
		}
      if (!RegistryTraits::IsVoidReturn::result)
		   return ReturnType();
	}	
};

} //namespace carnamock

#endif 