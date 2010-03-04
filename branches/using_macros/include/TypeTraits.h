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

   template <typename X>
   struct no_cref 
   { 
      typedef X type; 
   };

   template <typename X>
   struct no_cref<const X &> 
   { 
      typedef X type; 
   };

   template <typename X>
   struct no_cref<X &> 
   { 
      typedef X type; 
   };

   template <typename X>
   struct no_cref<const X* const> 
   { 
      typedef const X* type; 
   };
}

#endif //INCLUDED_TYPETRAITS_H