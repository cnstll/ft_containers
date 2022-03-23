#ifndef MAP_HPP
#define MAP_HPP
// ! Remove
#include "pair.hpp"
#include "RBtree.hpp"
#include "iterator.hpp"
#include <functional>
#include <memory>

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
  typedef Key                                key_type;                
  typedef T                                  mapped_type;             
  typedef typename ft::pair<const Key, T>            value_type;           
  typedef std::size_t                  size_type;               
  //typedef std::ptrdiff            difference_type;         
  typedef Compare                            key_compare;             
  typedef Allocator                          allocator_type;
  //typedef RedBlackTree::reference                  reference;               
  //typedef RedBlackTree::const_reference            const_reference;         
  //typedef RedBlackTree::pointer                    pointer;                 
  //typedef RedBlackTree::const_pointer              const_pointer;           
  typedef typename ft::mapIterator<value_type>                   iterator;                
  //typedef ft::constMapIterator<value_type>             const_iterator;          
  //typedef RedBlackTree::reverse_iterator           reverse_iterator;        
  //typedef RedBlackTree::const_reverse_iterator     const_reverse_iterator;  
  //typedef value_compare_impl                 value_compare;
  //typedef typename ft::mapNode<value_type>  node_type;
  //typedef typename ft::mapNode<value_type>*  node_pointer;
  //template <class Key, class T, class Compare, class Alloc>
  //class map<Key, T, Compare, Alloc>::value_compare {
  class value_compare : public std::binary_function<value_type, value_type, bool> {
    friend class map;
  protected:
    Compare comp;
    value_compare(Compare c) : comp(c) {} // constructed with map's comparison object
  public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type &x, const value_type &y) const
    {
      return comp(x.first, y.first);
    }
  };
  // construct/copy/destruct
  explicit map(const Compare& comp = Compare(), const allocator_type& alloc = Allocator()): tree(comp){
    (void)(alloc);
  };
  map( const map& other ){ this = other; };
  ~map(){};
  map& operator=( const map& other ){
    if (this != &other){
      ;//tree.insert(other->tree.getRoot();
    }
  };
  //// public member functions
  key_compare key_comp() const { return tree.getComp(); };
  value_compare value_comp() const{ return value_compare(key_comp());};

  //allocator_type get_allocator() const { return tree_allocator; };
  iterator begin(){ return iterator(tree.getMin(tree.getRoot())) ;};
  // const_iterator begin() const{};
  iterator end(){ return iterator(tree.getMax(tree.getRoot())->right); };
  // const_iterator end() const{};
  // reverse_iterator rbegin(){};
  // const_reverse_iterator rbegin() const{};
  // reverse_iterator rend(){};
  // const_reverse_iterator rend() const{};
  /**
   * CAPACITY FUNCTIONS 
   */
  bool empty() const { return tree.getNodeCount() == 0; };
  size_type size() const { return tree.getNodeCount(); };
  size_type max_size() const { return tree_allocator.max_size(); };
  mapped_type& operator[]( const key_type& key ){
    return insert(ft::make_pair(key, mapped_type())).first->second;
  };
  // void swap(map &){};
  ft::pair<iterator, bool> insert( const value_type& value ){
    
    bool insertionResult = tree.insert(value);
    //if (insertionResult) tree.printTree();
    //std::cout << "Tree state: \n";
    //tree.printTree();
    return make_pair(iterator(tree.getLastInsertedNode()), insertionResult);
  };

  template< class InputIt >
  void insert( InputIt first, InputIt last ){
    iterator it = first;
    while (it != last){
      tree.insert(*it);
      ++it;
    }
  };
  //void erase( iterator pos ){
  //  remove ()
  //};
  //iterator erase( const_iterator pos );
  size_type erase( const Key& key ){
    return (tree.remove(make_pair(key,0)));
  };
  void clear(){
    tree.clearTree();
  };
  /**
   * LOOKUP FUNCTIONS 
   */

  /**
   * @brief search the RBtree for nodes with the corresponding key
   * 
   * @param key used to search the tree for the corresponding node
   * @return iterator to the node where key was found or end() if no node with key was found
   */
  iterator find(const key_type &key){
    iterator it(tree.searchTree(make_pair(key, 0)));
    if (it == tree.getSentinel())
      return end();
    else
      return it;
  };
  // const_iterator find(const key_type &) const{};
  /**
   * @brief count the number of node with the key passed, as map is made of unique keys count can only return 1 or 0
   * 
   * @param key used to search the tree for the corresponding node
   * @return size_type of 1 or 0 
   */
  size_type count(const key_type &key) const {
    if (tree.searchTree(make_pair(key, 0)) != tree.getSentinel())
      return 1;
    else
      return 0;
  };
  //! Not sure about implementation, to be further tested
  /**
   * @brief find the first node with a key that validate key !key_compare
   * 
   * @param key checked against
   * @return iterator to the node which validates !key_compare or end() if no such node is found
   */
  iterator lower_bound(const key_type &key){
    iterator it(tree.getLowerBound(make_pair(key, 0)));
    if (it != tree.getSentinel())
      return it;
    else
      return end();
  };
  // const_iterator lower_bound(const key_type &) const{};
  /**
   * @brief find the successor of the node with key passed as parameter
   * 
   * @param key checked against 
   * @return iterator to the successor node or end() if no successor is found 
   */
  iterator upper_bound(const key_type &key){
    iterator it(tree.getSuccessor(make_pair(key, 0)));
    if (it != tree.getSentinel())
      return it;
    else
      return end();
  }
  // const_iterator upper_bound(const key_type &) const{};
  /**
   * @brief find a pair of iterator that points to the lower and upper bound of the key passed
   * 
   * @param key checked against
   * @return ft::pair< iterator, iterator > pair of iterator to the lower bound and the upper bound 
   */
  ft::pair< iterator, iterator > equal_range(const key_type &key){
    return ft::make_pair(lower_bound(key), upper_bound(key));
  };
  // std::pair< const_iterator, const_iterator >
  // equal_range(const key_type &) const{};
  private : 
    RedBlackTree<value_type, key_compare, allocator_type>        tree;
    allocator_type tree_allocator;
};
};//NAMESPACE
#endif