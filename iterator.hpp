#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <cstddef>

namespace ft {

struct output_iterator_tag {};
struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Category, class T, class Distance = std::ptrdiff_t,
          class Pointer = T*, class Reference = T&>
  struct iterator {

    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
  };

template <class Iterator>
  class iterator_traits {

    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
  };

template <class T>
  class iterator_traits<T*>{

    typedef	std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef	random_access_iterator_tag iterator_category;
  };

template <class T>
  class iterator_traits<const T*>{

    typedef	std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef	random_access_iterator_tag iterator_category;
  };

template <class T> 
class vectorIterator : public ft::iterator<random_access_iterator_tag, T>
{
  public:
    typedef random_access_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    //typedef const T value_type;
    typedef T* pointer;
    typedef T& reference;
  /* Is default-constructible, copy-constructible, copy-assignable and destructible */
    vectorIterator() {}
    vectorIterator(T* i) : p(i) {}
    vectorIterator(const vectorIterator& src) {*this = src;}
    vectorIterator &operator=(const vectorIterator& rhs) { 
      if (this != &rhs)
        this->p = rhs.p; 
      return *this;
    }
    ~vectorIterator(void) {}
  /*Can be compared for equivalence using the equality/inequality operators*/
    bool operator==(const vectorIterator& rhs) const {return p==rhs.p;}
    bool operator!=(const vectorIterator& rhs) const {return !(p==rhs.p);}

  /*Can be dereferenced as an lvalue (if in a dereferenceable state).*/
    T& operator*() {return *p;}

  /*Can be incremented (if in a dereferenceable state).*/
    vectorIterator& operator++() {++p; return *this;}
    vectorIterator operator++(int) {vectorIterator tmp(*this); operator++(); return tmp;}

  /*Can be incremented (if in a dereferenceable state).*/
    vectorIterator& operator--() {--p; return *this;}
    vectorIterator operator--(int) {vectorIterator tmp(*this); operator--(); return tmp;}
  /*Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another.*/
    vectorIterator operator+(difference_type n) {T* tmp = p; return tmp += n;}
    vectorIterator operator-(difference_type n) {T* tmp = p; return tmp -= n;}
    difference_type operator-(const vectorIterator &It) {return It->p - this->p;}
  /*Supports compound assignment operations += and -= */
    vectorIterator& operator+=(difference_type n) {
      difference_type m = n;
      if (m >= 0) while (m--) ++p;
      else while (m++) --p;
      return p;
    }
    vectorIterator& operator-=(difference_type n) {return p += -n;}
  /*Can be compared with inequality relational operators (<, >, <= and >=).*/
  /*Supports the offset dereference operator ([])	*/
  private:
    T* p;
  };
}; // NAMESPACE
#endif
