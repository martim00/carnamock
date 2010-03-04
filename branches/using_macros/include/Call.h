#ifndef INCLUDED_CALL_H
#define INCLUDED_CALL_H

#include "NullType.h"
#include "ResultType.h"
#include "ValueHolder.h"

#include <boost/shared_ptr.hpp>
//
//template <class ReturnType=nulltype
//, class Param1=nulltype
//, class Param2=nulltype
//, class Param3=nulltype
//, class Param4=nulltype
//, class Param5=nulltype> 
//class Call;
//
//class ICall
//{
//public:	
//   virtual ~ICall() {}
//	ICall() : verified(false) {}
//	bool Verified() const
//	{
//		return verified;
//	}
//
//	void Verified(bool wasVerified)
//	{
//		verified= wasVerified;
//	}
//
//   virtual int GetNrParams()= 0;
//
//   //virtual ResultType *Compare(ICall &)= 0;
//
//protected:
//	bool verified;
//};
//
//template <class ReturnType>
//class Call<ReturnType> : public ICall
//{
//public:
//   //ResultType *Compare(ICall &_call)
//   //{      
//   //   return NULL;
//   //}
//
//   virtual int GetNrParams() { return 0; }
//};
//
////1 arity
//template <class ReturnType, class Param1>
//class Call<ReturnType, Param1> : public ICall
//{
//	Param1 param1;
//public:
//	Call(Param1 p1) : param1(p1) {}
//
//	Param1 GetParam1() 
//	{
//		return param1; 
//	}
//
//   //ResultType *Compare(ICall &_call)
//   //{
//   //   typedef Matcher<Param1>* Matcher1;
//
//   //   Call<ReturnType, Matcher1 > *call= 
//   //      dynamic_cast<Call<ReturnType, Matcher1>*>(&_call);
//   //   if (*call->GetParam1() != param1)
//   //      return new ParameterIncorrect(1, "Incorrect parameter");
//   //   return NULL;
//   //}
//
//   virtual int GetNrParams() { return 1; }
//};
//
////2 arity
//template <class ReturnType, class Param1, class Param2>
//class Call<ReturnType, Param1, Param2> : public ICall
//{
//	Param1 param1;
//	Param2 param2;
//
//public:
//	Call(Param1 p1, Param2 p2) : param1(p1), param2(p2) {}
//
//	Param1 GetParam1() 
//	{
//		return param1; 
//	}
//	Param2 GetParam2() 
//	{
//		return param2;
//	}
//
//   //ResultType *Compare(ICall &_call)
//   //{
//   //   typedef Matcher<Param1>* Matcher1;
//   //   typedef Matcher<Param2>* Matcher2;
//
//   //   Call<ReturnType, Matcher1, Matcher2> *call= 
//   //      dynamic_cast<Call<ReturnType, Matcher1, Matcher2>*>(&_call);
//   //   if (*call->GetParam1() != param1)
//   //      return new ParameterIncorrect(1, "Incorrect parameter");
//   //   if (*call->GetParam2() != param2)
//   //      return new ParameterIncorrect(2, "Incorrect parameter");
//   //   return NULL;
//   //}
//   virtual int GetNrParams() { return 2; }
//};
//
////3 arity
//template <class ReturnType, class Param1, class Param2, class Param3>
//class Call<ReturnType, Param1, Param2, Param3> : public ICall
//{
//	Param1 param1;
//	Param2 param2;
//	Param3 param3;
//public:
//	Call(Param1 p1, Param2 p2, Param3 p3) 
//		: param1(p1)
//		, param2(p2)
//		, param3(p3)
//	{}
//
//	Param1 GetParam1() 
//	{
//		return param1; 
//	}
//	Param2 GetParam2() 
//	{
//		return param2; 
//	}
//	Param3 GetParam3() 
//	{
//		return param3; 
//	}
//
//   //ResultType *Compare(ICall &_call)
//   //{
//   //   typedef Matcher<Param1>* Matcher1;
//   //   typedef Matcher<Param2>* Matcher2;
//   //   typedef Matcher<Param3>* Matcher3;
//
//   //   Call<ReturnType, Matcher1, Matcher2, Matcher3> *call= 
//   //      dynamic_cast<Call<ReturnType, Matcher1, Matcher2, Matcher3>*>(&_call);
//   //   if (*call->GetParam1() != param1)
//   //      return new ParameterIncorrect(1, "Incorrect parameter");
//   //   if (*call->GetParam2() != param2)
//   //      return new ParameterIncorrect(2, "Incorrect parameter");
//   //   if (*call->GetParam3() != param3)
//   //      return new ParameterIncorrect(3, "Incorrect parameter");
//   //   return NULL;
//   //}
//   virtual int GetNrParams() { return 3; }
//};
//
////4 arity
//template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
//class Call<ReturnType, Param1, Param2, Param3, Param4> : public ICall
//{
//	Param1 param1;
//	Param2 param2;
//	Param3 param3;
//	Param4 param4;
//public:
//	Call(Param1 p1, Param2 p2, Param3 p3, Param4 p4) 
//		: param1(p1)
//		, param2(p2)
//		, param3(p3)
//		, param4(p4) 
//	{}
//
//	Param1 GetParam1() 
//	{
//		return param1; 
//	}
//	Param2 GetParam2() 
//	{
//		return param2; 
//	}
//	Param3 GetParam3() 
//	{
//		return param3; 
//	}
//	Param4 GetParam4() 
//	{
//		return param4; 
//	}
//
//   virtual int GetNrParams() { return 4; }
//
//   //ResultType *Compare(ICall &_call)
//   //{
//   //   typedef Matcher<Param1>* Matcher1;
//   //   typedef Matcher<Param2>* Matcher2;
//   //   typedef Matcher<Param3>* Matcher3;
//   //   typedef Matcher<Param4>* Matcher4;
//
//   //   Call<ReturnType, Matcher1, Matcher2, Matcher3, Matcher4> *call= 
//   //      dynamic_cast<Call<ReturnType, Matcher1, Matcher2, Matcher3, Matcher4>*>(&_call);
//   //   if (*call->GetParam1() != param1)
//   //      return new ParameterIncorrect(1, "Incorrect parameter");
//   //   if (*call->GetParam2() != param2)
//   //      return new ParameterIncorrect(2, "Incorrect parameter");
//   //   if (*call->GetParam3() != param3)
//   //      return new ParameterIncorrect(3, "Incorrect parameter");
//   //   if (*call->GetParam4() != param4)
//   //      return new ParameterIncorrect(4, "Incorrect parameter");
//   //   return NULL;
//   //}
//};
//
////5 arity
//template <class ReturnType, class Param1, class Param2, class Param3, class Param4, class Param5>
//class Call<ReturnType, Param1, Param2, Param3, Param4, Param5> : public ICall
//{
//	Param1 param1;
//	Param2 param2;
//	Param3 param3;
//	Param4 param4;
//	Param5 param5;
//public:
//	Call(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) 
//		: param1(p1)
//		, param2(p2)
//		, param3(p3)
//		, param4(p4) 
//		, param5(p5) 
//	{}
//
//	Param1 GetParam1() 
//	{
//		return param1; 
//	}
//	Param2 GetParam2() 
//	{
//		return param2; 
//	}
//	Param3 GetParam3() 
//	{
//		return param3; 
//	}
//	Param4 GetParam4() 
//	{
//		return param4; 
//	}
//	Param5 GetParam5() 
//	{
//		return param5; 
//	}
//};


//template <class ReturnType, class Param1>
//class Call<ReturnType, const Param1&> : public ICall
//{
//	Param1 param1;
//public:
//	Call(Param1 p1) : param1(p1) {}
//
//	/*Call<ReturnType, Param1>& WithParam(Param1 p1)
//	{
//		param1= p1;
//		return *this;
//	}	*/
//
//	Param1 GetParam1() 
//	{
//		return param1; 
//	}
//};


//
//class ICall {
//public:
//   virtual ResultType* Compare(ICall *_call)= 0;
//};
//
//class ICallImpl {
//public:
//   void AddParam(IValueHolder* _value) { params.push_back(_value); }
//protected:
//   std::vector<IValueHolder*> params;
//};
//
//template <class Derived>
//class CallImplBase : public ICallImpl
//{
//};
//
//template <class ReturnType=nulltype
//, class Param1=nulltype
//, class Param2=nulltype
//, class Param3= nulltype
//, class Param4=nulltype
//, class Param5=nulltype> 
//class CallImpl;
//
//
//template <class ReturnType>
//class CallImpl<ReturnType> : public CallImplBase<CallImpl<ReturnType> >
//{
//public:
//   static unsigned GetNrParams() { return 0; }
//};
//
//template <class ReturnType, class Param1>
//class CallImpl<ReturnType, Param1> : public CallImplBase<CallImpl<ReturnType, Param1> >
//{
//public:
//   CallImpl(Param1 *param1)
//   {
//      this->AddParam(new ValueHolder(param1));
//   }
//
//   static unsigned GetNrParams() { return 1; }
//};

class Call
{
public:
	void AddParam(IValueHolder* _value) { params.push_back(boost::shared_ptr<IValueHolder>(_value)); }
	size_t GetNrParams() { return params.size(); }
	boost::shared_ptr<IValueHolder> GetParamAt(size_t index) { return params[index]; }
protected:
	std::vector<boost::shared_ptr<IValueHolder> > params;

public:
   virtual ~Call() {}
//   Call(ICallImpl *_impl) : impl(_impl) {}
//
//private:
//   ICallImpl *impl;
};



#endif 