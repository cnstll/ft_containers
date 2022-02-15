#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

//https://www.fluentcpp.com/2018/05/15/make-sfinae-pretty-1-what-value-sfinae-brings-to-code/
// "SFINAE in code is as pretty as a windmill in a field. That is, not very pretty.
// But like a windmill, it’s useful. 
// SFINAE helps deactivate a piece of template code depending on a condition, and that can be very convenient."
namespace ft {
/**
 * @brief Triggers SFINAE: Substitution Failure Is Not An Error
 *        If Cond is true, enable_if will provide type,
 *        Else we will have a substitution failure as no type will be provided
 *        Hence the template will be ignored
 */
template <bool Cond, class T = void> struct enable_if {};

template<typename T> struct enable_if<true, T> { typedef T type; };

}; //namespace
#endif