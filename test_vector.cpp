#include "vector.hpp"
#include "iterator.hpp"
#include <iostream> 
#include <vector>
#include <string>
//template <typename T>
//void sprint_vector(ft::vector<T> const &vec){
//
//    typename ft::vector<T>::const_iterator it = vec.begin();
//
//    while (it != vec.end())
//    {
//        std::cout << *it << " ";
//        it++;
//    }
//    std::cout << "\n";
//};

int main (void){

    // TESTING INT ON VECTORS
    {
        int number = 1;
        std::size_t pos = 0;
        std::size_t max_size = 5;
        //ACTIVE_NAMESPACE::vector<int> tw1(5, 21);
        ACTIVE_NAMESPACE::vector<int> s1;
        //ACTIVE_NAMESPACE::vector<int> s2(tw1);
        //ACTIVE_NAMESPACE::vector<int> s3(5, 42);

        // test Push_back
        std::cout << "Testing multiple push_back calls" << std::endl;
        while (pos < max_size) {
            s1.push_back(number);
            number += 1;
            std::cout << "Element at pos " << pos << " ? : " << s1.at(pos) << std::endl;
            std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
            pos++;
        }

        // test Pop_back
        std::cout << "Testing multiple pop_back calls" << std::endl;
        pos--;
        while (pos != 0) {
            s1.pop_back();
            pos--;
            std::cout << "Element at pos " << pos << " ? : " << s1.at(pos) << std::endl;
            std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        }
        std::cout << "Testing pop_back on empty vector" << std::endl;
        s1.pop_back();

        std::cout << "Testing out_of_range at() call" << std::endl;
        try {
            s1.at(--pos);
        } catch (std::exception &e) { std::cerr << e.what() << std::endl; }
        try {
            s1.at(s1.size());
        } catch (std::exception &e) { std::cerr << e.what() << std::endl; }

        std::cout << "Vector is empty ? : " << s1.empty() << std::endl;
	    std::cout << "Vector size ? : " << s1.size() << std::endl;
        s1.pop_back();
	    std::cout << "Vector size after pop ? : " << s1.size() << std::endl;

        std::cout << "Size of allocator ? : " << sizeof(s1.get_allocator()) << std::endl;
        //s3 = s1;
        // std::cout << "TESTING OPERATORS" << std::endl;
        // s3.pop_back();
        // std::cout << "Poped one element from copied stack" << std::endl;
        // std::cout << "s1 < s3: " << (s1 < s3) << std::endl;
        // std::cout << "s1 > s3: " << (s1 > s3) << std::endl;
        // std::cout << "s1 == s3: " << (s1 == s3) << std::endl;
        // std::cout << "s1 != s3: " << (s1 != s3) << std::endl;
        // std::cout << "s1 <= s3: " << (s1 != s3) << std::endl;
        // std::cout << "s1 >= s3: " << (s1 != s3) << std::endl;
    }
    {
        //Testing copyCtor for int
        std::cout << "Testing copy ctor an empty vector" << std::endl;
        ACTIVE_NAMESPACE::vector<int> s1;
        ACTIVE_NAMESPACE::vector<int> s2(s1);
        std::cout << "Done" << std::endl;
    }
    {
        //Testing copyCtor for int
        int pos = 0;
        std::cout << "Testing copy ctor with one el vector" << std::endl;
        ACTIVE_NAMESPACE::vector<int> s1;
        s1.push_back(42);
        s1.push_back(42);
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        ACTIVE_NAMESPACE::vector<int> s2(s1);
        std::cout << "Element at pos " << pos << " ? : " << s1.at(pos) << std::endl;
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        std::cout << "Element at pos " << pos << " ? : " << s2.at(pos) << std::endl;
        std::cout << "Size : " << s2.size() << " -- Capacity : " << s2.capacity() << std::endl;
        s1.pop_back();
        std::cout << "Deep copy? : " << std::endl;
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        std::cout << "Element at pos " << pos << " ? : " << s2.at(pos) << std::endl;
        std::cout << "Size : " << s2.size() << " -- Capacity : " << s2.capacity() << std::endl;
    }
    {
        //Testing operator= for int
        int pos = 0;
        std::cout << "Testing copy ctor with one el vector" << std::endl;
        ACTIVE_NAMESPACE::vector<int> s1;
        s1.push_back(42);
        s1.push_back(42);
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        ACTIVE_NAMESPACE::vector<int> s2;
        s2 = s1;
        std::cout << "Element at pos " << pos << " ? : " << s1.at(pos) << std::endl;
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        std::cout << "Element at pos " << pos << " ? : " << s2.at(pos) << std::endl;
        std::cout << "Size : " << s2.size() << " -- Capacity : " << s2.capacity() << std::endl;
        s1.pop_back();
        std::cout << "Deep copy? : " << std::endl;
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        std::cout << "Element at pos " << pos << " ? : " << s2.at(pos) << std::endl;
        std::cout << "Size : " << s2.size() << " -- Capacity : " << s2.capacity() << std::endl;
    }
    {
        //Testing operator= for int on empty vectors
        std::cout << "Testing copy ctor with one el vector" << std::endl;
        ACTIVE_NAMESPACE::vector<int> s1;
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        ACTIVE_NAMESPACE::vector<int> s2;
        s2 = s1;
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        std::cout << "Size : " << s2.size() << " -- Capacity : " << s2.capacity() << std::endl;
    }
    {
        std::string element = "hello";
        std::size_t pos = 0;
        std::size_t max_size = 100;
        //ACTIVE_NAMESPACE::vector<std::string> tw1(5, 21);
        ACTIVE_NAMESPACE::vector<std::string> s1;
        //ACTIVE_NAMESPACE::vector<std::string> s2(tw1);
        //ACTIVE_NAMESPACE::vector<std::string> s3(5, 42);

        // test Push_back
        std::cout << "Testing multiple push_back calls" << std::endl;
        while (pos < max_size) {
            s1.push_back(element);
            std::cout << "Element at pos " << pos << " ? : " << s1.at(pos) << std::endl;
            std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
            pos++;
        }

        // test Pop_back
        std::cout << "Testing multiple pop_back calls" << std::endl;
        pos--;
        while (pos != 0) {
            s1.pop_back();
            pos--;
            std::cout << "Element at pos " << pos << " ? : " << s1.at(pos) << std::endl;
            std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        }
        std::cout << "Testing pop_back on empty vector" << std::endl;
        s1.pop_back();

        std::cout << "Testing out_of_range at() call" << std::endl;
        try {
            s1.at(--pos);
        } catch (std::exception &e) { std::cerr << e.what() << std::endl; }
        try {
            s1.at(s1.size());
        } catch (std::exception &e) { std::cerr << e.what() << std::endl; }

        std::cout << "Vector is empty ? : " << s1.empty() << std::endl;
	    std::cout << "Vector size ? : " << s1.size() << std::endl;
        //std::cout << "Testing pop_back call on empty vector - causes undefined behaviour" << std::endl;
        //s1.pop_back();
	    //std::cout << "Vector size after pop ? : " << s1.size() << std::endl;

        std::cout << "Testing get_allocator call on empty vector" << std::endl;
        std::cout << "Size of allocator ? : " << sizeof(s1.get_allocator()) << std::endl;
        //s3 = s1;
        // std::cout << "TESTING OPERATORS" << std::endl;
        // s3.pop_back();
        // std::cout << "Poped one element from copied stack" << std::endl;
        // std::cout << "s1 < s3: " << (s1 < s3) << std::endl;
        // std::cout << "s1 > s3: " << (s1 > s3) << std::endl;
        // std::cout << "s1 == s3: " << (s1 == s3) << std::endl;
        // std::cout << "s1 != s3: " << (s1 != s3) << std::endl;
        // std::cout << "s1 <= s3: " << (s1 != s3) << std::endl;
        // std::cout << "s1 >= s3: " << (s1 != s3) << std::endl;
    }
    {
        std::cout << "Testing simple iterator ctor" << std::endl;
        ft::vector<int>::iterator it1; 
        ft::vector<int>::iterator it2(it1); 
        ft::vector<int>::iterator it3 = it1; 
    }
    {
        std::cout << "Testing simple iterator begin/end" << std::endl;
        ft::vector<int> v1; 
        ft::vector<int>::iterator it1; 
        v1.push_back(42);
        v1.push_back(21);
        v1.push_back(10);
        it1 = v1.begin();
        std::cout << "Value at beginning of vector: " << *it1 << std::endl;
        while (it1 != v1.end()) {
            std::cout << "Value at vector " << ": " << *it1 << std::endl;
            it1++;
        }
        std::cout << "Call to front returns : " << v1.front() << std::endl;
        std::cout << "Call to back returns : " << v1.back() << std::endl;
        std::cout << "Call Range ctor " << *it1 << std::endl;
        ft::vector<int> v2(v1.begin(), v1.end()); 
        std::cout << "Call to front returns : " << v2.front() << std::endl;
        std::cout << "Call to back returns : " << v2.back() << std::endl;
    }
};