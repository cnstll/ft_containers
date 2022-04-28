#ifndef MAP_HPP
#define MAP_HPP
// ! Remove
#include "lexicographical_compare.hpp"
#include "pair.hpp"
#include "RBtree.hpp"
#include "iterator.hpp"
#include "utilities.hpp"
#include <exception>
#include <functional>
#include <memory>
#include <stdexcept>

// ! Remove std::less std::pair
namespace ft {
template<
    class Key,
    class T,
    class Compare = std::less<Key>, 
    class Allocator = std::allocator<ft::pair<const Key, T> > 
> class map {
public:
  // types
  typedef Key                                                           key_type;
  typedef T                                                             mapped_type;
  typedef typename ft::pair<const Key, T>                               value_type;
  typedef std::size_t                                                   size_type;
  typedef std::ptrdiff_t                                                difference_type;
  typedef Compare                                                       key_compare;
  typedef Allocator                                                     allocator_type;
  typedef value_type&                                                   reference;
  typedef const value_type&                                             const_reference;
  typedef typename Allocator::pointer                                   pointer;
  typedef typename Allocator::const_pointer                             const_pointer;
  typedef typename ft::mapIterator<value_type>                          iterator;
  typedef typename ft::constMapIterator<value_type>                     const_iterator;
  typedef typename ft::reverse_iterator<iterator>                       reverse_iterator;
  typedef typename ft::reverse_iterator<const_iterator>                 const_reverse_iterator;
  /**
   * @brief ft::map::value_compare is a function object that compares objects of type
   * ft::map::value_type (key-value pairs) by comparing of the first components of the pairs.
   * 
   */
  class value_compare : public std::binary_function<value_type, value_type, bool> {
    friend class map;
    protected:
      key_compare comp;
      value_compare(Compare c) : comp(c) {} // constructed with map's comparison object
    public:
      typedef bool result_type;
      typedef value_type first_argument_type;
      typedef value_type second_argument_type;
      /**
       * @brief Compares x.first and y.first by calling the stored comparator
       */
      bool operator()(const value_type &x, const value_type &y) const {
        return comp(x.first, y.first);
      }
  };
  /**
   * CONSTRUCTORS, COPY CONSTRUCTORS, DESTRUCTOR
   */
  explicit map(const Compare& comp = Compare(), const allocator_type& alloc = Allocator()): tree(comp), tree_allocator(alloc){};
  template< class InputIt >
  map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : tree(comp), tree_allocator(alloc){
    insert(first, last);
  };
  map( const map& other ){ *this = other; };
  ~map(){};
  map& operator=( const map& other ){
    if (this != &other){
      tree_allocator = Allocator(other.tree_allocator);
      tree = other.tree;
    }
    return *this;
  };
  allocator_type get_allocator() const { return tree_allocator; };
  /**
   * ELEMENT ACCESS FUNCTIONS
   */
  mapped_type& operator[]( const key_type& key ){
    return insert(ft::make_pair(key, mapped_type())).first->second;
  };
  /**
   * ITERATORS FUNCTIONS
   */
  iterator begin(){ return iterator(tree.getMin(tree.getRoot()));};
  const_iterator begin() const { return const_iterator(tree.getMin(tree.getRoot())); };
  iterator end(){ return iterator(tree.getSentinel()); };
  const_iterator end() const { return const_iterator(tree.getSentinel()); };
  reverse_iterator rbegin(){ return reverse_iterator(end()); };
  const_reverse_iterator rbegin() const{ return const_reverse_iterator(end()); };
  reverse_iterator rend(){ return reverse_iterator(begin()); };
  const_reverse_iterator rend() const{ return const_reverse_iterator(begin()); };
  /**
   * CAPACITY FUNCTIONS 
   */
  bool empty() const { return tree.getNodeCount() == 0; };
  size_type size() const { return tree.getNodeCount(); };
  size_type max_size() const { return tree_allocator.max_size(); };
  /**
   * MODIFIERS FUNCTIONS
   */
  void clear(){
    if (tree.getNodeCount() > 0)
      tree.clearTree();
  };
  ft::pair<iterator, bool> insert( const value_type& value ){
    
    bool insertionResult = tree.insert(value);
    return ft::make_pair(iterator(tree.getLastInsertedNode()), insertionResult);
  };

  template< class InputIt >
  void insert( InputIt first, InputIt last ){
    iterator it = first;
    while (it != last){
      tree.insert(*it);
      ++it;
    }
  };
  void erase( iterator pos ){
    erase((*pos).first);
  };

  void erase( iterator first, iterator last ){
    key_type nextKey = (*first).first;
    // key_type lastKey = (*last).first;
      // std::cerr << "LK: "<< lastKey << std::endl;
    iterator tmp = first;
    std::cerr << "NK: "<< nextKey << std::endl;
    while (first != last){
      tmp = upper_bound((*tmp).first);
      nextKey = (*tmp).first;
      erase(first);
      if (tmp == end())
        break;
      tree.printTree();
      std::cerr << "NK: "<< nextKey << std::endl;
      tmp = find(nextKey);
      first = tmp;
    }
  };

  size_type erase( const Key& key ){
    return (tree.remove(ft::make_pair(key, mapped_type())));
  };
  
  void swap(map &other){
    baseSwap(tree_allocator, other.tree_allocator);
    baseSwap(tree, other.tree);
  };
  /**
   * LOOKUP FUNCTIONS 
   */

  /**
   * @brief count the number of node with the key passed, as map is made of unique keys count can only return 1 or 0
   * 
   * @param key used to search the tree for the corresponding node
   * @return size_type of 1 or 0 
   */
  size_type count(const key_type &key) const {
    if (tree.searchTree(ft::make_pair(key, mapped_type())) != tree.getSentinel())
      return 1;
    else
      return 0;
  };
  /**
   * @brief search the RBtree for nodes with the corresponding key
   * 
   * @param key used to search the tree for the corresponding node
   * @return iterator to the node where key was found or end() if no node with key was found
   */
  iterator find(const key_type &key){
    iterator it(tree.searchTree(ft::make_pair(key, mapped_type())));
    if (it == tree.getSentinel())
      return end();
    else
      return it;
  };
  const_iterator find(const key_type &key) const {
    const_iterator it(tree.searchTree(ft::make_pair(key, mapped_type())));
    if (it == tree.getSentinel())
      return end();
    else
      return it;
  };
  /**
   * @brief find a pair of iterator that points to the lower and upper bound of the key passed
   * 
   * @param key checked against
   * @return ft::pair< iterator, iterator > pair of iterator to the lower bound and the upper bound 
   */
  ft::pair< iterator, iterator > equal_range(const key_type &key){
    return ft::make_pair(lower_bound(key), upper_bound(key));
  };
  ft::pair< const_iterator, const_iterator > equal_range(const key_type &key) const {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  };
  //! Not sure about implementation, to be further tested
  /**
   * @brief lower_bound, find the first node with a key that validate key !key_compare
   * 
   * @param key checked against
   * @return iterator to the node which validates !key_compare or end() if no such node is found
   */
  iterator lower_bound(const key_type &key){
    iterator it(tree.getLowerBound(ft::make_pair(key, mapped_type())));
    if (it != tree.getSentinel())
      return it;
    else
      return end();
  };
  const_iterator lower_bound(const key_type &key) const {
    const_iterator it(tree.getLowerBound(ft::make_pair(key, mapped_type())));
    if (it != tree.getSentinel())
      return it;
    else
      return end();
  };
  /**
   * @brief find the successor of the node with key passed as parameter
   * 
   * @param key checked against 
   * @return iterator to the successor node or end() if no successor is found 
   */
  iterator upper_bound(const key_type &key){
    iterator it(tree.getSuccessor(ft::make_pair(key, mapped_type())));
    if (it != tree.getSentinel())
      return it;
    else
      return end();
  }
  const_iterator upper_bound(const key_type &key) const{
    const_iterator it(tree.getSuccessor(ft::make_pair(key, mapped_type())));
    if (it != tree.getSentinel())
      return it;
    else
      return end();
  };
  /**
   * OBSERVERS FUNCTIONS
   */
  key_compare key_comp() const { return tree.getComp(); };
  value_compare value_comp() const { return value_compare(key_comp());};
  /**
   * @brief overload of operator== marked as friend to be able to access "tree" in map
   */
  template< class _Key, class _T, class _Compare, class _Alloc >
  friend bool operator==( const ft::map<_Key,_T,_Compare,_Alloc>& lhs, const ft::map<_Key,_T,_Compare,_Alloc>& rhs );
  
  private : 
    RedBlackTree<value_type, key_compare, allocator_type>        tree;
    allocator_type tree_allocator;
};
/**
* map Non member functions
*/

template< class Key, class T, class Compare, class Alloc >
void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ){ lhs.swap(rhs); };

/**
 * @brief Checks if the contents of lhs and rhs are equal,
 * that is, they have the same number of elements
 * and each element in lhs compares equal with the element in rhs at the same position.
 */
template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
  if (lhs.tree.getNodeCount() != rhs.tree.getNodeCount())
    return false;
  typename ft::map<Key,T,Compare,Alloc>::const_iterator it_lhs = lhs.begin();
  typename ft::map<Key,T,Compare,Alloc>::const_iterator it_rhs = rhs.begin();
  while (it_lhs != lhs.end() && it_rhs != rhs.end()){
    if ((*it_lhs).first != (*it_lhs).first)
      return false;
    if ((*it_lhs).second != (*it_lhs).second)
      return false;
    ++it_lhs;
    ++it_rhs;
  }
  if (it_lhs != lhs.end() || it_rhs != rhs.end())
    return false;
  return true;
};
template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
  return !(lhs == rhs);
};

/**
 * @brief Compares the contents of lhs and rhs lexicographically.
 * The comparison is performed by a function equivalent to std::lexicographical_compare.
 * This comparison ignores the map's ordering Compare.
 */
template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
};
template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
  return !(rhs < lhs);
};
template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
  return (rhs <  lhs);
};
template< class Key, class T, class Compare, class Alloc >
bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
  return !(lhs < rhs);
};
};//NAMESPACE
#endif