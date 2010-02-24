#ifndef INCLUDED_ANY_H
#define INCLUDED_ANY_H

#include "Matcher.h"

#include "no_cref.h"

template <class Type>
//class Any : public Matcher<typename no_cref<Type>::type>
class Any : public Matcher<Type>
{
	//typedef typename no_cref<Type>::type T;
public:
	bool operator==(const typename Matcher<Type>::T &type)
	{
		return true;
	}

	virtual Matcher<typename Matcher<Type>::T> *Clone()
	{
		return new Any<typename Matcher<Type>::T>();
	}
};

template <class Type>
//class Equal : public Matcher<typename no_cref<Type>::type>
class Equal : public Matcher<Type>
{
//	typedef typename no_cref<Type>::type T;

	typename Matcher<Type>::T value;
public:
	virtual ~Equal() {
	}
	explicit Equal(typename Matcher<Type>::T _value) : value(_value) {}
	bool operator==(const typename Matcher<Type>::T &_value)
	{
      bool result= value == _value;
      if (!result) {
         description << "Expect value " << value << " is not equal to actual " << _value << std::endl;
      }
		return result;
	}

	virtual Matcher<typename Matcher<Type>::T> *Clone()
	{
		return new Equal<typename Matcher<Type>::T>(value);
	}
};
//
//template <class Type>
//class Equal<const Type&> : public Matcher<const Type&>
//{
//	Type value;
//public:
//	Equal(Type _value) : value(_value) {}
//	bool operator==(const Type &_value)
//	{
//		return value == _value;
//	}
//};


/*
template <class Type>
class LessThan : public Matcher<Type>
{
	Type value;
public:
	LessThan(Type _value) : value(_value) {}

	bool operator==(const Type &_value)
	{
		return value > _value;
	}
};    */


#endif