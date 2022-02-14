#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft {

template <bool Cond, class T = void> struct enable_if{

  typedef T type;
};

}; //namespace
#endif