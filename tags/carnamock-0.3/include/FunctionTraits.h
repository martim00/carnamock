#pragma once
#ifndef INCLUDED_FUNCTIONTRAITS_H
#define INCLUDED_FUNCTIONTRAITS_H

#include "NullType.h"
#include "TypeTraits.h"

namespace carnamock {

template <class ReturnType= nulltype, class Param1= nulltype, class Param2= nulltype, class Param3= nulltype, class Param4= nulltype, class Param5=nulltype> 
struct FunctionTraits;

template <class ReturnType>
struct FunctionTraits<ReturnType>
{
   enum { NrParams= 0 };
   typedef ReturnType ReturnType;
   typedef carnamock::is_void<ReturnType> IsVoidReturn;
   typedef boost::function0<ReturnType> FunctionType;
};

template <class ReturnType, class Param1>
struct FunctionTraits<ReturnType, Param1>
{
   enum { NrParams= 1 };
   typedef ReturnType ReturnType;
   typedef Param1 Param1;
   typedef carnamock::is_void<ReturnType> IsVoidReturn;
   typedef boost::function1<ReturnType, Param1> FunctionType;
};

template <class ReturnType, class Param1, class Param2>
struct FunctionTraits<ReturnType, Param1, Param2>
{
   enum { NrParams= 2 };
   typedef ReturnType ReturnType;
   typedef Param1 Param1;
   typedef Param2 Param2;
   typedef carnamock::is_void<ReturnType> IsVoidReturn;
   typedef boost::function2<ReturnType, Param1, Param2> FunctionType;
};

template <class ReturnType, class Param1, class Param2, class Param3>
struct FunctionTraits<ReturnType, Param1, Param2, Param3>
{
   enum { NrParams= 3 };
   typedef ReturnType ReturnType;
   typedef Param1 Param1;
   typedef Param2 Param2;
   typedef Param3 Param3;
   typedef carnamock::is_void<ReturnType> IsVoidReturn;
   typedef boost::function3<ReturnType, Param1, Param2, Param3> FunctionType;
};


template <class ReturnType, class Param1, class Param2, class Param3, class Param4>
struct FunctionTraits<ReturnType, Param1, Param2, Param3, Param4>
{
   enum { NrParams= 4 };
   typedef ReturnType ReturnType;
   typedef Param1 Param1;
   typedef Param2 Param2;
   typedef Param3 Param3;
   typedef Param4 Param4;
   typedef carnamock::is_void<ReturnType> IsVoidReturn;
   typedef boost::function4<ReturnType, Param1, Param2, Param3, Param4> FunctionType;
};

} //namespace carnamock

#endif //INCLUDED_FUNCTIONTRAITS_H