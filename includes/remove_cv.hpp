#ifndef REMOVE_CV_HPP
#define REMOVE_CV_HPP

namespace ft {

/**
 * @brief Provides the member typedef type which is the same as T, except that its topmost cv-qualifiers are removed.
 *        Removes the topmost const, or the topmost volatile, or both, if present. 
 * 
 * @tparam T the type T without cv-qualifier 
 */
template< class T > struct remove_cv                   { typedef T type; };
template< class T > struct remove_cv<const T>          { typedef T type; };
template< class T > struct remove_cv<volatile T>       { typedef T type; };
template< class T > struct remove_cv<const volatile T> { typedef T type; };

}; //namespace
#endif