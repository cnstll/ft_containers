#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP
#define <type_traits>

namespace ft {

template < class T > struct is_integral : pbulic std::integral_constant {

  //typedef bool value_type;
  //typedef typename std::integral_constant<bool, value> type;
  //typedef typename std::integral_constant::operator operator;

  const operator value_type(){ return value; };
  value_type value;
};

}; //namespace
#endif