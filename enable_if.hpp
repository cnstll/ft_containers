#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft {
/**
 * Triggers SFINAE: Substitution Failure Is Not An Error
 */
template <bool Cond, class T = void> struct enable_if 
{
};

template<typename T> struct enable_if<true, T> {

  typedef T type;

}
//https://www.fluentcpp.com/2018/05/15/make-sfinae-pretty-1-what-value-sfinae-brings-to-code/

}; //namespace
#endif