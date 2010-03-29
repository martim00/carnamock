#include "IRegistry.h"

#include "MockMap.h"

namespace carnamock {

carnamock::IRegistry::IRegistry()
: actualCall(0)
, verifyOnDestructor(true)
, timesVerified(0)
, throwsOnError(true)
, owner(NULL) 
{
}

carnamock::IRegistry::~IRegistry()
{
   if (verifyOnDestructor || expectations.size()) {

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
         ss << "Some expectations of the method " << methodName << " werent accepted" << std::endl;
         ss << result->Description();

         if (throwsOnError) {
            std::runtime_error e(ss.str());
            throw e;
         } else {
            internal::MockMap::AddLog(owner, ss.str());
            internal::MockMap::DeleteMockedMethod(owner, this);
         }
      }
   }
}

void carnamock::IRegistry::ThrowsOnError( bool throws )
{
   throwsOnError= throws;
   if (!throwsOnError) {
      assert(owner != NULL);
      internal::MockMap::AddMockedMethod(owner, this);
   }
}

void carnamock::IRegistry::AddAction( CallActionBase *_action )
{
   actions.push_back(boost::shared_ptr<CallActionBase>(_action));
}

void carnamock::IRegistry::AddCall( Call *call )
{
   effectiveCalls.push_back(boost::shared_ptr<Call>(call));
}

Call * carnamock::IRegistry::GetNextCall()
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

void carnamock::IRegistry::AddExpectation( Expectation *expectation )
{
   expectations.push_back(boost::shared_ptr<Expectation>(expectation));
}

} //namespace carnamock