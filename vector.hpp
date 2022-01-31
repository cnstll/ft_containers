#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <memory>
#include <exception>
#include <stdexcept>
#include <iterator>

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
        typedef typename T value_type;
        typedef typename Allocator allocator_type;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef typename std::size_t size_type;
        typedef typename std::ptrdiff_t difference_type;
        typedef typename value_type &reference;
        typedef typename const value_type &const_reference;

        // ! Add Ite
        /**
         * Member functions
        */
        // Default constructor. Constructs an empty container with a default-constructed allocator.
        vector(void){

            return;
        };
        //Constructs an empty container with the given allocator alloc.
        explicit vector(const Allocator &alloc) { std::cout << "Constructor" << std::endl; };
        // Constructs the container with count copies of elements with value value.
        explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator());
        // Constructs the container with the contents of the range [first, last)
        template <class InputIt>
        vector(InputIt first, InputIt last, const Allocator &alloc = Allocator());
        vector(const vector &other) { this->c = other.c; };
        vector &operator=(const vector &other)
        {
            this->c = other.c;
            return *this;
        };
        // Destructs the vector. The destructors of the elements are called and the used storage is deallocated.
        // Note, that if the elements are pointers, the pointed-to objects are not destroyed.
        ~vector(){};

        /**
         * Element access 
        */
        //Returns a reference to the element at specified location pos. Bounds checking is performed.
        reference at( size_type pos ){
            //if !(pos < size())
            //throw std::out_of_range;
            return &a[pos];
        };

        const_reference at( size_type pos ) const {

            //if !(pos < size())
            //throw std::out_of_range;
            return const &a[pos];
        };

        //Returns a reference to the element at specified location pos. No bounds checking is performed.
        reference operator[]( size_type pos ){ return *begin(); };
        const_reference operator[]( size_type pos ) const{ return const *begin(); };

        // Returns a reference to the first element in the container. Calling front on an empty container is undefined.
        reference front() { return *(end() - 1); };
        const_reference front() const{ return const *(end() - 1); };

        // Returns pointer to the underlying array serving as element storage.
        // The pointer is such that range [data(); data() + size()) is always a valid range, even if the container is empty (data() is not dereferenceable in that case).
        T* data() { return this->a; };
        const T* data() const { return const this->a; };

        //Replaces the contents with count copies of value value
        void assign( size_type count, const T& value ){};
        //Replaces the contents with copies of those in the range [first, last). The behavior is undefined if either argument is an iterator into *this.
        template< class InputIt > void assign( InputIt first, InputIt last );

        //Returns the allocator associated with the container.
        allocator_type get_allocator() const {};

        /**
         * Capacity 
        */
        bool empty() const { return (begin() == end()); };
        // ! Difference between size() and max_size() ??
        // Returns the number of elements in the container, i.e. std::distance(begin(), end())
        size_type size() const { return (std::distance(begin(), end())) };

        // Returns the maximum number of elements the container is able to hold due to system or library implementation limitations,
        // i.e. std::distance(begin(), end()) for the largest container.
        size_type max_size() const{ return size(); };
        void reserve( size_type new_cap ){
            if(new_cap > this->capacity())
                a.allocate(this->capacity());// reallocate
            
        };
        size_type capacity() const {};
        /**
         * Modifiers 
        */

    private:
        /**
         * Container Objects
        */
        T *n;
        T *A;

    public:
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