#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP
#include "integral_constant.hpp"
#include "remove_cv.hpp"

namespace ft {

/**
 * @brief Checks whether T is an integral type. Provides the member constant value which is equal to true,
 *        if T is the type bool, char, short, int, long, long long,
 *        or any implementation-defined extended integer types, including any signed, unsigned, and cv-qualified variants.
 *        Otherwise, value is equal to false. 
 * 
 * @tparam T a type to check 
 */
template < class T > struct is_integral_base: ft::false_type {};
template<> struct is_integral_base<bool>: ft::true_type {};
template<> struct is_integral_base<char>: ft::true_type {};
template<> struct is_integral_base<short int>: ft::true_type {};
template<> struct is_integral_base<int>: ft::true_type {};
template<> struct is_integral_base<long int>: ft::true_type {};
template<> struct is_integral_base<long long int>: ft::true_type {};
template<> struct is_integral_base<unsigned char>: ft::true_type {};
template<> struct is_integral_base<unsigned short int>: ft::true_type {};
template<> struct is_integral_base<unsigned int>: ft::true_type {};
template<> struct is_integral_base<unsigned long int>: ft::true_type {};
template<> struct is_integral_base<unsigned long long int>: ft::true_type {};

template<typename T> struct is_integral: is_integral_base<T> {};
//template<typename T> struct is_integral: is_integral_base<typename ft::remove_cv<T>::type> {};

}; //namespace
#endif