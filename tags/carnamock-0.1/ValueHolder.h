#ifndef INCLUDED_VALUEHOLDER_H
#define INCLUDED_VALUEHOLDER_H

template <class ValueType>
class ValueHolder
{
public:
	ValueHolder(ValueType _value) : value(_value) {}

	ValueType GetValue() 
	{ 
		return value; 
	}
private:
	ValueType value;
};

#endif 