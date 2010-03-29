#pragma once
#ifndef INCLUDED_MOCKINFO_H
#define INCLUDED_MOCKINFO_H

#include <string>
#include <set>

namespace carnamock {

   namespace internal {

      /**
      *  A info struct that stores all informations needed for a mock instance at runtime
      */ 
      class MockInfo
      {
      public:
         MockInfo() : isNiceMock(false), isNiceReport(false) {}

         /**
         *  Is the mock a nice mock?
         *  @return bool
         */ 
         bool IsNiceMock() const { return isNiceMock; }

         /**
         *  Sets if it is a nice mock
         *  @param bool _isNiceMock
         */ 
         void IsNiceMock(bool _isNiceMock) { isNiceMock = _isNiceMock; }

         /**
         *  Is the mock a nice report mock?
         *  @return bool
         */ 

         bool IsNiceReport() const { return isNiceReport; }
         /**
         *  Sets if it is a nice report mock. 
         *  @see NiceReportMock
         *  @param bool _isNiceReportMock
         */ 
         void IsNiceReport(bool val) { isNiceReport = val; }

         /**
         *  Append a log to this mock info         
         *  @param const std::string & _log
         */ 
         void AddLog(const std::string &_log)
         {
            log.append(_log);
         }

         /**
         *  Get the log for this mock object
         *  @return std::string
         */ 
         std::string GetLog()
         {
            return log;
         }

         /**
         *  Tells that the mockedMethod passed are in use..
         *  @param const void * mockedMethod
         */ 
         void AddMockedMethodInUse(const void *mockedMethod)
         {
            mockedMethods.insert(mockedMethod);
         }

         /**
         *  Tells that the mockedMethod are not longer in use...
         *  @param const void * mockedMethod
         */ 
         void RemoveMockedMethodInUse(const void *mockedMethod)
         {
            mockedMethods.erase(mockedMethod);            
         }

         /**
         *  Get the number of mocked methods in use...
         *  @return size_t
         */ 
         size_t GetNrMockedMethodsInUse()
         {
            return mockedMethods.size();
         }

      private:
         std::string log;
         bool isNiceMock;
         bool isNiceReport;
         std::set<const void *> mockedMethods;
      };

   } //namespace internal

} //namespace carnamock

#endif //INCLUDED_MOCKINFO_H