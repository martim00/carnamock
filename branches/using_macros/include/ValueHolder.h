#ifndef INCLUDED_VALUEHOLDER_H
#define INCLUDED_VALUEHOLDER_H

struct IValueHolder 
{
public:
   virtual ~IValueHolder () {}
};

template <class ValueType>
class ValueHolder : public IValueHolder
{
public:
   virtual ~ValueHolder() {}
	ValueHolder(ValueType _value) : value(_value) {}

	ValueType GetValue() 
	{ 
		return value; 
	}
private:
	ValueType value;
};

#endif 