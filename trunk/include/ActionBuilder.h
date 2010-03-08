#ifndef INCLUDED_ACTIONBUILDER_H
#define INCLUDED_ACTIONBUILDER_H

#include "IRegistry.h"
#include "NullType.h"

#include <boost/shared_ptr.hpp>

namespace carnamock {   

   //with parameters and return
   template <class RegistryType
      , class ReturnType= typename RegistryType::RegistryTraits::ReturnType
      , int NrParams= RegistryType::NrParams >
   class ActionBuilder 
   {
   public:
      typedef boost::shared_ptr<ActionBuilder<RegistryType, ReturnType, NrParams> > Ptr;

      ActionBuilder(
         RegistryType &_reg
         ) : registry(_reg), actualAction(new CallAction<typename RegistryType::RegistryTraits>()) {}
      
      template <class Param1>
      ActionBuilder<RegistryType, ReturnType, NrParams> &WithParam(const hamcrest::matcher<Param1> &matcher)
      {
         BOOST_STATIC_ASSERT(RegistryType::RegistryTraits::NrParams == 1);
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param1, Param1>::value));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(matcher.copy()));
         return *this;
      }

      template <class Param1, class Param2>
      ActionBuilder<RegistryType, ReturnType, NrParams> &WithParams(
         const hamcrest::matcher<Param1> &matcher1
         , const hamcrest::matcher<Param2> &matcher2)
      {
         BOOST_STATIC_ASSERT(RegistryType::RegistryTraits::NrParams == 2);
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param1, Param1>::value));
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param2, Param2>::value));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(matcher1.copy()));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param2>, Param2>(matcher2.copy()));
         return *this;
      }

      template <class Param1, class Param2, class Param3>
      ActionBuilder<RegistryType, ReturnType, NrParams> &WithParams(
         const hamcrest::matcher<Param1> &matcher1
         , const hamcrest::matcher<Param2> &matcher2
         , const hamcrest::matcher<Param3> &matcher3)
      {
         BOOST_STATIC_ASSERT(RegistryType::RegistryTraits::NrParams == 3);
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param1, Param1>::value));
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param2, Param2>::value));
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param3, Param3>::value));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(matcher1.copy()));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param2>, Param2>(matcher2.copy()));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param3>, Param3>(matcher3.copy()));
         return *this;
      }

      template <class Param1, class Param2, class Param3, class Param4>
      ActionBuilder<RegistryType, ReturnType, NrParams> &WithParams(
         const hamcrest::matcher<Param1> &matcher1
         , const hamcrest::matcher<Param2> &matcher2
         , const hamcrest::matcher<Param3> &matcher3
         , const hamcrest::matcher<Param4> &matcher4)
      {
         BOOST_STATIC_ASSERT(RegistryType::RegistryTraits::NrParams == 4);
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param1, Param1>::value));
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param2, Param2>::value));
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param3, Param3>::value));
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param4, Param4>::value));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(matcher1.copy()));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param2>, Param2>(matcher2.copy()));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param3>, Param3>(matcher3.copy()));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param4>, Param4>(matcher4.copy()));
         return *this;
      }

      template <class ReturnType>
      ActionBuilder<RegistryType, ReturnType, NrParams> &ThenReturn(ReturnType returns)
      {
         BOOST_STATIC_ASSERT((!boost::is_same<void, ReturnType>::value));
         actualAction->SetReturn(returns);
         registry.AddAction(actualAction);
         return *this;
      }

      ActionBuilder<RegistryType, ReturnType, NrParams> &ThenExecute(typename RegistryType::RegistryTraits::FunctionType func)
      {
         actualAction->SetFunction(func);
         registry.AddAction(actualAction);
         return *this;
      }

   private:
      CallAction<typename RegistryType::RegistryTraits> *actualAction;
      RegistryType &registry;    
   };

   //no return, no parameter
   template <class RegistryType>
   class ActionBuilder<RegistryType, void, 0> 
   {
   public:
      typedef boost::shared_ptr<ActionBuilder<RegistryType, void, 0> > Ptr;

      ActionBuilder(
         RegistryType &_reg
         ) : registry(_reg), actualAction(new CallAction<typename RegistryType::RegistryTraits>()) 
      {
      }      

      ActionBuilder<RegistryType, void, 0> &AllwaysExecute(typename RegistryType::RegistryTraits::FunctionType func)
      {
         actualAction->SetFunction(func);
         registry.AddAction(actualAction);
         return *this;
      }

   private:
      CallAction<typename RegistryType::RegistryTraits> *actualAction;
      RegistryType &registry;    
   };


   //no return with parameters
   template <class RegistryType, int NrParams>
   class ActionBuilder<RegistryType, void, NrParams> 
   {
   public:
      typedef boost::shared_ptr<ActionBuilder<RegistryType, void, NrParams> > Ptr;

      ActionBuilder(
         RegistryType &_reg
         ) : registry(_reg), actualAction(new CallAction<typename RegistryType::RegistryTraits>()) 
      {
      }

      template <class Param1>
      ActionBuilder<RegistryType, void, NrParams> &WithParam(const hamcrest::matcher<Param1> &matcher)
      {
         BOOST_STATIC_ASSERT(RegistryType::RegistryTraits::NrParams == 1);
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param1, Param1>::value));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(matcher.copy()));
         return *this;
      }

      template <class Param1, class Param2>
      ActionBuilder<RegistryType, void, NrParams> &WithParams(
         const hamcrest::matcher<Param1> &matcher1
         , const hamcrest::matcher<Param2> &matcher2)
      {
         BOOST_STATIC_ASSERT(RegistryType::RegistryTraits::NrParams == 2);
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param1, Param1>::value));
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param2, Param2>::value));         
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(matcher1.copy()));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param2>, Param2>(matcher2.copy()));
         return *this;
      }

      template <class Param1, class Param2, class Param3>
      ActionBuilder<RegistryType, void, NrParams> &WithParams(
         const hamcrest::matcher<Param1> &matcher1
         , const hamcrest::matcher<Param2> &matcher2
         , const hamcrest::matcher<Param3> &matcher3)
      {
         BOOST_STATIC_ASSERT(RegistryType::RegistryTraits::NrParams == 3);
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param1, Param1>::value));
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param2, Param2>::value));
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param3, Param3>::value));         
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(matcher1.copy()));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param2>, Param2>(matcher2.copy()));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param3>, Param3>(matcher3.copy()));
         return *this;
      }

      template <class Param1, class Param2, class Param3, class Param4>
      ActionBuilder<RegistryType, void, NrParams> &WithParams(
         const hamcrest::matcher<Param1> &matcher1
         , const hamcrest::matcher<Param2> &matcher2
         , const hamcrest::matcher<Param3> &matcher3
         , const hamcrest::matcher<Param4> &matcher4)
      {
         BOOST_STATIC_ASSERT(RegistryType::RegistryTraits::NrParams == 4);
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param1, Param1>::value));
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param2, Param2>::value));
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param3, Param3>::value));
         BOOST_STATIC_ASSERT((boost::is_same<typename RegistryType::Param4, Param4>::value));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param1>, Param1>(matcher1.copy()));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param2>, Param2>(matcher2.copy()));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param3>, Param3>(matcher3.copy()));
         actualAction->AddParam(new IMatcherWrapper<hamcrest::matcher<Param4>, Param4>(matcher4.copy()));
         return *this;
      }

      ActionBuilder<RegistryType, void, NrParams> &ThenExecute(
         typename RegistryType::RegistryTraits::FunctionType func)
      {
         actualAction->SetFunction(func);
         registry.AddAction(actualAction);
         return *this;
      }

   private:
      CallAction<typename RegistryType::RegistryTraits> *actualAction;
      RegistryType &registry;
   };

   //with return and no parameter
   template <class RegistryType, class ReturnType>
   class ActionBuilder<RegistryType, ReturnType, 0> 
   {
   public:
      typedef boost::shared_ptr<ActionBuilder<RegistryType, ReturnType, 0> > Ptr;

      ActionBuilder(
         RegistryType &_reg
         ) : registry(_reg), actualAction(new CallAction<typename RegistryType::RegistryTraits>()) 
      {
      }      

      template <class ReturnType>
      ActionBuilder<RegistryType, ReturnType, 0> &AllwaysReturn(ReturnType returns)
      {
         BOOST_STATIC_ASSERT((!boost::is_same<void, ReturnType>::value));
         actualAction->SetReturn(returns);
         registry.AddAction(actualAction);
         return *this;
      }

      ActionBuilder<RegistryType, ReturnType, 0> &AllwaysExecute(typename RegistryType::RegistryTraits::FunctionType func)
      {
         actualAction->SetFunction(func);
         registry.AddAction(actualAction);
         return *this;
      }

   private:
      CallAction<typename RegistryType::RegistryTraits> *actualAction;
      RegistryType &registry;    
   };

} // namespace carnamock

#endif 