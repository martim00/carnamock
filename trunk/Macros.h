#ifndef INCLUDED_MACROS_H
#define INCLUDED_MACROS_H

//#define VOID_METHOD0(methodName) void methodName() { this->registerCallForVoidMethod<void>(#methodName); } 
//#define VOID_METHOD1(methodName, p1) void methodName(p1 p1Value) { this->registerCallForVoidMethod<void, p1>(#methodName, p1Value); } 
//#define VOID_METHOD2(methodName, p1, p2) void methodName(p1 p1Value, p2 p2Value) { this->registerCallForVoidMethod<void, p1, p2>(#methodName, p1Value, p2Value); } 
//#define VOID_METHOD3(methodName, p1, p2, p3) void methodName(p1 p1Value, p2 p2Value, p3 p3Value) { this->registerCallForVoidMethod<void, p1, p2, p3>(#methodName, p1Value, p2Value, p3Value); } 
//#define VOID_METHOD4(methodName, p1, p2, p3, p4) void methodName(p1 p1Value, p2 p2Value, p3 p3Value, p4 p4Value) { this->registerCallForVoidMethod<void, p1, p2, p3, p4>(#methodName, p1Value, p2Value, p3Value, p4Value); } 

#define VOID_METHOD0(returnType, methodName) returnType methodName() { this->registerCallForVoidMethod<returnType>(#methodName); } 
#define VOID_METHOD1(returnType, methodName, p1) returnType methodName(p1 p1Value) { this->registerCallForVoidMethod<returnType, p1>(#methodName, p1Value); } 
#define VOID_METHOD2(returnType, methodName, p1, p2) returnType methodName(p1 p1Value, p2 p2Value) { this->registerCallForVoidMethod<returnType, p1, p2>(#methodName, p1Value, p2Value); } 
#define VOID_METHOD3(returnType, methodName, p1, p2, p3) returnType methodName(p1 p1Value, p2 p2Value, p3 p3Value) { this->registerCallForVoidMethod<returnType, p1, p2, p3>(#methodName, p1Value, p2Value, p3Value); } 
#define VOID_METHOD4(returnType, methodName, p1, p2, p3, p4) returnType methodName(p1 p1Value, p2 p2Value, p3 p3Value, p4 p4Value) { this->registerCallForVoidMethod<returnType, p1, p2, p3, p4>(#methodName, p1Value, p2Value, p3Value, p4Value); } 

#define RETURN_METHOD0(returnType, methodName) returnType methodName() { return this->registerCallForMethod<returnType>(#methodName); }  
#define RETURN_METHOD1(returnType, methodName, p1) returnType methodName(p1 p1Value) { return this->registerCallForMethod<returnType, p1>(#methodName, p1Value); }  
#define RETURN_METHOD2(returnType, methodName, p1, p2) returnType methodName(p1 p1Value, p2 p2Value) { return this->registerCallForMethod<returnType, p1, p2>(#methodName, p1Value, p2Value); }  
#define RETURN_METHOD3(returnType, methodName, p1, p2, p3) returnType methodName(p1 p1Value, p2 p2Value, p3 p3Value) { return this->registerCallForMethod<returnType, p1, p2, p3>(#methodName, p1Value, p2Value); }  
#define RETURN_METHOD4(returnType, methodName, p1, p2, p3, p4) returnType methodName(p1 p1Value, p2 p2Value, p3 p3Value, p4 p4Value) { return this->registerCallForMethod<returnType, p1, p2, p3, p3>(#methodName, p1Value, p2Value, p3Value, p4Value); }  


#endif