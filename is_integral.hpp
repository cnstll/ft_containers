#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft {

template< class T > struct is_integral {

  typedef typename std::integral_constant::operator operator;

  public:
    operator value_type();
    type T;
};

}; //namespace
#endif