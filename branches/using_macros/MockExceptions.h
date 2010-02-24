#pragma once
#ifndef INCLUDED_MOCKEXCEPTIONS
#define INCLUDED_MOCKEXCEPTIONS

#include <stdexcept.h>

class NoMoreCallsException : public std::runtime_error
{
public:
	const char *what() const
	{
		return "";
	}

};

#endif 