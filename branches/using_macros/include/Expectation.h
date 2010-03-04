#pragma once
#ifndef INCLUDED_EXPECTATION_H
#define INCLUDED_EXPECTATION_H

#include "Call.h"
#include "ResultType.h"
#include "NullType.h"
#include "Matcher.h"

namespace carnamock {

class Expectation
{
public:
	~Expectation() {}

   ResultType* Compare(Call* call)
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

	void AddParamMatcher(IMatcher *matcher)
	{	
		paramsMatcher.push_back(boost::shared_ptr<IMatcher>(matcher));
	}

private:
	std::vector<boost::shared_ptr<IMatcher> > paramsMatcher;
};

} //namespace carnamock

#endif //INCLUDED_EXPECTATION_H