#ifndef INCLUDED_MOCK_H
#define INCLUDED_MOCK_H

#include <boost/function.hpp>
#include <stdexcept>
#include <sstream>

#define METHOD0(returnType, methodName) returnType methodName() { this->registerCallForMethod(#methodName); }
#define METHOD1(returnType, methodName, p1) returnType methodName(p1) { this->registerCallForMethod(#methodName); }
#define METHOD2(returnType, methodName, p1, p2) returnType methodName(p1, p2) { this->registerCallForMethod(#methodName); }
#define METHOD3(returnType, methodName, p1, p2, p3) returnType methodName(p1, p2, p3) { this->registerCallForMethod(#methodName); }
#define METHOD4(returnType, methodName, p1, p2, p3, p4) returnType methodName(p1, p2, p3, p4) { this->registerCallForMethod(#methodName); }
#define METHOD5(returnType, methodName, p1, p2, p3, p4, p5) returnType methodName(p1, p2, p3, p4, p5) { this->registerCallForMethod(#methodName); }
#define METHOD6(returnType, methodName, p1, p2, p3, p4, p5, p6) returnType methodName(p1, p2, p3, p4, p5, p6) { this->registerCallForMethod(#methodName); }
#define METHOD7(returnType, methodName, p1, p2, p3, p4, p5, p6, p7) returnType methodName(p1, p2, p3, p4, p5, p6, p7) { this->registerCallForMethod(#methodName); }
#define METHOD8(returnType, methodName, p1, p2, p3, p4, p5, p6, p7, p8) returnType methodName(p1, p2, p3, p4, p5, p6, p7, p8) { this->registerCallForMethod(#methodName); }



#define RETURN_METHOD0(returnType, methodName) returnType methodName() { return this->registerCallForMethod<returnType>(#methodName); }
#define RETURN_METHOD1(returnType, methodName, p1) returnType methodName(p1) { return this->registerCallForMethod<returnType,p1>(#methodName); }
#define RETURN_METHOD2(returnType, methodName, p1, p2) returnType methodName(p1 p1Value, p2 p2Value) { return this->registerCallForMethod<returnType,p1,p2>(#methodName, p1Value, p2Value); }

//#define METHOD0(returnType, methodName)										\
//		returnType methodName()														\
//		{																					\
//			registerCallForMethod(#methodName);									\					
//		}																					

class CallRegistry
{
public:
	CallRegistry() : timesExpected(0), timesCalled(0), allowTracking(true) {}

	size_t GetTimesExpected() const { return timesExpected; }
	size_t GetTimesCalled() const { return timesCalled; }

	void IncrementTimesCalled()
	{
		timesCalled++;
	}

	void IncrementTimesExpected(int times)
	{
		timesExpected+= times;
	}

	bool ExpectationsAccepted() const
	{
		return timesExpected == timesCalled;
	}

   void TurnOffTracking()
   {
      allowTracking= true;
   }

   bool AllowTracking()
   {
      return allowTracking;
   }

private:
   bool allowTracking;

	size_t timesExpected;
	size_t timesCalled;


};

class MockMixin 
{
public:

	typedef std::map<std::string, CallRegistry*>::iterator CallIterator; 

	virtual ~MockMixin() {
		clearCalls();
	} 
	MockMixin() {} 

	void Expect(const std::string &methodName, int times= 1)
	{
		if (!alreadyExistsRegistryForMethod(methodName))
			methodCalls[methodName]= new CallRegistry();
		methodCalls[methodName]->IncrementTimesExpected(times);
	}

   void TurnOffMethodTracking(const std::string &methodName)
   {
      methodCalls[methodName]->TurnOffTracking();
   }

   template <typename ReturnType>
   void OnCall(const std::string &methodName, boost::function0<ReturnType> dummyImpl)
   {
      GetDummyImplementations<ReturnType>()[methodName]= dummyImpl;
   }

   template <typename ReturnType, typename P1>
   void OnCall(const std::string &methodName, boost::function1<ReturnType, P1> dummyImpl)
   {
      GetDummyImplementations<ReturnType, P1>()[methodName]= dummyImpl;
   }

   template <typename ReturnType, typename P1, typename P2>
   void OnCall(const std::string &methodName, boost::function2<ReturnType, P1, P2> dummyImpl)
   {
      GetDummyImplementations<ReturnType, P1, P2>()[methodName]= dummyImpl;
   }


	/*template <typename P1>
	void Expect(const std::string &methodName, P1 p1)
	{	
		if (!alreadyExistsRegistryForMethod(methodName))
			methodCalls[methodName]= new CallRegistry();
		methodCalls[methodName]->IncrementTimesExpected();
	}	*/

	bool alreadyExistsRegistryForMethod(const std::string &methodName)
	{
		return methodCalls.find(methodName) != methodCalls.end();
	}

	void registerCallForMethod(const std::string &methodName)
	{
		if (!alreadyExistsRegistryForMethod(methodName))			
			this->methodCalls[methodName]= new CallRegistry();
		this->methodCalls[methodName]->IncrementTimesCalled();	

      if (existsDummyImplementations<void>(methodName))
         GetDummyImplementations<void>()[methodName]();
	}

   template <typename ReturnType>
   ReturnType registerCallForMethod(const std::string &methodName)
	{
		if (!alreadyExistsRegistryForMethod(methodName))
			this->methodCalls[methodName]= new CallRegistry();
		this->methodCalls[methodName]->IncrementTimesCalled();

      if (existsDummyImplementations<ReturnType>(methodName))
         return GetDummyImplementations<ReturnType>()[methodName]();
	}

   template <typename ReturnType, typename P1>
   ReturnType registerCallForMethod(const std::string &methodName)
   {
      if (!alreadyExistsRegistryForMethod(methodName))
         this->methodCalls[methodName]= new CallRegistry();
      this->methodCalls[methodName]->IncrementTimesCalled();

      if (existsDummyImplementations<ReturnType, P1>(methodName))
         return GetDummyImplementations<ReturnType, P1>()[methodName]();
   }

   template <typename ReturnType, typename P1, typename P2>
   ReturnType registerCallForMethod(const std::string &methodName, P1 p1, P2 p2)
   {
      if (!alreadyExistsRegistryForMethod(methodName))
         this->methodCalls[methodName]= new CallRegistry();
      this->methodCalls[methodName]->IncrementTimesCalled();

      if (existsDummyImplementations<ReturnType, P1, P2>(methodName))
         return GetDummyImplementations<ReturnType, P1, P2>()[methodName](p1,p2);
   }

   template <typename ReturnType>
   bool existsDummyImplementations(const std::string &methodName)
   {      
      return GetDummyImplementations<ReturnType>().find(methodName) 
         != GetDummyImplementations<ReturnType>().end();
   }

   template <typename ReturnType, typename P1>
   bool existsDummyImplementations(const std::string &methodName)
   {      
      return GetDummyImplementations<ReturnType, P1>().find(methodName) 
         != GetDummyImplementations<ReturnType, P1>().end();
   }

   template <typename ReturnType, typename P1, typename P2>
   bool existsDummyImplementations(const std::string &methodName)
   {      
      return GetDummyImplementations<ReturnType, P1, P2>().find(methodName) 
         != GetDummyImplementations<ReturnType, P1, P2>().end();
   }

	void Verify()
	{
		CallIterator it= Begin();
		for (; it != End(); it++)
		{
         if (!it->second->AllowTracking())
            continue;

			if (!it->second->ExpectationsAccepted()) {

            std::stringstream ss;
            ss << "O metodo " + it->first + " nao teve suas expectations aceitas...\n";
            ss << "Esperava ser chamado " << it->second->GetTimesExpected() << " vezes. \n";
            ss << "Foi chamado " << it->second->GetTimesCalled() << " vezes. \n";            
            
				std::runtime_error e(ss.str());
				throw e;
			}
		}
	}	

	std::map<std::string, CallRegistry*> &GetMethodCalls() 
	{
		return methodCalls;
	}	

	CallIterator Begin()
	{
		return methodCalls.begin();
	}

	CallIterator End()
	{
		return methodCalls.end();
	}

protected:
	void clearCalls()
	{	
		CallIterator it= Begin();
		for (; it != End(); it++)
			delete it->second;
	
		methodCalls.clear();
	}


	
protected:
	std::map<std::string, CallRegistry*> methodCalls;

   template <class ReturnType>
   static std::map<std::string,boost::function0<ReturnType> > &GetDummyImplementations()
   {
      static std::map<std::string,boost::function0<ReturnType> > dummyImplementations;
      return dummyImplementations;
   }

   template <class ReturnType, class P1>
   static std::map<std::string,boost::function1<ReturnType, P1> > &GetDummyImplementations()
   {
      static std::map<std::string,boost::function1<ReturnType, P1> > dummyImplementations;
      return dummyImplementations;
   }

   template <class ReturnType, class P1, class P2>
   static std::map<std::string,boost::function2<ReturnType, P1, P2> > &GetDummyImplementations()
   {
      static std::map<std::string,boost::function2<ReturnType, P1, P2> > dummyImplementations;
      return dummyImplementations;
   }
   
};



//template <class Production>
//class Mock : public Production
//{	
//public:
//	
//	Mock() : chamouMetodo(false) {}
//
//	template <class P1>
//	Mock(P1 p1) : Production(p1), chamouMetodo(false) {}
//
//	template <class P1, class P2>
//	Mock(P1 p1, P2 p2) : Production(p1, p2), chamouMetodo(false) {}
//
//	template <class P1, class P2, class P3>
//	Mock(P1 p1, P2 p2, P3 p3) : Production(p1, p2, p3), chamouMetodo(false) {}
//
//	template <class P1, class P2, class P3, class P4>
//	Mock(P1 p1, P2 p2, P3 p3, P4 p4) : Production(p1, p2, p3, p4), chamouMetodo(false) {}
//
//
//	bool chamouMetodo;
//
//#define EXPECT(MethodName) void MethodName()	{	chamouMetodo= true;	}
//
//};

#endif 