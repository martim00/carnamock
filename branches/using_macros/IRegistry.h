#pragma once
#ifndef INCLUDED_IREGISTRY_H
#define INCLUDED_IREGISTRY_H

#include "ResultType.h"
#include <stdexcept>

class ICall;
class CallActionBase;

//template <class Derived>
class IRegistry {
public:
   virtual ~IRegistry() {
      if (!AllCallsVerified() && verifyOnDestructor)
      {
			result.reset(new TimesIncorrect(TimesVerified(), GetTimesCalled()));
		} 

		if (result.get()) {
			std::stringstream ss;
			ss << "Nem todas as expectations do metodo " << methodName << " foram aceitas" << std::endl;
			ss << result->Description();

			std::runtime_error e(ss.str());
         throw e;
		}

      //TODO: limpar estruturas...

   }
   IRegistry() : actualCall(0), verifyOnDestructor(true), timesVerified(0){}

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
		timesVerified++;
      if (effectiveCalls.size() <= actualCall) {

			
         std::runtime_error e("Nao ha mais calls");
         throw e;
      }
      else {
         return effectiveCalls[actualCall++];
      }
   }

	size_t TimesVerified() { return timesVerified; }

	void SetResult(ResultType *_result)
	{
		result.reset(_result);
	}

protected:
	boost::shared_ptr<ResultType> result;

   size_t actualCall;
	size_t timesVerified;
   std::string methodName;
   bool verifyOnDestructor;
   std::vector<CallActionBase*> actions;
   std::vector<ICall* > effectiveCalls;
};

#endif //INCLUDED_IREGISTRY_H