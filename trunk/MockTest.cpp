#include <cppunit/extensions/HelperMacros.h>

#include "Mock.h"
#include <boost/bind.hpp>

struct ProductionClass {
	void foo() {}
	void param1(int) {}
};

struct MockClass : public ProductionClass, public MockMixin
{
	METHOD0(void, foo);
	METHOD1(void, param1, int);
};


class MockTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( MockTest );
	//CPPUNIT_TEST( testMockEhDoMesmoTipoDaClasseDeProducao );
	//CPPUNIT_TEST( testMockearClasseComConstrutorComUmParametro );
	//CPPUNIT_TEST( testMockearClasseComConstrutorComDoisParametros );
	CPPUNIT_TEST( testMockPermiteDefinirExpectationsParaMetodosDaClasseDeProducao );
	CPPUNIT_TEST( testMockPermiteInterceptarChamadasParaMetodoDaClasseDeProducao );
	CPPUNIT_TEST( testMockFalhaSeExpectationsNaoForemRealizadas );
	CPPUNIT_TEST( testMockNaoFalhaSeExpectationsForemRealizadas );
	CPPUNIT_TEST( testMockPermiteMetodosComUmParametro );

   CPPUNIT_TEST( testMockPermiteDelegarChamadasParaFuncoes );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp()
  {
  }

protected:

	//void testMockEhDoMesmoTipoDaClasseDeProducao()
	//{
	//	struct DummyClass {};

	//	Mock<DummyClass> mock;

	//	DummyClass *dummyClass= dynamic_cast<DummyClass*>(&mock);
	//	CPPUNIT_ASSERT(NULL != dummyClass);
	//}

	//void testMockearClasseComConstrutorComUmParametro()
	//{
	//	struct DummyClass {
	//		DummyClass(int) {}
	//	};

	//	Mock<DummyClass> mock(1);
	//}

	//void testMockearClasseComConstrutorComDoisParametros()
	//{
	//	struct DummyClass {
	//		DummyClass(int, double) {}
	//	};

	//	Mock<DummyClass> mock(1,1.);
	//}

	void testMockPermiteDefinirExpectationsParaMetodosDaClasseDeProducao()
	{
		MockClass mock;
		mock.Expect("foo");		
		CPPUNIT_ASSERT_EQUAL((size_t)1, mock.GetMethodCalls()["foo"]->GetTimesExpected());
	}

	void testMockPermiteInterceptarChamadasParaMetodoDaClasseDeProducao()
	{
		MockClass mock;
		mock.foo();
		CPPUNIT_ASSERT_EQUAL((size_t)1, mock.GetMethodCalls()["foo"]->GetTimesCalled());		
	}

	void testMockFalhaSeExpectationsNaoForemRealizadas()
	{
		MockClass mock;
		mock.Expect("foo");

		CPPUNIT_ASSERT_THROW(mock.Verify(), std::runtime_error);		
	}

	void testMockNaoFalhaSeExpectationsForemRealizadas()
	{
		MockClass mock;
		mock.Expect("foo");
		mock.foo();

		CPPUNIT_ASSERT_NO_THROW(mock.Verify());
	}

	void testMockPermiteMetodosComUmParametro()
	{
		MockClass mock;

		mock.Expect("param1");
		mock.param1(1);

		CPPUNIT_ASSERT_NO_THROW(mock.Verify());
	}

	void testMockPermiteExpectationsNosParametrosDoMetodo()
	{
		/*MockClass mock;

		mock.Expect("param1", 1);
		mock.param1(1);*/
	}


   struct dummyImpl
   {
      dummyImpl() : chamou(false) {}
      bool chamou;

      void dummyImplementation()
      {
         chamou= true;
      }
      
   };

   void testMockPermiteDelegarChamadasParaFuncoes()
   {  
      MockClass mock;

      dummyImpl dummy;
      mock.OnCall("foo", boost::bind(&dummyImpl::dummyImplementation, &dummy));

      mock.foo();
      CPPUNIT_ASSERT(dummy.chamou);
   }
};

CPPUNIT_TEST_SUITE_REGISTRATION( MockTest );