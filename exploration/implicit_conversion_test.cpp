#include <iostream>
template <typename T>
class poinTer;

template <typename T>
class constPoinTer {
  public:
    T *p;
    constPoinTer(){}
    constPoinTer(T *i) : p(i){}
    constPoinTer(const constPoinTer &other){ *this = other;}
    constPoinTer(const poinTer<T> &other) : p(other.p){}
    constPoinTer operator= (const constPoinTer &rhs){this->p = rhs.p; return *this;}
    ~constPoinTer(){}
  template<typename _T>
    friend bool operator== (const constPoinTer<_T>& lhs, const constPoinTer<_T>&rhs);
    friend std::ptrdiff_t operator- (const constPoinTer& lhs, const constPoinTer&rhs){ return (lhs.p - rhs.p); }
};
template<typename T>
  bool operator== (const constPoinTer<T>& lhs, const constPoinTer<T>&rhs){ return lhs.p == rhs.p; }
template<typename T>
  bool operator!= (const constPoinTer<T>& lhs, const constPoinTer<T>&rhs){ return !operator== (lhs.p,rhs.p); }


template <typename T>
class poinTer {
  public:
    T *p;
    poinTer(){}
    poinTer(T *i) : p(i){}
    poinTer(const poinTer &other){ *this = other;}
    poinTer operator= (const poinTer &rhs){this->p = rhs.p; return *this;}
    ~poinTer(){}
    template <typename _T>
    friend bool operator== (const poinTer<_T>& lhs, const poinTer<_T>&rhs);
    //template <typename _T>
    friend std::ptrdiff_t operator- (const poinTer& lhs, const poinTer&rhs){ return (lhs.p - rhs.p); }
};
template<typename T>
  bool operator== (const poinTer<T>& lhs, const poinTer<T>&rhs){ return lhs.p == rhs.p; }
template<typename T>
  bool operator!= (const poinTer<T>& lhs, const poinTer<T>&rhs){ return !operator== (lhs.p,rhs.p); }



int main(){

  int *p;
  int *r;
  int a = 42;
  int b = 21;
  p = &a;
  r = &b;
  constPoinTer<int> ptr1(p);
  poinTer<int> ptr2(r);
  std::cout << (ptr1 == ptr2) << std::endl;
  std::cout << (ptr1 != ptr2) << std::endl;
  std::cout << (ptr1- ptr2) << std::endl;
  std::cout << (ptr2 - ptr1) << std::endl;

  return 0;
}