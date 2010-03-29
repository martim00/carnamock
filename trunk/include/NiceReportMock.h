#pragma once
#ifndef INCLUDED_NICEREPORTMOCK_H
#define INCLUDED_NICEREPORTMOCK_H

#include "CarnaUtils.h"


/**
*  The NiceReportMock shows all expectations not accepted once in the end.
*/ 
template <class MockClass>
class NiceReportMock : public MockClass
{
public:
   NiceReportMock() {
      carnamock::internal::MockMap::SetNiceReportMock(
         implicit_cast<MockClass*>(this));      
   }

   template <typename A1>
   explicit NiceReportMock(const A1& a1) : MockClass(a1) {
      carnamock::internal::MockMap::SetNiceReportMock(
         implicit_cast<MockClass*>(this)
         );
   }
   template <typename A1, typename A2>
   NiceReportMock(const A1& a1, const A2& a2) : MockClass(a1, a2) {
      carnamock::internal::MockMap::SetNiceReportMock(
         implicit_cast<MockClass*>(this)
         );  
   }

   template <typename A1, typename A2, typename A3>
   NiceReportMock(const A1& a1, const A2& a2, const A3& a3) : MockClass(a1, a2, a3) {
      carnamock::internal::MockMap::SetNiceReportMock(
         implicit_cast<MockClass*>(this)
         );
   }

   template <typename A1, typename A2, typename A3, typename A4>
   NiceReportMock(const A1& a1, const A2& a2, const A3& a3,
      const A4& a4) : MockClass(a1, a2, a3, a4) {
         carnamock::internal::MockMap::SetNiceReportMock(
            implicit_cast<MockClass*>(this)
            );
   }

   template <typename A1, typename A2, typename A3, typename A4, typename A5>
   NiceReportMock(const A1& a1, const A2& a2, const A3& a3, const A4& a4,
      const A5& a5) : MockClass(a1, a2, a3, a4, a5) {
         carnamock::internal::MockMap::SetNiceReportMock(
            implicit_cast<MockClass*>(this)
            );
   }

   template <typename A1, typename A2, typename A3, typename A4, typename A5,
      typename A6>
      NiceReportMock(const A1& a1, const A2& a2, const A3& a3, const A4& a4,
      const A5& a5, const A6& a6) : MockClass(a1, a2, a3, a4, a5, a6) {
         carnamock::internal::MockMap::SetNiceReportMock(
            implicit_cast<MockClass*>(this)
            );
   }

   template <typename A1, typename A2, typename A3, typename A4, typename A5,
      typename A6, typename A7>
      NiceReportMock(const A1& a1, const A2& a2, const A3& a3, const A4& a4,
      const A5& a5, const A6& a6, const A7& a7) : MockClass(a1, a2, a3, a4, a5,
      a6, a7) {
         carnamock::internal::MockMap::SetNiceReportMock(
            implicit_cast<MockClass*>(this)
            );
   }

   template <typename A1, typename A2, typename A3, typename A4, typename A5,
      typename A6, typename A7, typename A8>
      NiceReportMock(const A1& a1, const A2& a2, const A3& a3, const A4& a4,
      const A5& a5, const A6& a6, const A7& a7, const A8& a8) : MockClass(a1,
      a2, a3, a4, a5, a6, a7, a8) {
         carnamock::internal::MockMap::SetNiceReportMock(
            implicit_cast<MockClass*>(this)
            );
   }

   template <typename A1, typename A2, typename A3, typename A4, typename A5,
      typename A6, typename A7, typename A8, typename A9>
      NiceReportMock(const A1& a1, const A2& a2, const A3& a3, const A4& a4,
      const A5& a5, const A6& a6, const A7& a7, const A8& a8,
      const A9& a9) : MockClass(a1, a2, a3, a4, a5, a6, a7, a8, a9) {
         carnamock::internal::MockMap::SetNiceReportMock(
            implicit_cast<MockClass*>(this)
            );
   }

   template <typename A1, typename A2, typename A3, typename A4, typename A5,
      typename A6, typename A7, typename A8, typename A9, typename A10>
      NiceReportMock(const A1& a1, const A2& a2, const A3& a3, const A4& a4,
      const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9,
      const A10& a10) : MockClass(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) {
         carnamock::internal::MockMap::SetNiceReportMock(
            implicit_cast<MockClass*>(this)
            );
   }

   virtual ~NiceReportMock() {
   }
};


#endif //INCLUDED_NICEREPORTMOCK_H