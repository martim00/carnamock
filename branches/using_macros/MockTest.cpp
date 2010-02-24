#include <cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "Mock.h"
#include "Macros.h"
#include "Any.h"
#include <windows.h>

#include <boost/bind.hpp>

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
};

struct MockClass : public ProductionClass/*, public MockMixin*/
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
};


class MockTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( MockTest );
	CPPUNIT_TEST( testMockPermiteDefinirExpectationsParaMetodosDaClasseDeProducao );
	CPPUNIT_TEST( testMockPermiteInterceptarChamadasParaMetodoDaClasseDeProducao );
	CPPUNIT_TEST( testMockFalhaSeExpectationsNaoForemRealizadas );
	CPPUNIT_TEST( testMockNaoFalhaSeExpectationsForemRealizadas );
	CPPUNIT_TEST( testMockPermiteMetodosComUmParametro );
	CPPUNIT_TEST( testMockFazVerificacoesQuandoEhDeletado );
	CPPUNIT_TEST( testMockGuardaArgumentosPassado );
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
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp()
  {
  }

protected:

	void testMockPermiteDefinirExpectationsParaMetodosDaClasseDeProducao()
	{
		/*MockClass mock;
		mock.Expect<int>("foo");
		CPPUNIT_ASSERT_EQUAL((size_t)1, mock.GetRegistry<int>()["foo"]->GetTimesExpected());*/
	}

	void testMockPermiteInterceptarChamadasParaMetodoDaClasseDeProducao()
	{
		/*MockClass mock;
		mock.foo();
		CPPUNIT_ASSERT_EQUAL((size_t)1, mock.GetRegistry<int>()["foo"]->GetTimesCalled());		*/
	}

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


//		CPPUNIT_ASSERT_THROW(mock.Expect<int>("foo")->Times(1), std::runtime_error);
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
		//CPPUNIT_ASSERT_NO_THROW(mock.Expect<int>("foo")->Times(1));
	}

	void testMockPermiteMetodosComUmParametro()
	{
		/*MockClass mock;

		mock.Expect("param1");
		mock.param1(1);

		CPPUNIT_ASSERT_NO_THROW(mock.Verify());*/
	}

	void testMockGuardaArgumentosPassado()
	{
		/*MockClass mock;
		
		mock.param1(1);

		int p1= mock.carnaparam1.GetCalls()[0]->GetParam1();
		CPPUNIT_ASSERT_EQUAL(1, p1);

      EXPECT(mock, param1)->WithParams(Equal<int>(1))->Times(1);*/

		//mock.Expect<int, int>("param1")->WithParams(Equal<int>(1)).Times(1);
	}

	void testMockPermiteExpectationsNosParametrosDoMetodo()
	{		
      try 
      {  
         {
            MockClass mock;
		      mock.param1(1);

            EXPECT(mock, param1)->WithParams(Equal<int>(1)).Times(1);

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
            EXPECT(mock, param1)->WithParams(Equal<int>(5)).Times(1);
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

      EXPECT(mock, param1Double)->WithParams(Equal<double>(20.2)).Times(1);
		//mock.Expect<int, double>("param1Double")->WithParams(Equal<double>(20.2)).Times(1);
	}

	void testMockParamString()
	{	
		MockClass mock;
		mock.param1String("mock");

      EXPECT(mock, param1String)->WithParams(Equal<std::string>("mock")).Times(1);
		/*mock.Expect<int, const std::string&>("param1String")->WithParams(Equal<std::string>("mock")).Times(1);*/
	}

	void testMockParamPtr()
	{	
		int *ptr= new int(10);
		MockClass mock;
		mock.param1Ptr(ptr);

      EXPECT(mock, param1Ptr)->WithParams(Equal<int*>(ptr)).Times(1);
		/*mock.Expect<int, int*>("param1Ptr")->WithParams(Equal<int*>(ptr)).Times(1);*/
	}

	void testMockParamRef()
	{
		int ref= 10;
		MockClass mock;
		mock.param1Ref(ref);

      EXPECT(mock, param1Ref)->WithParams(Equal<int>(ref)).Times(1);
		/*mock.Expect<int, int&>("param1Ref")->WithParams(Equal<int>(ref)).Times(1);*/
	}

	void testMockPermiteDefinirAcoesParaMetodos()
	{
		int a= 10;
		int *b= new int(20);
		MockClass mock;      
      WHEN_CALL(mock, param1Double)->WithParam(Equal<double>(20.1)).ThenReturn(10);
      WHEN_CALL(mock, param1RetornoPtr)->WithParam(Equal<int>(a)).ThenReturn(b);

		/*mock.WhenCall<int, double>("param1Double")->WithParam(Equal<double>(20.1)).ThenReturn(10);
		mock.WhenCall<int*, int&>("param1RetornoPtr")->WithParam(Equal<int>(a)).ThenReturn(b);*/

		//mock.When("param1Double")->WithParam(_)->ThenExecute(qualquerFuncao());

		CPPUNIT_ASSERT_EQUAL(10, mock.param1Double(20.1));
		CPPUNIT_ASSERT_EQUAL(20, *mock.param1RetornoPtr(a));

		delete b;

		//CPPUNIT_ASSERT_EQUAL(10, mock.param1Double(20.1));
	}

	void testDefinirAcoesComPlaceHolders()
	{
		MockClass mock;
      WHEN_CALL(mock, param1Double)->WithParam(Any<double>()).ThenReturn(10);
		//mock.WhenCall<int, double>("param1Double")->WithParam(Any<double>()).ThenReturn(10);

//		mock.WhenCall<int, int>("param1")->WithParam(LessThan<int>(10)).ThenReturn(2);

		CPPUNIT_ASSERT_EQUAL(10, mock.param1Double(1));
		CPPUNIT_ASSERT_EQUAL(10, mock.param1Double(12));
		CPPUNIT_ASSERT_EQUAL(10, mock.param1Double(1282828));

		/*CPPUNIT_ASSERT_EQUAL(2, mock.param1(1));
		CPPUNIT_ASSERT_EQUAL(2, mock.param1(9));*/
	}

	void testMetodoComDoisParametros()		
	{
		MockClass mock;

		int a= 10;

      WHEN_CALL(mock, param2)->WithParam(Equal<int>(10), Equal<std::string>("ola"))
         .ThenReturn(10.2);

		/*mock.WhenCall<double, int&, const std::string&>("param2")
			->WithParam(Equal<int>(10), Equal<std::string>("ola"))
			.ThenReturn(10.2);*/
		
		const std::string ola("ola");

		CPPUNIT_ASSERT_DOUBLES_EQUAL(10.2, mock.param2(a, ola), 0.01);

      EXPECT(mock, param2)->WithParams(Equal<int>(a), Equal<std::string>("ola")).Times(1);
	}

	void testMetodosSemRetorno()
	{
		MockClass mock;
		mock.metodoSemRetornoSemParam();

      EXPECT(mock, metodoSemRetornoSemParam)->Times(1);
		//mock.Expect<void>("metodoSemRetornoSemParam")->Times(1);
	}

   void testMetodoSemRetornoUmParametro()
   {
      int a= 1;
      MockClass mock;
      mock.metodoSemRetornoComUmParam(a);

      EXPECT(mock, metodoSemRetornoComUmParam)->WithParams(Equal<int>(a)).Times(1);
      //mock.Expect<void, int&>("metodoSemRetornoComUmParam")->WithParams(Equal<int>(a)).Times(1);
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
         //paramPassado= _param;
         //return 1;
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
      WHEN_CALL(mock, metodoSemRetornoComDoisParam)->WithParam(Equal<char*>("2"), Equal<int>(10))
         .ThenExecute(boost::bind(&Dummy::dummyMethodWithReturnAndParam, &dummy, _1, _2));

      mock.metodoSemRetornoComDoisParam("2", 10);

      CPPUNIT_ASSERT(dummy.executou);
      EXPECT(mock, metodoSemRetornoComDoisParam)->WithParams(Equal<char*>("2"), Equal<int>(10)).Times(1);
   }
};

CPPUNIT_TEST_SUITE_REGISTRATION( MockTest );