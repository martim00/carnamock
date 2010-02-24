#ifndef INCLUDED_MACROS_H
#define INCLUDED_MACROS_H

//#define VOID_METHOD0(methodName) void methodName() { this->registerCallForVoidMethod<void>(#methodName); } 
//#define VOID_METHOD1(methodName, p1) void methodName(p1 p1Value) { this->registerCallForVoidMethod<void, p1>(#methodName, p1Value); } 
//#define VOID_METHOD2(methodName, p1, p2) void methodName(p1 p1Value, p2 p2Value) { this->registerCallForVoidMethod<void, p1, p2>(#methodName, p1Value, p2Value); } 
//#define VOID_METHOD3(methodName, p1, p2, p3) void methodName(p1 p1Value, p2 p2Value, p3 p3Value) { this->registerCallForVoidMethod<void, p1, p2, p3>(#methodName, p1Value, p2Value, p3Value); } 
//#define VOID_METHOD4(methodName, p1, p2, p3, p4) void methodName(p1 p1Value, p2 p2Value, p3 p3Value, p4 p4Value) { this->registerCallForVoidMethod<void, p1, p2, p3, p4>(#methodName, p1Value, p2Value, p3Value, p4Value); } 

#define VOID_METHOD0(returnType, methodName) returnType methodName() { carna##methodName.SetMethodName(#methodName); carna##methodName.Execute(); } CallRegistry<returnType> carna##methodName;
#define VOID_METHOD1(returnType, methodName, p1) returnType methodName(p1 p1Value) { carna##methodName.SetMethodName(#methodName); carna##methodName.Execute(p1Value); } CallRegistry<returnType, p1> carna##methodName;
#define VOID_METHOD2(returnType, methodName, p1, p2) returnType methodName(p1 p1Value, p2 p2Value) { carna##methodName.SetMethodName(#methodName); carna##methodName.Execute(p1Value, p2Value); } CallRegistry<returnType, p1, p2> carna##methodName;
#define VOID_METHOD3(returnType, methodName, p1, p2, p3) returnType methodName(p1 p1Value, p2 p2Value, p3 p3Value) { carna##methodName.SetMethodName(#methodName); carna##methodName.Execute(p1Value, p2Value, p3Value); } CallRegistry<returnType, p1, p2, p3> carna##methodName;
#define VOID_METHOD4(returnType, methodName, p1, p2, p3, p4) returnType methodName(p1 p1Value, p2 p2Value, p3 p3Value, p4 p4Value) { carna##methodName.SetMethodName(#methodName); carna##methodName.Execute(p1Value, p2Value, p3Value, p4Value); } CallRegistry<returnType, p1, p2, p3, p4> carna##methodName;

#define RETURN_METHOD0(returnType, methodName) CallRegistry<returnType> carna##methodName; returnType methodName() { carna##methodName.SetMethodName(#methodName); return carna##methodName.Execute(); } 
#define RETURN_METHOD1(returnType, methodName, p1) returnType methodName(p1 p1Value) { carna##methodName.SetMethodName(#methodName); return carna##methodName.Execute(p1Value); } CallRegistry<returnType, p1> carna##methodName;
#define RETURN_METHOD2(returnType, methodName, p1, p2) returnType methodName(p1 p1Value, p2 p2Value) { carna##methodName.SetMethodName(#methodName); return carna##methodName.Execute(p1Value, p2Value); } CallRegistry<returnType, p1, p2> carna##methodName;
#define RETURN_METHOD3(returnType, methodName, p1, p2, p3) returnType methodName(p1 p1Value, p2 p2Value, p3 p3Value) { carna##methodName.SetMethodName(#methodName); return carna#methodName.Execute(p1Value, p2Value, p3Value); } CallRegistry<returnType, p1, p2, p3> carna##methodName;
#define RETURN_METHOD4(returnType, methodName, p1, p2, p3, p4) returnType methodName(p1 p1Value, p2 p2Value, p3 p3Value, p4 p4Value) { carna##methodName.SetMethodName(#methodName); return carna##methodName.Execute(p1Value, p2Value, p3Value, p4Value); } CallRegistry<returnType, p1, p2, p3, p4> carna##methodName;


#define EXPECT(instance, methodName) instance.carna##methodName.SetMethodName(#methodName); instance.carna##methodName.Expect()

#endif