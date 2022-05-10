#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "rb_tree.hpp"
#include "remove_cv.hpp"
#include <cstddef> //std::ptrdiff_t | std::size_t

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

    /*Convert constant type*/
    operator vectorIterator<const T>() const{
      return vectorIterator<const T>(p);
    }
  /* The underlying pointer to data hold in the container */
    T* p;
  };
    /*Can be compared for equivalence using the equality/inequality operators*/
    template <typename T1, typename T2>
    bool operator==(const vectorIterator<T1>& lhs, const vectorIterator<T2>& rhs) { return lhs.p == rhs.p; };
    template <typename T1, typename T2>
    bool operator!=(const vectorIterator<T1> &lhs, const vectorIterator<T2> &rhs) { return !operator==(lhs, rhs); };
    /*Can be compared with inequality relational operators (<, >, <= and >=).*/
    template <typename T1, typename T2>
    bool operator< (const vectorIterator<T1>& lhs, const vectorIterator<T2>& rhs) { return lhs.p < rhs.p; };
    template <typename T1, typename T2>
    bool operator> (const vectorIterator<T1>& lhs, const vectorIterator<T2>& rhs) { return operator<(rhs, lhs); };
    template <typename T1, typename T2>
    bool operator<=(const vectorIterator<T1>& lhs, const vectorIterator<T2>& rhs) { return !operator>(lhs, rhs); };
    template <typename T1, typename T2>
    bool operator>=(const vectorIterator<T1>& lhs, const vectorIterator<T2>& rhs) { return !operator<(lhs, rhs); };
template <class T> 
class constMapIterator;

template <class T> 
class mapIterator : public ft::iterator<bidirectional_iterator_tag, T>
{
  public:
    typedef bidirectional_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef typename ft::mapNode<T> node;

//   /* Is default-constructible, copy-constructible, copy-assignable and destructible */
    mapIterator() : currentNode(){}
    mapIterator(node* someMapNode) : currentNode(someMapNode){}
    mapIterator(mapIterator const& other) : currentNode(other.currentNode){}
    mapIterator &operator=(const mapIterator& rhs){ 
      if (this != &rhs)
        this->currentNode = rhs.currentNode;
      return *this;
    }
    ~mapIterator() {}

  /*Can be dereferenced as an lvalue (if in a dereferenceable state).*/
    T& operator*() const { return currentNode->data; }
    T *operator->() const{ return &currentNode->data; }

//'ft::mapIterator<ft::pair<const char, int> >::node *' (aka 'mapNode<ft::pair<const char, int> > *')
//to 'mapIterator<const ft::pair<const char, int> >'
  /*Can be incremented (if in a dereferenceable state).*/
    mapIterator& operator++()  {
      if (currentNode->isSentinel)
        currentNode = currentNode->getMin();
      else
        currentNode = currentNode->getSuccessor();
      return *this;
    }
    mapIterator operator++(int) {mapIterator tmp(*this); operator++(); return tmp;}

  /*Can be incremented (if in a dereferenceable state).*/
    mapIterator& operator--() {
      if (currentNode->isSentinel){
        currentNode = currentNode->getMax();
      }
      else
        currentNode = currentNode->getPredecessor();
      return *this;
    }
    mapIterator operator--(int) {mapIterator tmp(*this); operator--(); return tmp;}
  
    /*Convert constant type*/
    // operator mapIterator<T>() const {
    //   return constMapIterator<T>(currentNode);
    // }
    // friend bool operator==(const mapIterator& lhs, const mapIterator& rhs) { return lhs.currentNode == rhs.currentNode; };
    // friend bool operator!=(const mapIterator& lhs, const mapIterator& rhs) { return !operator==(lhs, rhs); };
    node* currentNode;
};

  template <typename T1, typename T2>
  bool operator==(const mapIterator<T1>& lhs, const mapIterator<T2>& rhs) { return lhs.currentNode == rhs.currentNode; };
  template <typename T1, typename T2>
  bool operator!=(const mapIterator<T1>& lhs, const mapIterator<T2>& rhs) { return !operator==(lhs, rhs); };

template <class T> 
class constMapIterator : public ft::iterator<bidirectional_iterator_tag, T>
{
  public:
    typedef bidirectional_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    typedef const T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef typename ft::mapNode<T> const_node;
    typedef typename ft::mapNode<T> node;
  /* Is default-constructible, copy-constructible, copy-assignable and destructible */
    constMapIterator() : currentNode(){}
    constMapIterator(node * someMapNode) : currentNode(someMapNode){}
    constMapIterator(const mapIterator<T>& other) : currentNode(other.currentNode){}
    constMapIterator(const constMapIterator& other) : currentNode(other.currentNode){}
    constMapIterator &operator=(const mapIterator<T>& rhs){ 
      //if (this != &rhs)
        this->currentNode = rhs.currentNode;
      return *this;
    }
    ~constMapIterator(void) {}

  /*Can be dereferenced as an lvalue (if in a dereferenceable state).*/
    reference operator*() const { return currentNode->data; }
    pointer operator->() const { return &currentNode->data; }

  /*Can be incremented (if in a dereferenceable state).*/
    constMapIterator& operator++() {
      if (currentNode->isSentinel)
        currentNode = currentNode->getMin();
      else
        currentNode = currentNode->getSuccessor();
      return *this;
    }
    constMapIterator operator++(int) {constMapIterator tmp(*this); operator++(); return tmp;}

  /*Can be incremented (if in a dereferenceable state).*/
    constMapIterator& operator--() {
      if (currentNode->isSentinel)
        currentNode = currentNode->getMax();
      else
        currentNode = currentNode->getPredecessor();
      return *this;
    }
    constMapIterator operator--(int) {constMapIterator tmp(*this); operator--(); return tmp;}
    
    // operator mapIterator<T>() {
    //   return constMapIterator<T>(currentNode);
    // }

  /*Can be compared for equivalence using the equality/inequality operators*/
    // friend bool operator==(const constMapIterator& lhs, const constMapIterator& rhs) { return lhs.currentNode == rhs.currentNode; };
    // friend bool operator!=(const constMapIterator& lhs, const constMapIterator& rhs) { return !operator==(lhs, rhs); };

    const_node *currentNode;
};

  template <typename T1, typename T2>
  bool operator==(const constMapIterator<T1>& lhs, const constMapIterator<T2>& rhs) { return lhs.currentNode == rhs.currentNode; };
  template <typename T1, typename T2>
  bool operator!=(const constMapIterator<T1>& lhs, const constMapIterator<T2>& rhs) { return !operator==(lhs, rhs); };
  /*Can be compared for equivalence using the equality/inequality operators*/
  template <typename T1, typename T2>
  bool operator==(const mapIterator<T1>& lhs, const constMapIterator<T2>& rhs) { return lhs.currentNode == rhs.currentNode; };
  template <typename T1, typename T2>
  bool operator!=(const mapIterator<T1>& lhs, const constMapIterator<T2>& rhs) { return !operator==(lhs, rhs); };
  template <typename T1, typename T2>
  bool operator==(const constMapIterator<T1>& lhs, const mapIterator<T2>& rhs) { return lhs.currentNode == rhs.currentNode; };
  template <typename T1, typename T2>
  bool operator!=(const constMapIterator<T1>& lhs, const mapIterator<T2>& rhs) { return !operator==(lhs, rhs); };
/**
 * @brief ft::reverse_iterator is an iterator adaptor that reverses the direction of a given iterator,
          which must be at least a LegacyBidirectionalIterator. In other words, when provided with a bidirectional iterator,
          ft::reverse_iterator produces a new iterator that moves from the end to the beginning of the sequence defined by the underlying bidirectional iterator.
 * 
 * @tparam Iter 
 */
template< class Iter >
class reverse_iterator
{
  public:
    typedef Iter iterator_type;
    typedef typename iterator_traits<Iter>::value_type value_type;
    typedef typename iterator_traits<Iter>::iterator_category iterator_category;
    typedef typename iterator_traits<Iter>::difference_type difference_type;
    typedef typename iterator_traits<Iter>::pointer pointer;
    typedef typename iterator_traits<Iter>::reference reference;

    reverse_iterator(): current(){};
    explicit reverse_iterator( iterator_type x ) : current(x) {};
    template< class U >
    reverse_iterator( const reverse_iterator<U>& other ) : current(other.base()){};
    template< class U >
    reverse_iterator& operator=( const reverse_iterator<U>& other ) { this->current = other.base(); return *this; };
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
    reverse_iterator& operator++() { --current; return *this; };
    reverse_iterator& operator--() { ++current; return *this; };
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
template< class Iterator >
reverse_iterator<Iterator> operator+(  typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it ){
      return (reverse_iterator<Iterator>(it.base() - n));
};
template< class Iterator1, class Iterator2 >
typename reverse_iterator<Iterator1>::difference_type operator-(
  const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ){
  return (rhs.base() - lhs.base());
}
template< class Iterator >
typename reverse_iterator<Iterator>::difference_type operator-(
  const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ){
  return (rhs.base() - lhs.base());
}
}; // NAMESPACE

#endif