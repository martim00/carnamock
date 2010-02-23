#pragma once
#ifndef INCLUDED_IREGISTRY_H
#define INCLUDED_IREGISTRY_H

#include <stdexcept>

class ICall;
class CallActionBase;

//template <class Derived>
class IRegistry {
public:
   virtual ~IRegistry() {
      //MockMixin::GetRegistry<ReturnType>().erase(methodName);
      if (!AllCallsVerified() && verifyOnDestructor)
      {
         std::runtime_error e("Nem todas as expectations do metodo "+methodName+" foram aceitas");
         throw e;
      }
   }
   IRegistry() : actualCall(0), verifyOnDestructor(true) {}

   std::string MethodName() const { return methodName; }
   void SetMethodName(const std::string &_methodName) { methodName= _methodName; }

   void VerifyOnDestructor(bool verify)
   {
      verifyOnDestructor= verify;
   }

   void AddAction(CallActionBase *_action)
   {	      
      actions.push_back(_action);
   }

   bool AllCallsVerified()
   {
      if (effectiveCalls.empty()) return true;
      return (effectiveCalls[effectiveCalls.size()-1]->Verified());
   }

   void AddCall(ICall *call)
   {  
      effectiveCalls.push_back(call);
   }

   size_t GetTimesCalled() { return effectiveCalls.size(); }

   std::vector<ICall*> &GetCalls()
   {
      return effectiveCalls;
   }

   ICall *GetNextCall()
   {
      if (effectiveCalls.size() <= actualCall) {
         std::runtime_error e("Nao ha mais calls");
         throw e;
      }
      else {
         return effectiveCalls[actualCall++];
      }
   }

protected:
   size_t actualCall;
   std::string methodName;
   bool verifyOnDestructor;
   std::vector<CallActionBase*> actions;
   std::vector<ICall* > effectiveCalls;
};

#endif //INCLUDED_IREGISTRY_H