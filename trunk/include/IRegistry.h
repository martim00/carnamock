#pragma once
#ifndef INCLUDED_IREGISTRY_H
#define INCLUDED_IREGISTRY_H

#include "ResultType.h"
#include <stdexcept>
#include "Expectation.h"
#include "CallAction.h"
#include "Call.h"

namespace carnamock {

/**
*  The base class for a method registry. Records all the informations needed for a mocked method
*  in runtime.
*/ 
class IRegistry {
public:
	virtual ~IRegistry(); 
	IRegistry();

	std::string MethodName() const { return methodName; }
	void SetMethodName(const std::string &_methodName) { methodName= _methodName; }
	
	/**
	*  Verifies the expectation on destructor. 
   *  If false the expectations will not be verified.
	*  @param bool verify
	*/ 
   void VerifyOnDestructor(bool verify) { verifyOnDestructor= verify; }

   /**
   *  Sets the mock owner of this method..
   *  @param const void * _owner
   */ 
   void SetOwner(const void* _owner) { owner= _owner; }

   /**
   *  Configure this method to throw an exception on expectations not accepted.
   *  If false will log the error on MockMap
   *  @see MockMap
   *  @see MockInfo
   *  @param bool throws
   */ 
   void ThrowsOnError(bool throws);

	/**
	*  Adds an actions to this method registry.
	*  @param CallActionBase * _action
	*/ 
   void AddAction(CallActionBase *_action);

	/**
	*  Adds a call to this method registry.
	*  @param Call * call
	*/ 
   void AddCall(Call *call);

   /**
	*  Adds an expectation to this method registry
	*  @param Expectation * expectation
	*/ 
   void AddExpectation(Expectation *expectation);

	/**
	*  Returns the number of times that this method was called.
	*  @return std::size_t
	*/ 
   std::size_t GetTimesCalled() { return effectiveCalls.size(); }

	/**
	*  Returns the next call made to this method.
	*  @return Call *
	*/ 
   Call *GetNextCall();	

	/**
	*  Sets the actual result to this method registry.
	*  @param ResultType * _result
	*/ 
   void SetResult(ResultType *_result)	{ result.reset(_result); }

protected:
   const void *owner;
	bool throwsOnError;
   std::size_t actualCall;
	std::string methodName;   
	bool verifyOnDestructor;
   std::size_t timesVerified;
   boost::shared_ptr<ResultType> result;
	std::vector<boost::shared_ptr<Call> > effectiveCalls;
   std::vector<boost::shared_ptr<CallActionBase> > actions;   
	std::vector<boost::shared_ptr<Expectation> > expectations;
};

} //namespace carnamock

#endif //INCLUDED_IREGISTRY_H