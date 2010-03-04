#pragma once
#ifndef INCLUDED_IREGISTRY_H
#define INCLUDED_IREGISTRY_H

#include "ResultType.h"
#include <stdexcept>
#include "Expectation.h"

namespace carnamock {

class ICall;
class CallActionBase;

class IRegistry {
public:
	virtual ~IRegistry() {

		if (verifyOnDestructor) {

			if (effectiveCalls.size() != expectations.size())
			{
				result.reset(new TimesIncorrect(expectations.size(), GetTimesCalled()));
			} else {

				for (unsigned i= 0; i < effectiveCalls.size(); i++) {
					Call *effectiveCall= effectiveCalls[i].get();
					Expectation *expectedCall= expectations[i].get();

					result.reset(expectedCall->Compare(effectiveCall));
					if (result.get()) break;
				}
			}      

			if (result.get()) {
				std::stringstream ss;
				ss << "Nem todas as expectations do metodo " << methodName << " foram aceitas" << std::endl;
				ss << result->Description();

				std::runtime_error e(ss.str());
				throw e;
			}
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
		actions.push_back(boost::shared_ptr<CallActionBase>(_action));
	}

	/*bool AllCallsVerified()
	{
	if (effectiveCalls.empty()) return true;
	return (effectiveCalls[effectiveCalls.size()-1]->Verified());
	}*/

	void AddCall(Call *call)
	{  
		effectiveCalls.push_back(boost::shared_ptr<Call>(call));
	}

	std::size_t GetTimesCalled() { return effectiveCalls.size(); }

	std::vector<boost::shared_ptr<Call> > &GetCalls()
	{
		return effectiveCalls;
	}

	Call *GetNextCall()
	{
		timesVerified++;
		if (effectiveCalls.size() <= actualCall) {


			std::runtime_error e("Nao ha mais calls");
			throw e;
		}
		else {
			return effectiveCalls[actualCall++].get();
		}
	}

	void AddExpectation(Expectation *expectation)
	{
		expectations.push_back(boost::shared_ptr<Expectation>(expectation));
	}

	std::size_t GetActualCall() { return actualCall; }

	std::size_t TimesVerified() { return timesVerified; }

	void SetResult(ResultType *_result)
	{
		result.reset(_result);
	}

protected:
	boost::shared_ptr<ResultType> result;

	std::size_t actualCall;
	std::string methodName;
	bool verifyOnDestructor;
   std::size_t timesVerified;
	std::vector<boost::shared_ptr<Call> > effectiveCalls;
   std::vector<boost::shared_ptr<CallActionBase> > actions;   
	std::vector<boost::shared_ptr<Expectation> > expectations;
};

} //namespace carnamock

#endif //INCLUDED_IREGISTRY_H