#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "iterator.hpp"
#include <iostream>
#include <memory>
#include <exception>
#include <stdexcept>
#include <cstddef>

namespace ft {

/**
 *  The std::stack class is a container adaptor that gives the programmer the functionality of a stack - specifically,
 *  a LIFO (last-in, first-out) data structure.
 *  The class template acts as a wrapper to the underlying container - only a specific set of functions is provided.
 *  The stack pushes and pops the element from the back of the underlying container, known as the top of the stack.
 *  source: https://en.cppreference.com/w/cpp/container/stack
*/

/**
 * 
 * @param T The type of the stored elements. The behavior is undefined if T is not the same type as Container::value_type.
 * @param Container The type of the underlying container to use to store the elements.
 * The container must satisfy the requirements of SequenceContainer.
 * Additionally, it must provide the following functions with the usual semantics:
 *     - back()
 *     - push_back()
 *     - pop_back()
 * Here, by default vector is used if no contianer is specified.
 */

template<
    class T,
    class Allocator = std::allocator<T>
> class vector {

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
        //typedef const_iterator;
        //typedef reverse_iterator;
        //typedef const_reverse_iterator;

        /**
         * Member functions
        */
        // Default constructor. Constructs an empty container with a default-constructed allocator.
        vector(void) : currentSize(0), currentCapacity(0), n(NULL) {};

        //Constructs an empty container with the given allocator alloc.
        explicit vector(const Allocator &alloc)
            : n_allocator(alloc), currentSize(0), currentCapacity(0) {};
        // Constructs the container with count copies of elements with value value.
        explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator())
            : n_allocator(alloc), currentSize(count), currentCapacity(count) {

            n = n_allocator.allocate(count);
            for (size_type i = 0; i < count; i++) {
                n_allocator.construct(&n[i], value);
                //n[i] = value;
            }
        };
        // Constructs the container with the contents of the range [first, last)
        template <class InputIt>
        vector(InputIt first, InputIt last, const Allocator &alloc = Allocator()) {

            size_type counter = 0;
            InputIt it = first;
            while (it != last){
                counter++;
                it++;
            }
            n_allocator = alloc;
            currentCapacity = counter;
            currentSize = counter;
            n = n_allocator.allocate(currentCapacity);
            size_type i = 0;
            while (i < counter) {
                n_allocator.construct(&n[i++], *first++);
            }
        };
        // Copy Construct
        vector(const vector &other) { *this = other; };

    private:
        void    copyElements(T *dest, T *src, size_type size) {

            for (size_type i = 0; i < size; i++){
                n_allocator.construct(&dest[i], src[i]);
            }
        };

        void deepCopy(const vector &other) {

            if (other.n && other.size())
            {
                this->n = this->n_allocator.allocate(other.capacity());
                copyElements(this->n, other.n, other.size());
            }
            else
                this->n = NULL;
            this->currentCapacity = other.capacity();
            this->currentSize = other.size();
        };

    public:

        vector &operator=(const vector &other) {

            deepCopy(other);
            return *this;
        };
        // Destructs the vector. The destructors of the elements are called and the used storage is deallocated.
        // Note, that if the elements are pointers, the pointed-to objects are not destroyed.
        ~vector(){
            //for (size_type i = 0; i < currentSize; i++){
            //    n_allocator.destroy(&n[i]);
            //}
            //std::cout << "Destructor\n";
            if (n && capacity() > 0)
                n_allocator.deallocate(n, capacity()); 
        };

        /**
         * Element access 
        */
        //Returns a reference to the element at specified location pos. Bounds checking is performed.
        reference at( size_type pos ){
            if (!(pos < size()))
                throw std::out_of_range("index out of range");
            return (*this)[pos];
        };

        const_reference at( size_type pos ) const {

            if (!(pos < size()))
                throw std::out_of_range("index out of range");
            return (*this)[pos];
        };

        //Returns a reference to the element at specified location pos. No bounds checking is performed.
        reference operator[]( size_type pos ){ return *(n + pos); };
        const_reference operator[]( size_type pos ) const{ return *(n + pos); };

        // Returns a reference to the first element in the container. Calling front on an empty container is undefined.
        reference front() { return *begin(); };
        //const_reference front() const{ return const *begin(); };

        // Returns a reference to the last element in the container.
        reference back() { return *(end() - 1); };
        //const_reference back() const{ return const *(end() - 1); };

        // Returns pointer to the underlying array serving as element storage.
        // The pointer is such that range [data(); data() + size()) is always a valid range, even if the container is empty (data() is not dereferenceable in that case).
        T* data() { return this->n; };
        const T* data() const { return this->n; };

        //Replaces the contents with count copies of value value
        //void assign( size_type count, const T& value ){};
        //Replaces the contents with copies of those in the range [first, last). The behavior is undefined if either argument is an iterator into *this.
        //template< class InputIt > void assign( InputIt first, InputIt last );

        //Returns the allocator associated with the container.
        allocator_type get_allocator() const { return this->n_allocator; };
        /**
         * Iterators 
        */

        iterator begin() { iterator it = n; return it; };
// # To Do
//        const_iterator begin(){ const_iterator it = n; return it; };
//
        iterator end(){ iterator it = (n + size()); return it; };
        //const iterator end(){ const iterator it = (n + size()); return it; };
        //reverse_iterator rbegin() { reverse_iterator it = (n + size); return it };
        //const_reverse_iterator rbegin() { const_reverse_iterator it = (n + size); return it };
        //reverse_iterator rend() { const_reverse_iterator it = n; return it; };
        //const_reverse_iterator rend() { const_reverse_iterator it = n; return it; };
        /**
         * Capacity 
        */
        bool empty() const { return (currentSize == 0); };
        // Returns the number of elements in the container, i.e. std::distance(begin(), end())
        size_type size() const { return currentSize; };

        // Returns the maximum number of elements the container is able to hold due to system or library implementation limitations,
        // i.e. std::distance(begin(), end()) for the largest container.
        size_type max_size() const{ return n_allocator.max_size(); };

//        void reserve( size_type new_cap ){
//            if(new_cap > this->capacity())
//                a.allocate(this->capacity());// reallocate
//            
//        };
        size_type capacity() const { return currentCapacity;};
        /**
         * Modifiers 
        */
        void push_back( const T& value ){

            if (size() + 1 >= max_size())
                throw std::length_error(NULL);
            if (currentCapacity == 0) 
            {
                try {
                    n = n_allocator.allocate(currentCapacity + 1);
                    n_allocator.construct(&n[0], value);
                    currentSize++;
                    currentCapacity++;
                } catch (...) {};
            }
            else
            {
                size_type savedCapacity = currentCapacity;
                if (currentSize >= currentCapacity)
                    currentCapacity *= 2;
                if (currentCapacity != savedCapacity)
                {
                    try {
                        T *tmp_n = n_allocator.allocate(currentCapacity);
                        copyElements(tmp_n, n, currentSize);
                        n_allocator.deallocate(n, savedCapacity); 
                        n = tmp_n;
                    } catch (...) {
                        currentCapacity = savedCapacity;
                    }

                }
                n_allocator.construct(&n[currentSize], value);
                currentSize++;
            }
            //std::cout << "capacity : " << currentCapacity << " -- size : " << currentSize << " -- added value: " << n[currentSize - 1] << std::endl;

        };

        void pop_back(){

            currentSize--;
            n_allocator.destroy(&n[currentSize]);
        };


    private:
        /**
         * Container Objects
        */
        Allocator n_allocator;
        size_t currentSize;
        size_t currentCapacity;
        T *n;

    //public:
        /**
         * Non member functions that require access to the protected Member Object "c" 
        */

//        template <class _T, class _Container>
//        friend bool operator<(const ft::vector<_T, _Container> &lhs, const ft::vector<_T, _Container> &rhs);
//
//        template <class _T, class _Container>
//        friend bool operator==(const ft::vector<_T, _Container> &lhs, const ft::vector<_T, _Container> &rhs);
};
// TODO: look into EqualityComparable requirement https://en.cppreference.com/w/cpp/named_req/EqualityComparable
/**
 * Non member functions
*/

// Operator "<" and "==" are used to build the other operator overloads to limit the use of "friend" functions
//template< class T, class Container >
//    bool operator<( const ft::vector<T,Container>& lhs, const ft::vector<T,Container>& rhs ) { return (lhs.c < rhs.c); };
//
//template< class T, class Container >
//    bool operator==( const ft::vector<T,Container>& lhs, const ft::vector<T,Container>& rhs ) { return (lhs.c == rhs.c); };
//
//template< class T, class Container >
//    bool operator!=( const ft::vector<T,Container>& lhs, const ft::vector<T,Container>& rhs ) { return !(lhs == rhs); };
//
//template< class T, class Container >
//    bool operator<=( const ft::vector<T,Container>& lhs, const ft::vector<T,Container>& rhs ) { return !(rhs < lhs); };
//
//template< class T, class Container >
//bool operator>( const ft::vector<T,Container>& lhs, const ft::vector<T,Container>& rhs ) { return (rhs < lhs); };
//
//template< class T, class Container >
//    bool operator>=( const ft::vector<T,Container>& lhs, const ft::vector<T,Container>& rhs ) { return !(lhs < rhs); };
//
}; // namespace

#endif