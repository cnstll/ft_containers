
#ifndef INTEGRAL_CONSTANT_HPP
#define INTEGRAL_CONSTANT_HPP

namespace ft {

/**
 * @brief   integral_constant wraps a static constant of specified type. It is the base class for the C++ type traits.
 * 
 */
template <class T, T v> struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T,v> type;
  operator value_type() { return value; }
};

typedef integral_constant<bool,true> true_type;
typedef integral_constant<bool,false> false_type;

}; //namespace
#endif