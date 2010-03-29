#pragma once
#ifndef INCLUDED_CALL_H
#define INCLUDED_CALL_H

#include "ValueHolder.h"
#include <vector>
#include <boost/shared_ptr.hpp>

namespace carnamock {

/**
*  Represents a method call. 
*  The IRegistry will record that to the final verifications...
*  @see IRegistry
*/ 
class Call
{
public:
   virtual ~Call() {}
   Call() {}

   size_t GetNrParams() { return params.size(); }
   boost::shared_ptr<IValueHolder> GetParamAt(size_t index) { return params[index]; }
	void AddParam(IValueHolder* _value) { params.push_back(boost::shared_ptr<IValueHolder>(_value)); }
protected:
	std::vector<boost::shared_ptr<IValueHolder> > params;
};

} //namespace carnamock

#endif 