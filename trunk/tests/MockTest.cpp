#include <cppunit/extensions/HelperMacros.h>


#include <carnamock.h>

#include <boost/bind.hpp>

#include "hamcrest/core/matchers/hc_equal_to.h"
#include "hamcrest/core/hc_matcher.h"
#include "hamcrest/core/matchers/hc_anything.h"
#include "NiceReportMock.h"
#include "NiceMock.h"

using namespace hamcrest;
using namespace carnamock;

struct ProductionClass {
	virtual int foo()= 0;
	virtual int param1(int)= 0;
	virtual int param1Double(double)= 0;
	virtual int param1String(const std::string &)= 0;
	virtual int param1Ptr(int *)= 0;
	virtual int param1Ref(int&)= 0;
	virtual int* param1RetornoPtr(int&)= 0;
	virtual double param2(int&, const std::string &)= 0;

	virtual void metodoSemRetornoSemParam()= 0;
	virtual void metodoSemRetornoComUmParam(int&)= 0;
	virtual void metodoSemRetornoComDoisParam(char*, int)= 0;
	virtual void constCharConstParameter(const char* const)= 0;
};

struct MockClass : public ProductionClass
{
public:
	virtual ~MockClass() {}

	RETURN_METHOD0(int, foo);
	RETURN_METHOD1(int, param1, int);
	RETURN_METHOD1(int, param1Double, double);
	RETURN_METHOD1(int, param1String, const std::string&);
	RETURN_METHOD1(int, param1Ptr, int*);
	RETURN_METHOD1(int, param1Ref, int&);
	RETURN_METHOD1(int*, param1RetornoPtr, int&);
	RETURN_METHOD2(double, param2, int&, const std::string&);
	
	VOID_METHOD0(void, metodoSemRetornoSemParam);
	VOID_METHOD1(void, metodoSemRetornoComUmParam, int&);
	VOID_METHOD2(void, metodoSemRetornoComDoisParam, char*, int);
	VOID_METHOD1(void, constCharConstParameter, const char* const);
};


class MockTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( MockTest );
	CPPUNIT_TEST( testMockFalhaSeExpectationsNaoForemRealizadas );
	CPPUNIT_TEST( testMockNaoFalhaSeExpectationsForemRealizadas );
	CPPUNIT_TEST( testMockFazVerificacoesQuandoEhDeletado );
	CPPUNIT_TEST( testMockPermiteExpectationsNosParametrosDoMetodo );
	CPPUNIT_TEST( testMockFalhaSeExpectationsNoParametroNaoForemRealizadas );
	CPPUNIT_TEST( testMockParamDouble );
	CPPUNIT_TEST( testMockParamString );
	CPPUNIT_TEST( testMockParamPtr );
	CPPUNIT_TEST( testMockParamRef );
   CPPUNIT_TEST( testMockFalhaPorTerTimesAMais );
	CPPUNIT_TEST( testMockPermiteDefinirAcoesParaMetodos );
	CPPUNIT_TEST( testDefinirAcoesComPlaceHolders );
	CPPUNIT_TEST( testMetodoComDoisParametros );
	CPPUNIT_TEST( testMetodosSemRetorno );
   CPPUNIT_TEST( testMetodoSemRetornoUmParametro );
   CPPUNIT_TEST( testWhenCallPermiteSetarThenExecuteStatement );
   CPPUNIT_TEST( testThenExecuteStatementPermiteParametros );
	CPPUNIT_TEST( testNiceMockSohReclamaParaExpectationsExplicitas );
   CPPUNIT_TEST( testUsingHamcrest );
	CPPUNIT_TEST( testExpectationBuilder );
	CPPUNIT_TEST( testConstCharConstParameter );
	CPPUNIT_TEST( testExpectationNaoPrecisaSetarParams );
   //CPPUNIT_TEST( testNiceReportMockShowsReportAllOnce );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp()
  {
  }

protected:	

	void testMockFalhaSeExpectationsNaoForemRealizadas()
	{      
      try
      {
         {
            MockClass mock;
            EXPECT(mock, foo)->Times(1);

         }
         CPPUNIT_ASSERT(false);
         
      }catch (std::runtime_error&)
      {
         CPPUNIT_ASSERT(true);
      }
	}

	void testMockFazVerificacoesQuandoEhDeletado()
	{
		try 
		{
			{
				MockClass mock;
				mock.foo();
			}
		} catch (...)
		{
			CPPUNIT_ASSERT(true);
			return;
		}
		CPPUNIT_ASSERT(false);
	}

	void testMockNaoFalhaSeExpectationsForemRealizadas()
	{
		MockClass mock;
		mock.foo();

      CPPUNIT_ASSERT_NO_THROW(EXPECT(mock, foo)->Times(1));
	}	

	void testMockPermiteExpectationsNosParametrosDoMetodo()
	{		
      try 
      {  
         {
            MockClass mock;
		      mock.param1(1);

            EXPECT(mock, param1)->WithParams(equal_to(1)).Times(1);

         }
			CPPUNIT_ASSERT(true);
		} catch (std::runtime_error&)
		{
			CPPUNIT_ASSERT(false);
		}
	}

	void testMockFalhaSeExpectationsNoParametroNaoForemRealizadas()
	{
      try {
         {
            MockClass mock;
            mock.param1(1);
            EXPECT(mock, param1)->WithParams(equal_to(5)).Times(1);
         }

         CPPUNIT_ASSERT(false);
      } catch (std::runtime_error &)
      {
         CPPUNIT_ASSERT(true);
      }		
	}

	void testMockParamDouble()
	{	
		MockClass mock;
		mock.param1Double(20.2);

      EXPECT(mock, param1Double)->WithParams(equal_to(20.2)).Times(1);

	}

	void testMockParamString()
	{	
		MockClass mock;
		mock.param1String("mock");

      EXPECT(mock, param1String)->WithParams(equal_to<std::string>("mock")).Times(1);

	}

	void testMockParamPtr()
	{	
		int *ptr= new int(10);
		MockClass mock;
		mock.param1Ptr(ptr);

      EXPECT(mock, param1Ptr)->WithParams(equal_to<int*>(ptr)).Times(1);
	}

	void testMockParamRef()
	{
		int ref= 10;
		MockClass mock;
		mock.param1Ref(ref);

      EXPECT(mock, param1Ref)->WithParams(equal_to(ref)).Times(1);
	}

	void testMockPermiteDefinirAcoesParaMetodos()
	{
		int a= 10;
		int *b= new int(20);
		MockClass mock;      
      WHEN_CALL(mock, param1Double)->WithParam(equal_to(20.1)).ThenReturn(10);
      WHEN_CALL(mock, param1RetornoPtr)->WithParam(equal_to(a)).ThenReturn(b);

		CPPUNIT_ASSERT_EQUAL(10, mock.param1Double(20.1));
		CPPUNIT_ASSERT_EQUAL(20, *mock.param1RetornoPtr(a));

  		EXPECT(mock, param1Double)->WithParams(equal_to(20.1)).Times(1);
		EXPECT(mock, param1RetornoPtr)->WithParams(equal_to(a)).Times(1);

		delete b;
	}

	void testDefinirAcoesComPlaceHolders()
	{
		MockClass mock;
      WHEN_CALL(mock, param1Double)->WithParam(anything<double>()).ThenReturn(10);

		CPPUNIT_ASSERT_EQUAL(10, mock.param1Double(1));
		CPPUNIT_ASSERT_EQUAL(10, mock.param1Double(12));
		CPPUNIT_ASSERT_EQUAL(10, mock.param1Double(1282828));

		EXPECT(mock, param1Double)->WithParams(equal_to(1.)).Times(1);
  		EXPECT(mock, param1Double)->WithParams(equal_to(12.)).Times(1);
  		EXPECT(mock, param1Double)->WithParams(equal_to(1282828.)).Times(1);
	}

	void testMetodoComDoisParametros()		
	{
		MockClass mock;

		int a= 10;

      WHEN_CALL(mock, param2)->WithParams(equal_to(10), equal_to<std::string>("ola"))
         .ThenReturn(10.2);

		const std::string ola("ola");

		CPPUNIT_ASSERT_DOUBLES_EQUAL(10.2, mock.param2(a, ola), 0.01);

      EXPECT(mock, param2)->WithParams(equal_to(a), equal_to<std::string>("ola")).Times(1);
	}

	void testMetodosSemRetorno()
	{
		MockClass mock;
		mock.metodoSemRetornoSemParam();
      EXPECT(mock, metodoSemRetornoSemParam)->Times(1);
	}

   void testMetodoSemRetornoUmParametro()
   {
      int a= 1;
      MockClass mock;
      mock.metodoSemRetornoComUmParam(a);

      EXPECT(mock, metodoSemRetornoComUmParam)->WithParams(equal_to(a)).Times(1);
   }

   void testMockFalhaPorTerTimesAMais()
	{
	/*	MockClass mock;
		mock.param1(2);
		mock.param1(2);
	*/	/*EXPECT(mock, param1)->WithParams(Equal<int>(2)).Times(1);

		EXPECT(mock, param1)->WithParams(Equal<int>(2)).Times(1);	*/
   }
   
   struct Dummy {

      Dummy() : executou(false), paramPassado(0) {}

      void dummyMethod() {
         executou= true;
      }

      void dummyMethodWithReturnAndParam(char*, int)
      {
         executou= true;
      }

      int paramPassado;
      bool executou;
   };

   void testWhenCallPermiteSetarThenExecuteStatement()
   {
      Dummy dummy;
      MockClass mock;
      WHEN_CALL(mock, metodoSemRetornoSemParam)->AllwaysExecute(
         boost::bind(&Dummy::dummyMethod, &dummy));

      mock.metodoSemRetornoSemParam();

      CPPUNIT_ASSERT(dummy.executou);

      EXPECT(mock, metodoSemRetornoSemParam)->Times(1);
   }

   void testThenExecuteStatementPermiteParametros()
   {
      Dummy dummy;
      MockClass mock;
      
      WHEN_CALL(mock, metodoSemRetornoComDoisParam)->WithParams(equal_to<char*>("2"), equal_to(10))
         .ThenExecute(boost::bind(&Dummy::dummyMethodWithReturnAndParam, &dummy, _1, _2));

      mock.metodoSemRetornoComDoisParam("2", 10);

      CPPUNIT_ASSERT(dummy.executou);
      EXPECT(mock, metodoSemRetornoComDoisParam)->WithParams(equal_to<char*>("2"), equal_to(10)).Times(1);
   }

	void testNiceMockSohReclamaParaExpectationsExplicitas()
	{      
      {
         //nice mock without expectations doesn't complain..
		   NiceMock<MockClass> mock;
  		   mock.param1(1);
      }

      try {

         {
            //if has some expectation nice mock must complain
            NiceMock<MockClass> mock;
            EXPECT(mock, metodoSemRetornoComDoisParam)->WithParams(equal_to<char*>("2"), equal_to(10)).Times(1);
            
         }
         CPPUNIT_ASSERT_MESSAGE("Nice mock with not accepted expectations. Must fail...", false);

      } catch (std::runtime_error &)
      {
         CPPUNIT_ASSERT(true);
      }
		
	}

	void testUsingHamcrest()
	{
		MockClass mock;

      EXPECT(mock, metodoSemRetornoComDoisParam)->WithParams(
         hamcrest::equal_to<char*>("2"), equal_to(10)).Times(1);

      mock.metodoSemRetornoComDoisParam("2", 10);
	}

	void testExpectationBuilder()
	{
		CallRegistry<int, int> reg1;
		ExpectationBuilder<CallRegistry<int, int> > builder1(reg1);

		builder1.WithParams(equal_to(1));

		CallRegistry<int, int, double> reg2;
		ExpectationBuilder<CallRegistry<int, int, double> > builder2(reg2);

		builder2.WithParams(equal_to(1), equal_to(2.));

		CallRegistry<int, int, double, const char*> reg3;
		ExpectationBuilder<CallRegistry<int, int, double, const char*> > builder3(reg3);

		builder3.WithParams(equal_to(1), equal_to(2.), equal_to<const char*>("a"));

		CallRegistry<int, int, double, const char*, int> reg4;
		ExpectationBuilder<CallRegistry<int, int, double, const char*, int> > builder4(reg4);

		builder4.WithParams(equal_to(1), equal_to(2.), equal_to<const char*>("a"), anything<int>());
	}

	void testConstCharConstParameter()
	{
		MockClass mock;

		EXPECT(mock, constCharConstParameter)->WithParams(equal_to<const char*>("a")).Times(1);

		mock.constCharConstParameter("a");
	}

	void testExpectationNaoPrecisaSetarParams()
	{
		MockClass mock;
		EXPECT(mock, constCharConstParameter)->Times(1);
		mock.constCharConstParameter("a");
	}

   /*void testNiceReportMockShowsReportAllOnce()
   {
      NiceReportMock<MockClass> mock;
      EXPECT(mock, constCharConstParameter)->Times(1);      

      mock.foo();
      mock.param1(1);            
   }*/

	
};

CPPUNIT_TEST_SUITE_REGISTRATION( MockTest );