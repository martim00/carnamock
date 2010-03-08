#ifndef INCLUDED_CALLACTION_H
#define INCLUDED_CALLACTION_H

#include <hamcrest/core/hc_matcher.h>

#include <boost/function.hpp>

namespace carnamock {   

   class IMatcher;

   class CallActionBase
   {   
   public:
      virtual ~CallActionBase() {}

      //if some other type will be added this must be factored to inheritance 
      enum ActionType { RETURNABLE, DELEGATE_TO_FUNCTION };

   protected:
      ActionType actionType;
   };

   template <class FuncTraits, class ReturnType= typename FuncTraits::ReturnType>
   class CallAction : public CallActionBase
   {
      ReturnType returns;
      std::vector<IMatcher*> matchers;
      typename FuncTraits::FunctionType func;
   public:	

      bool KnowsThat(std::vector<IValueHolder*> params)
      {
         assert(params.size() == matchers.size());
         for (unsigned i= 0; i < params.size(); i++) {
            if (*matchers[i] != *params[i])
               return false;
         }
         return true;
      }      
      
      typename FuncTraits::ReturnType Execute()
      {
         return actionType == RETURNABLE ? returns : func();
      }

      template <class Param1>
      typename FuncTraits::ReturnType Execute(Param1 p1)
      {
         return actionType == RETURNABLE ? returns : func(p1);
      }

      template <class Param1, class Param2>
      typename FuncTraits::ReturnType Execute(Param1 p1, Param2 p2)
      {
         return actionType == RETURNABLE ? returns : func(p1, p2);
      }

      template <class Param1, class Param2, class Param3>
      typename FuncTraits::ReturnType Execute(Param1 p1, Param2 p2, Param3 p3)
      {
         return actionType == RETURNABLE ? returns : func(p1, p2, p3);
      }

      template <class Param1, class Param2, class Param3, class Param4>
      typename FuncTraits::ReturnType Execute(Param1 p1, Param2 p2, Param3 p3, Param4 p4)
      {
         return actionType == RETURNABLE ? returns : func(p1, p2, p3, p4);
      }

      void AddParam(IMatcher *matcher)
      {
         matchers.push_back(matcher);
      }

      void SetReturn(typename FuncTraits::ReturnType _returns)
      {
         actionType= RETURNABLE;
         returns= _returns;
      }

      void SetFunction(typename FuncTraits::FunctionType _func) 
      { 
         actionType= DELEGATE_TO_FUNCTION;
         func= _func; 
      }
   };

   template <class FuncTraits>
   class CallAction<FuncTraits, void> : public CallActionBase
   {
      std::vector<IMatcher*> matchers;
      typename FuncTraits::FunctionType func;
   public:	
      bool KnowsThat(std::vector<IValueHolder*> params)
      {
         assert(params.size() == matchers.size());
         for (unsigned i= 0; i < params.size(); i++) {
            if (*matchers[i] != *params[i])
               return false;
         }
         return true;
      }      

      void Execute()
      {
         func();
      }

      template <class Param1>
      void Execute(Param1 p1)
      {
         func(p1);
      }

      template <class Param1, class Param2>
      void Execute(Param1 p1, Param2 p2)
      {
         func(p1, p2);
      }

      template <class Param1, class Param2, class Param3>
      void Execute(Param1 p1, Param2 p2, Param3 p3)
      {
         func(p1, p2, p3);
      }

      template <class Param1, class Param2, class Param3, class Param4>
      void Execute(Param1 p1, Param2 p2, Param3 p3, Param4 p4)
      {
         func(p1, p2, p3, p4);
      }

      void AddParam(IMatcher *matcher)
      {
         matchers.push_back(matcher);
      }      

      void SetFunction(typename FuncTraits::FunctionType _func) 
      { 
         actionType= DELEGATE_TO_FUNCTION;
         func= _func; 
      }
   };

} //namespace carnamock

#endif