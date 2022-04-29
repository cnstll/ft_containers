#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"
#include <iostream>

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

template <
    class T, 
    class Container = ft::vector< T >
> class stack {


    public:

        /**
         * Typefs Member types
        */
        typedef Container container_type;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

        /**
         * Member functions
        */
        explicit stack( const Container& cont = Container() ) : c(cont) {}; 
        stack( const stack& other ){ this->c = other.c; };
        stack& operator=( const stack& other ){ this->c = other.c; return *this;};
        ~stack(){};

        /**
         * Element access 
        */
        reference top(){ return c.back(); };
        const_reference top() const { return c.back(); };

        /**
         * Capacity 
        */
        bool empty() const { return c.empty(); };
        size_type size() const { return c.size(); };

        /**
         * Modifiers 
        */
        void push( const value_type& value ) { c.push_back(value); };
        void pop() { c.pop_back(); };


    protected :
        /**
         * Member Object (vector by default)
        */
        Container c;

    public :
        /**
         * Non member functions that require access to the protected Member Object "c" 
        */

    template< class _T, class _Container >
        friend bool operator<( const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs );

    template< class _T, class _Container >
        friend bool operator==( const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs );
};
// TODO: look into EqualityComparable requirement https://en.cppreference.com/w/cpp/named_req/EqualityComparable
/**
 * Non member functions
*/

// Operator "<" and "==" are used to build the other operator overloads to limit the use of "friend" functions
template< class T, class Container >
    bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c < rhs.c); };

template< class T, class Container >
    bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c == rhs.c); };

template< class T, class Container >
    bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return !(lhs == rhs); };

template< class T, class Container >
    bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return !(rhs < lhs); };

template< class T, class Container >
bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (rhs < lhs); };

template< class T, class Container >
    bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return !(lhs < rhs); };

}; // namespace

#endif