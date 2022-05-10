#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "enable_if.hpp" 
#include "is_integral.hpp" 
#include "integral_constant.hpp" 
#include "iterator.hpp"
#include "lexicographical_compare.hpp" 
#include "remove_cv.hpp" 
#include "utilities.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <exception>
#include <stdexcept>
#include <sstream>

namespace ft {

/**
 * @brief The elements are stored contiguously, which means that elements can be accessed not only through iterators, 
 *        but also using offsets to regular pointers to elements. 
 *        This means that a pointer to an element of a vector may be passed to any function that expects a pointer to an element of an array.
 *        The storage of the vector is handled automatically, being expanded and contracted as needed.
 *        Vectors usually occupy more space than static arrays, because more memory is allocated to handle future growth.
 *        source: https://en.cppreference.com/w/cpp/container/vector
 */

/**
 * 
 * @param T The type of the stored elements.
 * @param Allocator An allocator that is used to acquire/release memory and to construct/destroy the elements in that memory.
 */

template< class T, class Allocator = std::allocator<T> >
class vector {

    public:
        /**
         * Typefs Member types
        */
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef typename ft::vectorIterator<T> iterator;
        typedef typename ft::vectorIterator<const T> const_iterator;
        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

        /**
         * Member functions
        */
        /**
         * @brief Default constructor. Constructs an empty container with a default-constructed allocator.
         */
        vector() : n_allocator(), currentSize(0), currentCapacity(0), n() {};

        /**
         * @brief Constructs an empty container with the given allocator alloc.
         */
        explicit vector(const Allocator &alloc)
            : n_allocator(alloc), currentSize(0), currentCapacity(0), n(){};
        /**
         * @brief  Constructs the container with count copies of elements with value value.
         */
        explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator())
            : n_allocator(alloc), currentSize(0), currentCapacity(0) {

            assign(count, value);
        };
        /**
         * @brief Constructs the container with the contents of the range [first, last) 
         */
        template <class InputIt>
        vector(InputIt first, InputIt last, const Allocator &alloc = Allocator(),
        typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0) 
            : n_allocator(alloc), currentSize(0), currentCapacity(0) {
            assign(first, last);
        };
        /**
         * @brief Copy Construct
         */
        vector(const vector &other) { n = NULL; *this = other; };

        /**
         * @brief  Destructs the vector. The destructors of the elements are called and the used storage is deallocated.
         *         Note, that if the elements are pointers, the pointed-to objects are not destroyed.
         *
         */
        ~vector(){
            // std::cout << "CURRENT CAPCITY: " << currentCapacity << " CurrentSize: "<< currentSize << std::endl;
            
            clear();
            if (n)
                n_allocator.deallocate(n, currentCapacity); 
        };
    /*
     * Functions needed for deep copying in operator=
     */    
    private:

        void    copyElements(T *dest, T *src, size_type size) {

            for (size_type i = 0; i < size; i++){
                n_allocator.construct(&dest[i], src[i]);
            }
        };

        void deepCopy(const vector &other) {

            if (other.n && other.size())
            {
                if (n)
                    n_allocator.deallocate(n, currentCapacity);
                this->n = this->n_allocator.allocate(other.capacity());
                copyElements(this->n, other.n, other.size());
                currentCapacity = other.capacity();
                currentSize = other.size();
            }
            else
                this->n = NULL;
            this->currentCapacity = other.capacity();
            this->currentSize = other.size();
        };

    public:
        /**
         * @brief Assigns values to the container by deep copying it
         */
        vector &operator=(const vector &other) {
            if (this != &other)
                deepCopy(other);
            return *this;
        };


        /**
         * Element access 
        */
        
        /**
         * @brief Returns a reference to the element at specified location pos.
         *        Bounds checking is performed.
         */
        reference at( size_type pos ){
            if (!(pos < size())){
                std::stringstream sstm_err;
                sstm_err << "vector::_M_range_check: __n (which is " << pos << ") >= "; 
                sstm_err << "this->size() (which is " << currentSize << ")"; 
                throw std::out_of_range(sstm_err.str());
            }
            return (*this)[pos];
        };

        const_reference at( size_type pos ) const {

            if (!(pos < size())){
                std::stringstream sstm_err;
                sstm_err << "vector::_M_range_check: __n (which is " << pos << ") >= "; 
                sstm_err << "this->size() (which is " << currentSize << ")"; 
                throw std::out_of_range(sstm_err.str());
            }
            return (*this)[pos];
        };

        /**
         * @brief Returns a reference to the element at specified location pos. No bounds checking is performed. 
         */
        reference operator[]( size_type pos ){ return *(n + pos); };
        const_reference operator[]( size_type pos ) const { return *(n + pos); };

        /**
         * @brief Returns a reference to the first element in the container.
         *        Calling front on an empty container is undefined.
         */
        reference front() { return *begin(); };
        const_reference front() const { return *begin(); };

        /**
         * @brief Returns a reference to the last element in the container.
         *        Calling back on an empty container is undefined.
         */
        reference back() { return *(end() - 1); };
        const_reference back() const { return *(end() - 1); };

        // Returns pointer to the underlying array serving as element storage.
        // The pointer is such that range [data(); data() + size()) is always a valid range, even if the container is empty (data() is not dereferenceable in that case).
        T* data() { return this->n; };
        const T* data() const { return this->n; };
        /**
         * @brief Replaces the contents with count copies of value value
         */
        void assign( size_type count, const T& value ){
            // n_allocator.destroy(n);
            //std::cout << "Count: " << count << " CurrentCap: " << currentCapacity << std::endl;
            size_type index = 0;
            if (count > currentCapacity){
                T *tmp_n = n_allocator.allocate(count);
                while (index < count){
                    n_allocator.construct(tmp_n + index, value);
                    ++index;
                }
                if (currentCapacity > 0){
                    clear();
                    n_allocator.deallocate(n, currentCapacity);
                }
                currentCapacity = count;
                n = tmp_n;
            }
            else {
                while (index < count){
                    // std::cout << "INDEX: " << index << " Value: " << value << std::endl;
                    // n[index] = value;
                    n_allocator.construct(n + index, value);
                    ++index;
                }
            }
            currentSize = count;
        };
        /**
         * @brief Replaces the contents with copies of those in the range [first, last).
         * The behavior is undefined if either argument is an iterator into *this.
         */
        template< class InputIt >
        void assign( InputIt first, InputIt last,
        typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0) {
            size_type count = _distance(first, last);
                // n_allocator.destroy(n);
            if (count >= currentCapacity){
                T *tmp_n = n_allocator.allocate(count);
                size_type index = 0;
                while (first != last){
                    n_allocator.construct(&tmp_n[index], *first);
                    ++first;
                    ++index;
                }
                if (currentCapacity > 0)
                    n_allocator.deallocate(n, currentCapacity);
                currentCapacity = count;
                n = tmp_n;
            }
            else {
                size_type index = 0;
                while (first != last){
                    n_allocator.construct(n + index, *first);
                    ++index;
                    ++first;
                }
            }
            currentSize = count;
        };

        /**
         * @brief Returns the allocator associated with the container.
         */
        allocator_type get_allocator() const { return this->n_allocator; };

        /**
         * Iterators 
        */
        iterator begin() { iterator it = n; return it; };
        const_iterator begin() const { const_iterator it = n; return it; };
        /**
         * @brief Returns an iterator to the element following the last element of the vector.
         *        This element acts as a placeholder; attempting to access it results in undefined behavior.
         */
        iterator end() { iterator it = (n + size()); return it; };
        const_iterator end() const { const_iterator it = (n + size()); return it; };
        
        reverse_iterator rbegin() { reverse_iterator rit(end()); return rit; };
        const_reverse_iterator rbegin() const { const_reverse_iterator rit(end()); return rit; };

        /**
         * @brief Returns a reverse iterator to the element following the last element of the reversed vector.
         *        It corresponds to the element preceding the first element of the non-reversed vector.
         *        This element acts as a placeholder, attempting to access it results in undefined behavior.
         */
        reverse_iterator rend() { reverse_iterator rit(begin()); return rit; };
        const_reverse_iterator rend() const { const_reverse_iterator rit(begin()); return rit; };
        
        /**
         * Capacity 
        */
        
        /**
         * @brief check wether the container is empty
         */
        bool empty() const { return (currentSize == 0); };
        /**
         * @brief   Returns the number of elements in the container, i.e. the distance between (begin(), end()).
         */
        size_type size() const { return currentSize; };

        /**
         * @brief Returns the maximum number of elements the container is able to hold due to system or library implementation limitations.
         */
        size_type max_size() const { return n_allocator.max_size(); };

        /**
         * @brief returns the number of elements that can be held in currently allocated storage
         */
        size_type capacity() const { return currentCapacity; };

        /**
         * @brief Increase the capacity of the vector to a value that's greater or equal to new_cap.
         *        If new_cap is greater than the current capacity(), new storage is allocated, otherwise the function does nothing.
         */
        void reserve( size_type new_cap ){
            if (new_cap > max_size())
                throw std::length_error("vector::reserve");
            else if (new_cap > currentCapacity) {
                try {
                    T* tmp_n = n_allocator.allocate(new_cap);
                    copyElements(tmp_n, n, currentSize);
                    n_allocator.deallocate(n, currentCapacity); 
                    n = tmp_n;
                    currentCapacity = new_cap;
                }
                catch(...) {};
            }
        };

        /**
         * Modifiers 
        */
        
        /**
         * @brief Erases all elements from the container. After this call, size() returns zero.
         *        Invalidates any references, pointers, or iterators referring to contained elements.
         *        Any past-the-end iterators are also invalidated. 
         */
        void clear(){
            if (empty()) return;
            for (size_t index = 0; index < currentSize; index++) {
                n_allocator.destroy(&n[index]);
            }
            currentSize = 0;
        };

    private:
        
        /**
         * @brief Measure the distance between the two pointers passed as arguments.
         */
        template <typename InputIt>
        size_type _distance(InputIt start, InputIt end) {
           size_type distance = 0;
           InputIt it = start;

           while (it != end){
               distance++;
               it++;
           }
           return distance;
        };

    public:
        /**
         * @brief Inserts elements at the specified location in the container.
         *        Causes reallocation if the new size() is greater than the old capacity().
         *        If the new size() is greater than capacity(), all iterators and references are invalidated.
         *        Otherwise, only the iterators and references before the insertion point remain valid.
         *        The past-the-end iterator is also invalidated.
         */
        iterator insert( iterator pos, const T& value ) {
            size_type d1 = _distance<iterator>(begin(), pos);
            insert(pos, 1, value);
            return iterator(n + d1);
        };

        void insert( iterator pos, size_type count, const T& value ) {

            if (currentSize + count >= max_size())
                throw std::length_error(NULL);
            size_type savedCapacity = currentCapacity;
            if (currentCapacity == 0) 
                currentCapacity+= count;
            else while (currentSize + count > currentCapacity)
                currentCapacity *= 2;
            try {
                size_type index = 0;
                size_type d1 = _distance<iterator>(begin(), pos);
                size_type d2 = _distance<iterator>(pos, end());
                if (savedCapacity == currentCapacity){
                    index = 1;
                    while (index <= d2){
                        n_allocator.construct(&n[currentSize - index + count], n[currentSize - index]);
                        index++;
                    }
                    index = d1;
                    while (index < d1 + count){
                        n_allocator.construct(n + index, value);
                        ++index;
                    }
                }
                else {

                    T *tmp_n = n_allocator.allocate(currentCapacity);
                    while (index < d1){
                        n_allocator.construct(tmp_n + index, n[index]);
                        index++;
                    }
                    while (index < d1 + count){
                        n_allocator.construct(tmp_n + index, value);
                        index++;
                    }
                    while (index < d1 + d2 + count){
                        n_allocator.construct(tmp_n + index, n[index - count]);
                        index++;
                    }
                    n_allocator.deallocate(n, savedCapacity);
                    n = tmp_n;
                }
                currentSize+= count;
            } catch (...) {
                currentCapacity = savedCapacity;
            }
        };
        template< class InputIt >
        void insert( iterator pos, InputIt first, InputIt last, 
               typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0){

            size_type count = _distance<InputIt>(first, last);
            if (currentSize + count >= max_size())
                throw std::length_error(NULL);
            size_type savedCapacity = currentCapacity;
            if (currentCapacity == 0) 
                currentCapacity+= count;
            while (currentSize + count > currentCapacity)
                currentCapacity *= 2;
            try {
                T *tmp_n = n_allocator.allocate(currentCapacity);
                size_type index = 0;
                size_type d1 = _distance<iterator>(begin(), pos);
                size_type d2 = _distance<iterator>(pos, end());
                while (index < d1){
                    n_allocator.construct(tmp_n + index, n[index]);
                    ++index;
                }
                while (index < d1 + count){
                    n_allocator.construct(tmp_n + index, *first);
                    ++index;
                    ++first;
                }
                while (index < d1 + d2 + count){
                    n_allocator.construct(tmp_n + index, n[index - count]);
                    ++index;
                }
                n_allocator.deallocate(n, savedCapacity);
                n = tmp_n; 
                currentSize+= count;
            } catch (...) {
                currentCapacity = savedCapacity;
            }
        };

        /**
         * @brief Removes the element at pos.
         * @return Iterator following the last removed element.
         */
        iterator erase( iterator pos ) {

            try {
                    size_type index = _distance<iterator>(begin(), pos);
                    while (index < currentSize - 1){
                        n[index] =  n[index + 1];
                        index++;
                    }
                    --currentSize;
                } catch (...) {}
            if (pos == end() - 1)   
                return (end());
            else
                return pos;
        };
        /**
         * @brief Removes the elements in the range [first, last).
         * Invalidates iterators and references at or after the point of the erase, including the end() iterator.
         * The iterator pos must be valid and dereferenceable. 
         * Thus the end() iterator (which is valid, but is not dereferenceable) cannot be used as a value for pos.
         * The iterator first does not need to be dereferenceable if first==last: erasing an empty range is a no-op.
         */
        iterator erase( iterator first, iterator last ) {

            size_type d_range = _distance<iterator>(first, last);
            if (d_range == 0)
                return (last);
            bool endIsLast = 0;
            iterator after_removed_el;
            if (last == end())
                endIsLast = 1;
            try {
                    size_type d1 = _distance<iterator>(begin(), first);
                    size_type index = d1;
                    while (index < currentSize - d_range){
                        n[index] =  n[index + d_range];
                        index++;
                    }
                    after_removed_el = begin() + d1;
                    while (index < currentSize){
                        n_allocator.destroy(&n[index]);
                        index++;
                    }
                    if (currentSize - d_range > 0)
                        currentSize -= d_range;
                    else
                        currentSize = 0;
                } catch (...) {}
            if (endIsLast)
                return (end());
            return (after_removed_el);
        };
        /**
         * @brief Appends the given element value to the end of the container.
         *        If the new size() is greater than capacity() then all iterators and references (including the past-the-end iterator) are invalidated. 
         *        Otherwise only the past-the-end iterator is invalidated.
         */
        void push_back( const T& value ) { insert(end(), value); };
        /**
         * @brief Removes the last element of the container. Calling pop_back on an empty container results in undefined behavior.
         *        Iterators and references to the last element, as well as the end() iterator, are invalidated.
         * 
         */
        void pop_back() { n_allocator.destroy(&n[--currentSize]); };

        /**
         * @brief Resizes the container to contain count elements.
         * If the current size is greater than count, the container is reduced to its first count elements.
         * If the current size is less than count, additional copies of value are appended.
        */
        void resize( size_type count, T value = T() ) {
            if (count <= currentSize){
                while (count < currentSize)        
                    pop_back();
            }
            else {
                insert(end(), count - currentSize, value);
            }
        };

    public:
        /**
         * @brief Exchanges the contents of the container with those of other.
         * Does not invoke any move, copy, or swap operations on individual elements.
         * All iterators and references remain valid. The past-the-end iterator is invalidated.
         */
        void swap( vector& other ){

            baseSwap(this->n, other.n);
            baseSwap(this->n_allocator, other.n_allocator);
            baseSwap(this->currentCapacity, other.currentCapacity);
            baseSwap(this->currentSize, other.currentSize);
        };


    private:
        /**
         * Container Objects
        */
        Allocator n_allocator;
        size_t currentSize;
        size_t currentCapacity;
        T *n;

    public:
        /**
         * Non member functions that require access to the protected Member Object "n" 
        */

        template <class _T, class _Container>
        friend bool operator<(const ft::vector<_T, _Container> &lhs, const ft::vector<_T, _Container> &rhs);

};

/**
* Vector Non member functions
*/
template< class T, class Alloc >
void swap( vector<T, Alloc>& lhs, vector<T, Alloc>& rhs ){ lhs.swap(rhs); };

// Operator "<" is used to build the other operator overloads to limit the use of "friend" functions
template< class T, class Container >
    bool operator<( const ft::vector<T,Container>& lhs, const ft::vector<T,Container>& rhs ) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); 
    };

template< class T, class Container >
    bool operator==( const ft::vector<T,Container>& lhs, const ft::vector<T,Container>& rhs ) { return !(lhs < rhs) && !(rhs < lhs); };

template< class T, class Container >
    bool operator!=( const ft::vector<T,Container>& lhs, const ft::vector<T,Container>& rhs ) { return (lhs < rhs) || (rhs < lhs); };

template< class T, class Container >
    bool operator<=( const ft::vector<T,Container>& lhs, const ft::vector<T,Container>& rhs ) { return !(rhs < lhs); };

template< class T, class Container >
bool operator>( const ft::vector<T,Container>& lhs, const ft::vector<T,Container>& rhs ) { return (rhs < lhs); };

template< class T, class Container >
    bool operator>=( const ft::vector<T,Container>& lhs, const ft::vector<T,Container>& rhs ) { return !(lhs < rhs); };

}; // namespace
#endif