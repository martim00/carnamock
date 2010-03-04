#pragma once
#ifndef INCLUDED_RESULTTYPE_H
#define INCLUDED_RESULTTYPE_H

#include <sstream>

class ResultType
{
public:
	virtual ~ResultType() {}
	virtual std::string Description()= 0;
};

class TimesIncorrect : public ResultType
{
public:
	virtual ~TimesIncorrect() {}
	TimesIncorrect(size_t _timesExpected, size_t _timesCalled) 
		: timesExpected(_timesExpected), timesCalled(_timesCalled) {}
	virtual std::string Description()
	{
		std::stringstream ss;
		ss << "Times expected incorrect" << std::endl;
		ss << "Expected: " << timesExpected << std::endl;
		ss << "Called: " << timesCalled << std::endl;

		return ss.str();
	}

private:
	size_t timesCalled;
	size_t timesExpected;	
};

class ParameterIncorrect : public ResultType
{
public:
	virtual ~ParameterIncorrect() {}
	ParameterIncorrect(size_t _number, const std::string &_why) : why(_why), number(_number) {}

	virtual std::string Description()
	{
		std::stringstream ss;
		ss << "Parameter " << number << " incorrect" << std::endl;
		ss << why << std::endl;
		return ss.str();
	}

private:
	size_t number;
	std::string why;
};

#endif