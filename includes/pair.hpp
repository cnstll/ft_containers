#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {
  template<
    class T1,
    class T2
  > struct pair {

  typedef	T1  first_type;
  typedef T2  second_type;

  first_type first;
  second_type second;
  pair() : first(), second() {};
  pair( const T1& x, const T2& y ) : first(x), second(y){};
  template<class U1, class U2>
    pair( const pair<U1, U2>& p ) : first(p.first), second(p.second){};
  pair& operator=( const pair& other ){
    first = other.first;
    second = other.second;
    return *this;
  };
  operator pair<const T1, T2>() const {
    return pair<const T1, const T2>(first, second);
  }

};

template<class T1, class T2>
  pair<T1,T2> make_pair( T1 t, T2 u ){ return ( pair<T1,T2>(t,u)); };

template <class T1, class T2>
  bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
    return lhs.first == rhs.first && lhs.second == rhs.second;
  }

template <class T1, class T2>
  bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
    return !(lhs == rhs);
  }

template <class T1, class T2>
  bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
    return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
  }

template <class T1, class T2>
  bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
    return !(rhs < lhs);
  }

template <class T1, class T2>
  bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
    return rhs < lhs;
  }

template <class T1, class T2>
  bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
    return !(lhs < rhs);
  }
}; //NAMESPACE
#endif