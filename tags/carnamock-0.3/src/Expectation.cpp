#include "Expectation.h"

#include "Call.h"
#include "ResultType.h"

namespace carnamock {

ResultType* Expectation::Compare( Call* call )
{
   //must be the same size..
   assert(call->GetNrParams() == paramsMatcher.size());

   for (size_t i= 0; i < paramsMatcher.size(); i++)
   {
      if (*paramsMatcher[i] != *call->GetParamAt(i))
         return new ParameterIncorrect(i, paramsMatcher[i]->DescribeError());
   }
   return NULL;
}

void Expectation::AddParamMatcher( IMatcher *matcher )
{
   paramsMatcher.push_back(boost::shared_ptr<IMatcher>(matcher));
}

} //namespace carnamock