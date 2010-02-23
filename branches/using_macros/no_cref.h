#ifndef INCLUDED_NOCREF_H
#define INCLUDED_NOCREF_H

template <typename X>
struct no_cref { typedef X type; };

template <typename X>
struct no_cref<const X &> { typedef X type; };

template <typename X>
struct no_cref<X &> { typedef X type; };

template <typename X>
struct no_cref<const X* const> { typedef const X* type; };

//template <typename X>
//struct no_cref<const X* > { typedef X* type; };



#endif 