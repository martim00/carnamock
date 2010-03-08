#pragma once
#ifndef INCLUDED_ANY_H
#define INCLUDED_ANY_H

#include "Matcher.h"

namespace carnamock {

class Any : public IMatcher
{
public:
	virtual bool operator==(const IValueHolder &value)
	{
		return true;
	}
};

} //namespace carnamock


//deprecated! 
//use hamcrest!

//template <class Type>
//class Any : public Matcher<Type>
//{
//public:
//   virtual ~Any() {}
//	bool operator==(const typename Matcher<Type>::T &type)
//	{
//		return true;
//	}
//
//	virtual Matcher<typename Matcher<Type>::T> *Clone()
//	{
//		return new Any<typename Matcher<Type>::T>();
//	}
//};
//
//template <class Type>
//class Equal : public Matcher<Type>
//{
//	typename Matcher<Type>::T value;
//public:
//	virtual ~Equal() {
//	}
//	explicit Equal(typename Matcher<Type>::T _value) : value(_value) {}
//	bool operator==(const typename Matcher<Type>::T &_value)
//	{
//      bool result= value == _value;
//      if (!result) {
//         description << "Expect value " << value << " is not equal to actual " << _value << std::endl;
//      }
//		return result;
//	}
//
//	virtual Matcher<typename Matcher<Type>::T> *Clone()
//	{
//		return new Equal<typename Matcher<Type>::T>(value);
//	}
//};


#endif