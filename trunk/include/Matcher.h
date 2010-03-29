#ifndef INCLUDED_MATCHER_H
#define INCLUDED_MATCHER_H

#include "TypeTraits.h"
#include "ValueHolder.h"

#include <sstream>

namespace carnamock {

class IMatcher 
{
public:
	virtual std::string DescribeError()
   {
      return description.str();
   }

	virtual bool operator==(const IValueHolder &value)= 0;
	virtual bool operator!=(const IValueHolder &value)
	{
		return !operator==(value);
	}

protected:
   std::stringstream description;
};

template <class hc_matcher, class Type>
class IMatcherWrapper : public IMatcher
{
public:
	IMatcherWrapper(hc_matcher *_match) : match(_match) {}
   virtual bool operator==(const IValueHolder &value)
   {
      const ValueHolder<Type> *v= dynamic_cast<const ValueHolder<Type>*>(&value);
      return (*match)(v->GetValue());
   }

   virtual std::string DescribeError()
   {
      hamcrest::description_t description;
      match->describe_to(description);
      return description.description_m;
   }


private:
	hc_matcher *match;
};


template <class Type>
class Matcher : public IMatcher
{
public:
   typedef typename no_cref<Type>::type T;

   virtual ~Matcher() {}

	bool operator==(IValueHolder &value)
	{
		ValueHolder<Type> *holder= dynamic_cast<ValueHolder<Type>* >(&value); 
		return this->operator==(holder->GetValue());
	}
   
	virtual bool operator==(const T &type)= 0;
	virtual bool operator!=(const T &type)
	{
		return !operator==(type);
	}

	virtual Matcher<T> *Clone()= 0;
   
};

} // namespace carnamock

#endif 