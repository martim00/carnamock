#ifndef INCLUDED_MATCHER_H
#define INCLUDED_MATCHER_H

#include "no_cref.h"

template <class Type>
class Matcher
{
public:
   typedef typename no_cref<Type>::type T;
   
	virtual bool operator==(const T &type)= 0;
	virtual bool operator!=(const T &type)
	{
		return !operator==(type);
	}

	virtual Matcher<T> *Clone()= 0;
};
//
//template <class Type>
//class Matcher<const Type&>
//{
//public:
//	virtual bool operator==(const Type &type)= 0;	
//};

#endif 