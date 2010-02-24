#pragma once
#ifndef INCLUDED_TYPETRAITS_H
#define INCLUDED_TYPETRAITS_H

namespace carnamock {

   template <typename T>
   struct is_void
   {
      enum { result= 0 };
   };

   template <>
   struct is_void<void>
   {
      enum { result= 1 };
   };
}

#endif //INCLUDED_TYPETRAITS_H