#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <cstddef>
#include <iostream>

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
  struct iterator_traits {

    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
  };

template <class T>
  struct iterator_traits<T*>{

    typedef	std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef	random_access_iterator_tag iterator_category;
  };

template <class T>
  struct iterator_traits<const T*>{

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
    typedef T* pointer;
    typedef T& reference;
  /* Is default-constructible, copy-constructible, copy-assignable and destructible */
    vectorIterator() {}
    vectorIterator(T* i) : p(i) {}
    vectorIterator(const vectorIterator& other) {*this = other;}
    vectorIterator &operator=(const vectorIterator& rhs) { 
      if (this != &rhs)
        this->p = rhs.p; 
      return *this;
    }
    ~vectorIterator(void) {}

  /*Can be dereferenced as an lvalue (if in a dereferenceable state).*/
    reference operator*() {return *p;}
    pointer operator->() {return p;}

  /*Supports the offset dereference operator ([])	*/
    reference operator[](difference_type n) {return *(p + n);}
  /*Can be incremented (if in a dereferenceable state).*/
    vectorIterator& operator++() {++p; return *this;}
    vectorIterator operator++(int) {vectorIterator tmp(*this); operator++(); return tmp;}

  /*Can be incremented (if in a dereferenceable state).*/
    vectorIterator& operator--() {--p; return *this;}
    vectorIterator operator--(int) {vectorIterator tmp(*this); operator--(); return tmp;}
  /*Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another.*/
    vectorIterator operator+(difference_type n) {T* tmp = p; return vectorIterator(tmp += n);}

    friend vectorIterator operator+(difference_type n, const vectorIterator& op) {T* tmp = op.p; tmp += n; return vectorIterator(tmp);}

    vectorIterator operator-(difference_type n) { vectorIterator it = this->p; return it -= n;}

    friend vectorIterator operator-(difference_type n, const vectorIterator& op) {T* tmp = op.p; tmp -= n; return vectorIterator(tmp);}

    friend difference_type operator-(const vectorIterator &lIt, const vectorIterator &rIt) {return lIt.p - rIt.p;}
  /*Supports compound assignment operations += and -= */
    vectorIterator& operator+=(difference_type n) {
      difference_type m = n;
      if (m >= 0) while (m--) ++p;
      else while (m++) --p;
      return (*this);
    }
    vectorIterator& operator-=(difference_type n) { return operator+=(-n); }

  /*Can be compared for equivalence using the equality/inequality operators*/
    friend bool operator==(const vectorIterator& lhs, const vectorIterator& rhs) { return lhs.p == rhs.p; };
    friend bool operator!=(const vectorIterator& lhs, const vectorIterator& rhs) { return !operator==(lhs, rhs); };
  /*Can be compared with inequality relational operators (<, >, <= and >=).*/
    friend bool operator< (const vectorIterator& lhs, const vectorIterator& rhs) { return lhs.p < rhs.p; };
    friend bool operator> (const vectorIterator& lhs, const vectorIterator& rhs) { return operator<(rhs, lhs); };
    friend bool operator<=(const vectorIterator& lhs, const vectorIterator& rhs) { return !operator>(lhs, rhs); };
    friend bool operator>=(const vectorIterator& lhs, const vectorIterator& rhs) { return !operator<(lhs, rhs); };
  /* The underlying pointer to data hold in the container */
    T* p;
  };

template <class T> 
class constVectorIterator : public ft::iterator<random_access_iterator_tag, T>
{
  public:
    typedef random_access_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    typedef const T value_type;
    typedef const T* pointer;
    typedef const T& reference;
  /* Is default-constructible, copy-constructible, copy-assignable and destructible */
    constVectorIterator() {}
    constVectorIterator(T* i) : p(i) {}
    constVectorIterator(const constVectorIterator& other) {*this = other;}
    constVectorIterator(const vectorIterator<T>& other) : p(other.p){}
    constVectorIterator &operator=(const constVectorIterator& rhs) { 
      this->p = rhs.p; 
      return *this;
    }
    ~constVectorIterator() {}

  /*Can be dereferenced as an lvalue (if in a dereferenceable state).*/
    reference operator*() const {return *p;}
    pointer operator->() const {return p;}

  /*Supports the offset dereference operator ([])	*/
    reference operator[](difference_type n) const {return *(p + n);}
  /*Can be incremented (if in a dereferenceable state).*/
    constVectorIterator& operator++() {++p; return *this;}
    constVectorIterator operator++(int) {constVectorIterator tmp(*this); operator++(); return tmp;}

  /*Can be incremented (if in a dereferenceable state).*/
    constVectorIterator& operator--() {--p; return *this;}
    constVectorIterator operator--(int) {constVectorIterator tmp(*this); operator--(); return tmp;}
  /*Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another.*/
    constVectorIterator operator+(difference_type n) {T* tmp = p; return constVectorIterator(tmp += n);}
    friend constVectorIterator operator+(difference_type n, const constVectorIterator& op) {T* tmp = op.p; tmp += n; return constVectorIterator(tmp);}

    constVectorIterator operator-(difference_type n) { constVectorIterator it = this->p; return it -= n;}
    friend constVectorIterator operator-(difference_type n, const constVectorIterator& op) {T* tmp = op.p; tmp -= n; return constVectorIterator(tmp);}

    friend difference_type operator-(const constVectorIterator &lIt, const constVectorIterator &rIt) {return lIt.p - rIt.p;}
  /*Supports compound assignment operations += and -= */
    constVectorIterator& operator+=(difference_type n) {
      difference_type m = n;
      if (m >= 0) while (m--) ++p;
      else while (m++) --p;
      return (*this);
    }
    constVectorIterator& operator-=(difference_type n) { return operator+=(-n); }

  /*Can be compared for equivalence using the equality/inequality operators*/
    friend bool operator==(const constVectorIterator& lhs, const constVectorIterator& rhs) { return lhs.p == rhs.p; };
    friend bool operator!=(const constVectorIterator& lhs, const constVectorIterator& rhs) { return !operator==(lhs, rhs); };
  /*Can be compared with inequality relational operators (<, >, <= and >=).*/
    friend bool operator< (const constVectorIterator& lhs, const constVectorIterator& rhs) { return lhs.p < rhs.p; };
    friend bool operator> (const constVectorIterator& lhs, const constVectorIterator& rhs) { return operator<(rhs, lhs); };
    friend bool operator<=(const constVectorIterator& lhs, const constVectorIterator& rhs) { return !operator>(lhs, rhs); };
    friend bool operator>=(const constVectorIterator& lhs, const constVectorIterator& rhs) { return !operator<(lhs, rhs); };

  /* The underlying pointer to data hold in the container */
    T* p;
  };

/**
 * @brief ft::reverse_iterator is an iterator adaptor that reverses the direction of a given iterator,
          which must be at least a LegacyBidirectionalIterator. In other words, when provided with a bidirectional iterator,
          ft::reverse_iterator produces a new iterator that moves from the end to the beginning of the sequence defined by the underlying bidirectional iterator.
 * 
 * @tparam Iter 
 */
template< class Iter >
class reverse_iterator {
  public:
    typedef Iter iterator_type;
    typedef typename iterator_traits<Iter>::iterator_category iterator_category;
    typedef typename iterator_traits<Iter>::value_type value_type;
    typedef typename iterator_traits<Iter>::difference_type difference_type;
    typedef typename iterator_traits<Iter>::pointer pointer;
    typedef typename iterator_traits<Iter>::reference reference;

    reverse_iterator(){};
    explicit reverse_iterator( iterator_type x ) : current(x) {};
    template< class U >
    reverse_iterator( const reverse_iterator<U>& other ) { *this = other; };
    template< class U >
    reverse_iterator& operator=( const reverse_iterator<U>& other ) { this->current = other.p; return *this; };
    /**
     * @brief Returns the underlying base iterator. That is ft::reverse_iterator(it).base() == it
     * @return iterator_type 
     */
    iterator_type base() const { return current; };
    reference operator*() const { iterator_type tmp = current; return *--tmp;};
    pointer operator->() const { return &(operator*()); };
    reference operator[]( difference_type n ) const { return base()[-n-1]; };
    /**
     * @brief Increments or decrements the iterator. 
              Inverse operations are applied to the underlying operator because of the reverse order.
     * @return reverse_iterator&, or reverse_iterator 
     */
    reverse_iterator& operator++() { current--; return *this; };
    reverse_iterator& operator--() { current++; return *this; };
    reverse_iterator operator++( int ) { reverse_iterator tmp(base()); current--; return tmp; };
    reverse_iterator operator--( int ) { reverse_iterator tmp(base()); current++; return tmp; };
    reverse_iterator operator+( difference_type n ) const { return reverse_iterator(base() - n); };
    reverse_iterator operator-( difference_type n ) const { return reverse_iterator(base() + n); };
    reverse_iterator& operator+=( difference_type n ){ current = base() - n; return *this; };
    reverse_iterator& operator-=( difference_type n ){ current = base() + n; return *this; };

  protected:
    iterator_type current;
};
/**
 * @brief Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed
 * @return true or false
 */
template< class Iterator1, class Iterator2 >
bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ){
  return (lhs.base() == rhs.base()); };
template< class Iterator1, class Iterator2 >
bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ){
  return !(operator==(lhs, rhs));
};
template< class Iterator1, class Iterator2 >
bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ){
  return (lhs.base() > rhs.base());
};
template< class Iterator1, class Iterator2 >
bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ){
  return (!operator<(rhs, lhs));
};
template< class Iterator1, class Iterator2 >
bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ){
  return (operator<(rhs, lhs));
};
template< class Iterator1, class Iterator2 >
bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ){
    return (!operator<(lhs, rhs));
};
template< class Iter >
reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ){
      return (reverse_iterator<Iter>(it.base() - n));
    };
template< class Iterator >
typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ){
  return (rhs.base() - lhs.base());
}
}; // NAMESPACE

#endif