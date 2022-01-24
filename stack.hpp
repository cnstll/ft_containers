#ifndef STACK_HPP
#define STACK_HPP
#include <vector>
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

    template <class T, class Container = std::vector<T> >
    class stack {


        public:

            /**
             * Member types
            */
            typedef typename Container container_type
            typedef typename Container::value_type value_type;
            typedef typename Container::size_type size_type;
            typedef typename Container::reference reference;
            typedef typename Container::const_reference const_reference;

            /**
             * Member functions
            */
            explicit stack( const Container& cont = Container() ){ std::cout << "Constructor" <<std::endl; }; 
            stack( const stack& other ){};
            stack& operator=( const stack& other ){};
            ~stack(){};

            reference top(){};
            const_reference top() const {};

        private:
    };

};
#endif