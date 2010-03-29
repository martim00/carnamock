#pragma once
#ifndef INCLUDED_MOCKMAP_H
#define INCLUDED_MOCKMAP_H

#include "MockInfo.h"
#include <map>

namespace carnamock {

	namespace internal {

		class MockMap
		{
         static std::map<const void*, MockInfo> mockMap;
		public:         

			static void DisableVerificationsOnMock(const void* mockObject)
			{
				mockMap[mockObject].IsNiceMock(true);
			}

			static void ClearNiceMock(const void *mockObject)
			{
            mockMap[mockObject].IsNiceMock(false);
			}

			static bool IsNiceMock(const void *mockObject) 
			{
            if (mockMap.find(mockObject) != mockMap.end())
					return mockMap[mockObject].IsNiceMock();
				return false;
			}

         static void SetNiceReportMock(const void *mockObject)
         {
            mockMap[mockObject].IsNiceReport(true);
         }

         static bool IsNiceReportMock(const void *mockObject)
         {
            return mockMap[mockObject].IsNiceReport();
         }

         static void AddLog(const void *mockObject, const std::string &_log)
         {
            mockMap[mockObject].AddLog(_log);
         }

         static void ShowLog(const void *mockObject)
         {            
            std::runtime_error e(mockMap[mockObject].GetLog());
            throw e;
         }

         static void AddMockedMethod(const void *mockObject, const void *mockedMethod)
         {
            mockMap[mockObject].AddMockedMethodInUse(mockedMethod);
         }

         static void DeleteMockedMethod(const void *mockObject, const void *mockedMethod)
         {
            mockMap[mockObject].RemoveMockedMethodInUse(mockedMethod);
            if (mockMap[mockObject].GetNrMockedMethodsInUse() == 0)
            {
               ShowLog(mockObject);
               mockMap.erase(mockObject);
            }
         }
		};

	} //namespace internal

} //namespace carnamock

#endif 