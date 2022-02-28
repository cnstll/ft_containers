// ! Remove
#include <functional>
#include "RBtree.hpp"

// ! Remove std::less std::pair
namespace ft {
template<
    class Key,
    class T,
    class Compare = ft::less<Key>, 
    class Allocator = std::allocator<std::pair<const Key, T> > 
> class map {
public:
  // types
  typedef Key                                key_type;                
  typedef T                                  mapped_type;             
  typedef std::pair<const Key, T>            value_type;// ! Recoder std::pair           
  typedef tree_t::size_type                  size_type;               
  typedef tree_t::difference_type            difference_type;         
  typedef Compare                            key_compare;             
  typedef Allocator                          allocator_type;          
  typedef tree_t::reference                  reference;               
  typedef tree_t::const_reference            const_reference;         
  typedef tree_t::pointer                    pointer;                 
  typedef tree_t::const_pointer              const_pointer;           
  typedef tree_t::iterator                   iterator;                
  typedef tree_t::const_iterator             const_iterator;          
  typedef tree_t::reverse_iterator           reverse_iterator;        
  typedef tree_t::const_reverse_iterator     const_reverse_iterator;  
  typedef tree_t::stored_allocator_type      stored_allocator_type;   
  //typedef unspecified                        nonconst_impl_value_type;
  //typedef value_compare_impl                 value_compare;           

  // construct/copy/destruct
  map(){};
  explicit map(const Compare &, const allocator_type & = allocator_type()){};
  //template<typename InputIterator> 
  //  map(InputIterator, InputIterator, const Compare & = Compare(), 
  //      const allocator_type & = allocator_type()){};
  //template<typename InputIterator> 
  //  map(ordered_unique_range_t, InputIterator, InputIterator, 
  //      const Compare & = Compare(), const allocator_type & = allocator_type()){};
  //map(const map &){};
  //map(BOOST_RV_REF(map)){};
  //map(const map &, const allocator_type &){};
  //map(BOOST_RV_REF(map), const allocator_type &){};
  //map& operator=(BOOST_COPY_ASSIGN_REF(map)){};
  //map& operator=(BOOST_RV_REF(map)){};

  //// public member functions
  //key_compare key_comp() const{};
  //value_compare value_comp() const{};
  //allocator_type get_allocator() const{};
  //const stored_allocator_type & get_stored_allocator() const{};
  //stored_allocator_type & get_stored_allocator(){};
  //iterator begin(){};
  //const_iterator begin() const{};
  //const_iterator cbegin() const{};
  //iterator end(){};
  //const_iterator end() const{};
  //const_iterator cend() const{};
  //reverse_iterator rbegin(){};
  //const_reverse_iterator rbegin() const{};
  //const_reverse_iterator crbegin() const{};
  //reverse_iterator rend(){};
  //const_reverse_iterator rend() const{};
  //const_reverse_iterator crend() const{};
  //bool empty() const{};
  //size_type size() const{};
  //size_type max_size() const{};
  //mapped_type & operator[](const key_type &){};
  //mapped_type & operator[](key_type &&){};
  // BOOST_MOVE_CONVERSION_AWARE_CATCH(operator, key_type, mapped_type &, 
  //                                   priv_subscript) const{};
  //const T & at(const key_type &) const{};
  //void swap(map &){};
  //std::pair< iterator, bool > insert(const value_type &){};
  //std::pair< iterator, bool > insert(const nonconst_value_type &){};
  //std::pair< iterator, bool > insert(BOOST_RV_REF(nonconst_value_type)){};
  //std::pair< iterator, bool > insert(BOOST_RV_REF(nonconst_impl_value_type)){};
  //std::pair< iterator, bool > insert(BOOST_RV_REF(value_type)){};
  //iterator insert(iterator, const value_type &){};
  //iterator insert(iterator, BOOST_RV_REF(nonconst_value_type)){};
  //iterator insert(iterator, BOOST_RV_REF(nonconst_impl_value_type)){};
  //iterator insert(iterator, const nonconst_value_type &){};
  //iterator insert(iterator, BOOST_RV_REF(value_type)){};
  //template<typename InputIterator> void insert(InputIterator, InputIterator){};
  //template<class... Args> std::pair< iterator, bool > emplace(Args &&...){};
  //template<class... Args> iterator emplace_hint(const_iterator, Args &&...){};
  //iterator erase(const_iterator){};
  //size_type erase(const key_type &){};
  //iterator erase(const_iterator, const_iterator){};
  //void clear(){};
  //iterator find(const key_type &){};
  //const_iterator find(const key_type &) const{};
  //size_type count(const key_type &) const{};
  //iterator lower_bound(const key_type &){};
  //const_iterator lower_bound(const key_type &) const{};
  //iterator upper_bound(const key_type &){};
  //const_iterator upper_bound(const key_type &) const{};
  //std::pair< iterator, iterator > equal_range(const key_type &){};
  //std::pair< const_iterator, const_iterator > 
  //equal_range(const key_type &) const{};
};//
};//NAMESPACE