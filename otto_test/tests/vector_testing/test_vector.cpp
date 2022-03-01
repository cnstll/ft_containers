#include "iterator.hpp"
#include "./your_files/includes/vector.hpp"
#include <iostream> 
#include <vector>
#include <string>

int main (void){

    // TESTING INT ON VECTORS
    {
        int number = 1;
        std::size_t pos = 0;
        std::size_t max_size = 5;
        //NAMESPACE::vector<int> tw1(5, 21);
        NAMESPACE::vector<int> s1;
        //NAMESPACE::vector<int> s2(tw1);
        //NAMESPACE::vector<int> s3(5, 42);

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
        try {
            s1.at(42);
        } catch (std::exception &e) { std::cerr << e.what() << std::endl; }

        std::cout << "Vector is empty ? : " << s1.empty() << std::endl;
	    std::cout << "Vector size ? : " << s1.size() << std::endl;
        s1.pop_back();
	    std::cout << "Vector size after pop ? : " << s1.size() << std::endl;

        std::cout << "Size of allocator ? : " << sizeof(s1.get_allocator()) << std::endl;
        //s3 = s1;
    }
    {
        //Testing copyCtor for int
        std::cout << "Testing copy ctor an empty vector" << std::endl;
        NAMESPACE::vector<int> s1;
        NAMESPACE::vector<int> s2(s1);
        s2.insert(s2.begin(), 5, 42);
        NAMESPACE::vector<int> s3(s2.rbegin(), s2.rend() - 2);
        std::cout << "Done" << std::endl;
    }
    {
        //Testing copyCtor for int
        int pos = 0;
        std::cout << "Testing copy ctor with one el vector" << std::endl;
        NAMESPACE::vector<int> s1;
        s1.push_back(42);
        s1.push_back(42);
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        NAMESPACE::vector<int> s2(s1);
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
        NAMESPACE::vector<int> s1;
        s1.push_back(42);
        s1.push_back(42);
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        NAMESPACE::vector<int> s2;
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
        NAMESPACE::vector<int> s1;
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        NAMESPACE::vector<int> s2;
        s2 = s1;
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        std::cout << "Size : " << s2.size() << " -- Capacity : " << s2.capacity() << std::endl;
    }
    {
        std::string element = "hello";
        std::size_t pos = 0;
        std::size_t max_size = 100;
        //NAMESPACE::vector<std::string> tw1(5, 21);
        NAMESPACE::vector<std::string> s1;
        //NAMESPACE::vector<std::string> s2(tw1);
        //NAMESPACE::vector<std::string> s3(5, 42);

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
        std::cout << "Testing assign on int vector" << std::endl;
        NAMESPACE::vector<int> s1;
        NAMESPACE::vector<int> s2(23, 4);
        s1.assign(5, 42);
        NAMESPACE::vector<int>::iterator it1 = s1.begin();
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        while (it1 != s1.end()){
            std::cout << "Value after assign: " << *it1 << std::endl;
            it1++;
        }
        s1.assign(17, 21);
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        it1 = s1.begin();
        while (it1 != s1.end()){
            std::cout << "Value after assign: " << *it1 << std::endl;
            it1++;
        }
        s1.assign(2, 10);
        it1 = s1.begin();
        std::cout << "Size : " << s1.size() << " -- Capacity : " << s1.capacity() << std::endl;
        while (it1 != s1.end()){
            std::cout << "Value after assign: " << *it1 << std::endl;
            it1++;
        }
        s2.assign(s1.begin(), s1.end());
        std::cout << "Size : " << s2.size() << " -- Capacity : " << s2.capacity() << std::endl;
        it1 = s2.begin();
        while (it1 != s2.end()){
        std::cout << "Value after assign: " << *it1 << std::endl;
        it1++;
        }
    }
    {
        std::cout << "Testing simple iterator ctor" << std::endl;
        NAMESPACE::vector<std::string>::iterator it1; 
        NAMESPACE::vector<std::string>::iterator it2(it1); 
        NAMESPACE::vector<std::string>::iterator it3 = it1; 
        NAMESPACE::vector<std::string>::const_iterator it4;
        NAMESPACE::vector<std::string>::const_iterator it5(it1);
        NAMESPACE::vector<std::string>::const_iterator it6 = it2;
        NAMESPACE::vector<std::string>::const_iterator it7 = it5;
        *it3;
        it6 - it7;
    }
    {
        std::cout << "Testing simple iterator begin/end" << std::endl;
        NAMESPACE::vector<int> v1; 
        NAMESPACE::vector<int>::iterator it1; 
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
        NAMESPACE::vector<int> v2(v1.begin(), v1.end()); 
        std::cout << "Call to front returns : " << v2.front() << std::endl;
        std::cout << "Call to back returns : " << v2.back() << std::endl;
    }
    {
        std::cout << "Testing iterator operation and comparisons" << std::endl;
        NAMESPACE::vector<int> v1; 
        NAMESPACE::vector<int>::iterator it1; 
        v1.push_back(42);
        v1.push_back(21);
        v1.push_back(10);
        it1 = v1.begin();
        std::cout << "Value at beginning of vector: " << *it1 << std::endl;
        std::cout << "Value at beginning of vector: " << it1[0] << std::endl;
        std::cout << "Value at vector : " << *it1 << std::endl;
        std::cout << "Value at vector : " << *(it1 + 1) << std::endl;
        std::cout << "Value at vector : " << *(++it1) << std::endl;
        it1++;
        std::cout << "Value at vector : " << *it1 << std::endl;
        it1--;
        std::cout << "Value at vector : " << *it1 << std::endl;
        std::cout << "Value at vector : " << *(--it1) << std::endl;
        it1+=1;
        std::cout << "Value at vector : " << *it1 << std::endl;
        it1-=1;
        std::cout << "Value at vector : " << *it1 << std::endl;
        std::cout << "Value at vector : " << it1[0] << std::endl;
        std::cout << "Value at vector : " << it1[1] << std::endl;
        std::cout << "Value at vector : " << it1[2] << std::endl;
        std::cout << "Value at vector : " << (it1 - v1.begin()) << std::endl;
        NAMESPACE::vector<int>::iterator it2; 
        std::cout << "Iterator comparison > result : " << (it2 > it1) << std::endl;
        std::cout << "Iterator comparison < result : " << (it2 < it1) << std::endl;
        std::cout << "Iterator comparison <= result : " << (it2 <= it1) << std::endl;
        std::cout << "Iterator comparison >= result : " << (it2 >= it1) << std::endl;
        std::cout << "Iterator comparison == result : " << (it2 == it1) << std::endl;
        std::cout << "Iterator comparison << result : " << (it2 != it1) << std::endl;
    }
    {
        std::cout << "Testing simple iterator begin/end" << std::endl;
        NAMESPACE::vector<int> v1; 
        NAMESPACE::vector<int>::const_iterator it1; 
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
        NAMESPACE::vector<int> v2(v1.begin(), v1.end()); 
        std::cout << "Call to front returns : " << v2.front() << std::endl;
        std::cout << "Call to back returns : " << v2.back() << std::endl;
    }
    {
        std::cout << "Testing const iterator operation and comparisons" << std::endl;
        NAMESPACE::vector<int> v1; 
        NAMESPACE::vector<int>::const_iterator it1; 
        v1.push_back(42);
        v1.push_back(21);
        v1.push_back(10);
        it1 = v1.begin();
        std::cout << "Value at beginning of vector: " << *it1 << std::endl;
        std::cout << "Value at beginning of vector: " << it1[0] << std::endl;
        std::cout << "Value at vector : " << *it1 << std::endl;
        std::cout << "Value at vector : " << *(it1 + 1) << std::endl;
        std::cout << "Value at vector : " << *(++it1) << std::endl;
        it1++;
        std::cout << "Value at vector : " << *it1 << std::endl;
        it1--;
        std::cout << "Value at vector : " << *it1 << std::endl;
        std::cout << "Value at vector : " << *(--it1) << std::endl;
        it1+=1;
        std::cout << "Value at vector : " << *it1 << std::endl;
        it1-=1;
        std::cout << "Value at vector : " << *it1 << std::endl;
        std::cout << "Value at vector : " << it1[0] << std::endl;
        std::cout << "Value at vector : " << it1[1] << std::endl;
        std::cout << "Value at vector : " << it1[2] << std::endl;
        std::cout << "Value at vector : " << (it1 - v1.begin()) << std::endl;
        NAMESPACE::vector<int>::const_iterator it2; 
        std::cout << "Iterator comparison > result : " << (it2 > it1) << std::endl;
        std::cout << "Iterator comparison < result : " << (it2 < it1) << std::endl;
        std::cout << "Iterator comparison <= result : " << (it2 <= it1) << std::endl;
        std::cout << "Iterator comparison >= result : " << (it2 >= it1) << std::endl;
        std::cout << "Iterator comparison == result : " << (it2 == it1) << std::endl;
        std::cout << "Iterator comparison != result : " << (it2 != it1) << std::endl;
    }
    {
        std::cout << "Testing const iterator operation and comparisons" << std::endl;
        NAMESPACE::vector<int> v1; 
        NAMESPACE::vector<int>::const_iterator it1; 
        v1.push_back(42);
        v1.push_back(21);
        v1.push_back(10);
        it1 = v1.begin();
        std::cout << "Value at beginning of vector: " << *it1 << std::endl;
        std::cout << "Value at beginning of vector: " << it1[0] << std::endl;
        std::cout << "Value at vector : " << *it1 << std::endl;
        std::cout << "Value at vector : " << *(it1 + 1) << std::endl;
        std::cout << "Value at vector : " << *(++it1) << std::endl;
        it1++;
        std::cout << "Value at vector : " << *it1 << std::endl;
        it1--;
        std::cout << "Value at vector : " << *it1 << std::endl;
        std::cout << "Value at vector : " << *(--it1) << std::endl;
        it1+=1;
        std::cout << "Value at vector : " << *it1 << std::endl;
        it1-=1;
        std::cout << "Value at vector : " << *it1 << std::endl;
        std::cout << "Value at vector : " << it1[0] << std::endl;
        std::cout << "Value at vector : " << it1[1] << std::endl;
        std::cout << "Value at vector : " << it1[2] << std::endl;
        std::cout << "Value at vector : " << (it1 - v1.begin()) << std::endl;
        NAMESPACE::vector<int>::iterator it2 = v1.begin(); 
        std::cout << "Iterator comparison > result : " << (it2 > it1) << std::endl;
        std::cout << "Iterator comparison < result : " << (it2 < it1) << std::endl;
        std::cout << "Iterator comparison <= result : " << (it2 <= it1) << std::endl;
        std::cout << "Iterator comparison >= result : " << (it2 >= it1) << std::endl;
        std::cout << "Iterator comparison == result : " << (it2 == it1) << std::endl;
        std::cout << "Iterator comparison != result : " << (it2 != it1) << std::endl;
    }
    {
        std::cout << "Testing simple iterator ctor for strings" << std::endl;
        NAMESPACE::vector<std::string>::iterator it1; 
        NAMESPACE::vector<std::string>::iterator it2(it1); 
        NAMESPACE::vector<std::string>::iterator it3 = it1; 
        NAMESPACE::vector<std::string>::const_iterator it4;
        NAMESPACE::vector<std::string>::const_iterator it5(it1);
        NAMESPACE::vector<std::string>::const_iterator it6 = it2;
        NAMESPACE::vector<std::string>::const_iterator it7 = it5;
        *it3;
        it6 - it7;
    }
    {
        std::cout << "Testing simple iterator begin/end for strings" << std::endl;
        NAMESPACE::vector<std::string> v1; 
        NAMESPACE::vector<std::string>::iterator it1; 
        v1.push_back("banana");
        v1.push_back("papaya");
        v1.push_back("apple");
    
        it1 = v1.begin();
        std::cout << "Value at beginning of vector: " << *it1 << std::endl;
        while (it1 != v1.end()) {
            std::cout << "Value at vector " << ": " << *it1 << std::endl;
            it1++;
        }
        std::cout << "Call to front returns : " << v1.front() << std::endl;
        std::cout << "Call to back returns : " << v1.back() << std::endl;
    //std::cout << "Call Range ctor " << *it1 << std::endl;
        NAMESPACE::vector<std::string> v2(v1.begin(), v1.end()); 
        std::cout << "Call to front returns : " << v2.front() << std::endl;
        std::cout << "Call to back returns : " << v2.back() << std::endl;
    }
    {
        std::cout << "Testing iterator operation and comparisons for strings" << std::endl;
        NAMESPACE::vector<std::string> v1; 
        NAMESPACE::vector<std::string>::iterator it1; 
        v1.push_back("banana");
        v1.push_back("papaya");
        v1.push_back("apple");
        it1 = v1.begin();
        std::cout << "Value at beginning of vector: " << *it1 << std::endl;
        std::cout << "Value at vector : " << *it1 << std::endl;
        std::cout << "Value at vector : " << *(it1 + 1) << std::endl;
        std::cout << "Value at vector : " << *(++it1) << std::endl;
        it1++;
        std::cout << "Value at vector : " << *it1 << std::endl;
        it1--;
        std::cout << "Value at vector : " << *it1 << std::endl;
        std::cout << "Value at vector : " << *(--it1) << std::endl;
        it1+=1;
        std::cout << "Value at vector : " << *it1 << std::endl;
        it1-=1;
        std::cout << "Value at vector : " << *it1 << std::endl;
        std::cout << "Value at vector : " << it1[0] << std::endl;
        std::cout << "Value at vector : " << it1[1] << std::endl;
        std::cout << "Value at vector : " << it1[2] << std::endl;
        std::cout << "Value at vector : " << (it1 - v1.begin()) << std::endl;
        NAMESPACE::vector<std::string>::iterator it2; 
        std::cout << "Iterator comparison result : " << (it2 > it1) << std::endl;
        std::cout << "Iterator comparison result : " << (it2 < it1) << std::endl;
        std::cout << "Iterator comparison result : " << (it2 <= it1) << std::endl;
        std::cout << "Iterator comparison result : " << (it2 >= it1) << std::endl;
        std::cout << "Iterator comparison result : " << (it2 == it1) << std::endl;
        std::cout << "Iterator comparison result : " << (it2 != it1) << std::endl;
    }
    {
        std::cout << "Testing simple reverse_iterator ctor and operator and comparison" << std::endl;
        NAMESPACE::vector<int> v1;
        v1.push_back(42);
        v1.push_back(21);
        v1.push_back(10);
        NAMESPACE::vector<int>::iterator it1 = v1.begin();
        NAMESPACE::vector<int>::reverse_iterator rit1;
        NAMESPACE::vector<int>::reverse_iterator rit2(it1);
        NAMESPACE::vector<int>::reverse_iterator rit3(rit1);
        rit1 = rit2;
        rit1.base();
        std::cout << *rit1.base() << std::endl;
        std::cout << *(rit1.base() + 1) << std::endl;
        std::cout << *(rit1.base() + 2) << std::endl;
        std::cout << *(rit1.base() + 3) << std::endl;
        //std::cout << rit1[0] << std::endl;
        std::cout << rit1[-1] << std::endl;
        std::cout << rit1[-2] << std::endl;
        std::cout << rit1[-3] << std::endl;
        --rit1;
        std::cout << *rit1.base() << std::endl;
        rit1--;
        std::cout << *rit1 << std::endl;
        rit1--;
        std::cout << *rit1 << std::endl;
        std::cout << *(rit1 + 2) << std::endl;
        ++rit1;
        std::cout << *rit1 << std::endl;
        rit1++;
        std::cout << *rit1 << std::endl;
        std::cout << *(rit1 - 2) << std::endl;
        rit1-=2;
        std::cout << *rit1 << std::endl;
        rit1+=1;
        std::cout << *rit1 << std::endl;
        rit1 = v1.rbegin();
        while (rit1 != v1.rend()){
            std::cout << "Reversed iteration through vector yield: " << *rit1 << std::endl;
            rit1++;
        }
        std::cout << *v1.rbegin() << std::endl;
        std::cout << *(v1.rbegin() + 1) << std::endl;
        std::cout << *(v1.rend() - 1) << std::endl;
    }
        {
        std::cout << "Testing reverse_iterator comparisons and additional non-member operators" << std::endl;
        NAMESPACE::vector<int> v1; 
        NAMESPACE::vector<int>::iterator it1; 
        v1.push_back(42);
        v1.push_back(21);
        v1.push_back(10);
        it1 = v1.begin();
        NAMESPACE::vector<int>::reverse_iterator rit1(it1);
        it1+=2;
        NAMESPACE::vector<int>::reverse_iterator rit2(v1.end()); 
        std::cout << "Reverse iterator comparison > result : " << (rit2 > rit1) << std::endl;
        std::cout << "Reverse iterator comparison < result : " << (rit2 < rit1) << std::endl;
        std::cout << "Reverse iterator comparison <= result : " << (rit2 <= rit1) << std::endl;
        std::cout << "Reverse iterator comparison >= result : " << (rit2 >= rit1) << std::endl;
        std::cout << "Reverse iterator comparison == result : " << (rit2 == rit1) << std::endl;
        std::cout << "Reverse iterator comparison != result : " << (rit2 != rit1) << std::endl;
        std::cout << "Advancing rit with op+" << std::endl;
        (rit2 + 2);
        std::cout << *rit2 << std::endl;
        std::cout << "Diff between 2 rit :" << (rit2 - rit1) << std::endl;
    }
    {
        std::cout << "Testing simple reverse_iterator ctor and operator and comparison" << std::endl;
        NAMESPACE::vector<int> v1;
        v1.push_back(42);
        v1.push_back(21);
        v1.push_back(10);
        NAMESPACE::vector<int>::const_iterator it1 = v1.begin();
        NAMESPACE::vector<int>::const_reverse_iterator rit1;
        NAMESPACE::vector<int>::const_reverse_iterator rit2(it1);
        NAMESPACE::vector<int>::const_reverse_iterator rit3(rit1);
        rit1 = rit2;
        rit1.base();
        std::cout << *rit1.base() << std::endl;
        std::cout << *(rit1.base() + 1) << std::endl;
        std::cout << *(rit1.base() + 2) << std::endl;
        std::cout << *(rit1.base() + 3) << std::endl;
        //std::cout << rit1[0] << std::endl;
        std::cout << rit1[-1] << std::endl;
        std::cout << rit1[-2] << std::endl;
        std::cout << rit1[-3] << std::endl;
        --rit1;
        std::cout << *rit1.base() << std::endl;
        rit1--;
        std::cout << *rit1 << std::endl;
        rit1--;
        std::cout << *rit1 << std::endl;
        std::cout << *(rit1 + 2) << std::endl;
        ++rit1;
        std::cout << *rit1 << std::endl;
        rit1++;
        std::cout << *rit1 << std::endl;
        std::cout << *(rit1 - 2) << std::endl;
        rit1-=2;
        std::cout << *rit1 << std::endl;
        rit1+=1;
        std::cout << *rit1 << std::endl;
    }
        {
        std::cout << "Testing const_reverse_iterator comparisons and additional non-member operators" << std::endl;
        NAMESPACE::vector<int> v1; 
        NAMESPACE::vector<int>::const_iterator it1; 
        v1.push_back(42);
        v1.push_back(21);
        v1.push_back(10);
        it1 = v1.begin();
        NAMESPACE::vector<int>::const_reverse_iterator rit1(it1);
        it1+=2;
        NAMESPACE::vector<int>::const_reverse_iterator rit2(v1.end()); 
        std::cout << "Reverse iterator comparison > result : " << (rit2 > rit1) << std::endl;
        std::cout << "Reverse iterator comparison < result : " << (rit2 < rit1) << std::endl;
        std::cout << "Reverse iterator comparison <= result : " << (rit2 <= rit1) << std::endl;
        std::cout << "Reverse iterator comparison >= result : " << (rit2 >= rit1) << std::endl;
        std::cout << "Reverse iterator comparison == result : " << (rit2 == rit1) << std::endl;
        std::cout << "Reverse iterator comparison != result : " << (rit2 != rit1) << std::endl;
        std::cout << "Advancing rit with op+" << std::endl;
        (rit2 + 2);
        std::cout << *rit2 << std::endl;
        std::cout << "Diff between 2 rit :" << (rit2 - rit1) << std::endl;
    }
    {
        std::cout << "Testing looping on reserve calls" << std::endl;
        NAMESPACE::vector<int> v1; 
        std::size_t i = 0;
        std::size_t max = 100;
        v1.push_back(42);
        v1.push_back(21);
        v1.push_back(10);
        while (i < max) {
            v1.reserve(i);
            std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
            ++i;
        }
        std::cout << "Call to front returns : " << v1.front() << std::endl;
        std::cout << "Call to back returns : " << v1.back() << std::endl;
    }
    {
        std::cout << "Testing reserve call with max_size" << std::endl;
        NAMESPACE::vector<int> v1; 
        try {
            v1.reserve(v1.max_size() + 1);
        }
        catch (std::exception &e){ std::cerr << e.what() << std::endl; };
    }
    {
        std::cout << "Testing clear" << std::endl;
        std::size_t sz = 42;
        // ! Erreur de compilation si le type n'est pas précisé pour la size -> pb overload avec le range ctor
        NAMESPACE::vector<int> v1(sz, 21);  
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        v1.clear();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        NAMESPACE::vector<int> v2;  
        v1.clear();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;

    }
    {
        std::cout << "Testing simple insert on int" << std::endl;
        NAMESPACE::vector<int> v1;  
        NAMESPACE::vector<int>::iterator it1 = v1.end();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        std::cout << "Value inserted : " << *(v1.insert(it1, 2)) << std::endl;
        NAMESPACE::vector<int>::iterator it2 = v1.end();
        std::cout << "Value inserted : " << *(v1.insert(it2, 3)) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        NAMESPACE::vector<int>::iterator it3 = v1.begin();
        std::cout << "Value inserted : " << *(v1.insert(it3, 1)) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it3 = v1.end();
        --it3;
        --it3;
        std::cout << "Value inserted : " << *(v1.insert(it3, 42)) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "Value inserted : " << *it1 << std::endl;
            it1++;
        }
    }
    {
        std::cout << "Testing simple insert on str" << std::endl;
        NAMESPACE::vector<std::string> v1;  
        NAMESPACE::vector<std::string>::iterator it1 = v1.end();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        std::cout << "Value inserted : " << *(v1.insert(it1, "apple")) << std::endl;
        NAMESPACE::vector<std::string>::iterator it2 = v1.end();
        std::cout << "Value inserted : " << *(v1.insert(it2, "banana")) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        NAMESPACE::vector<std::string>::iterator it3 = v1.begin();
        std::cout << "Value inserted : " << *(v1.insert(it3, "cacao")) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it3 = v1.end();
        --it3;
        --it3;
        std::cout << "Value inserted : " << *(v1.insert(it3, "chips")) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "Value inserted : " << *it1 << std::endl;
            it1++;
        }
    }
    {
        std::cout << "Testing insert count values on int" << std::endl;
        NAMESPACE::vector<int> v1;  
        NAMESPACE::vector<int>::iterator it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        v1.insert(it1, 5, 42);
        it1 = v1.begin() + 2;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        v1.insert(it1, 5, 21);
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.end();
        v1.insert(it1, 5, 10);
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        v1.insert(it1, 5, 5);
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "Value inserted : " << *it1 << std::endl;
            it1++;
        }
    }
    {
        std::cout << "Testing insert count values on str" << std::endl;
        NAMESPACE::vector<std::string> v1;  
        NAMESPACE::vector<std::string>::iterator it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        v1.insert(it1, 5, "apple");
        it1 = v1.begin() + 2;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        v1.insert(it1, 5, "banana");
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.end();
        v1.insert(it1, 5, "caffafle");
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        v1.insert(it1, 5, "cacao");
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "Value inserted : " << *it1 << std::endl;
            it1++;
        }
    }
    {
        std::cout << "Testing insert a range of value on int" << std::endl;
        NAMESPACE::vector<int> v1;
        NAMESPACE::vector<int> v2(5, 42);
        NAMESPACE::vector<int> v3(5, 21);
        NAMESPACE::vector<int> v4(5, 10);
        NAMESPACE::vector<int>::iterator it1 = v1.begin();
        NAMESPACE::vector<int>::iterator range_begin = v2.begin();
        NAMESPACE::vector<int>::iterator range_end = v2.end();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        v1.insert(it1, range_begin, range_end);
        it1 = v1.begin() + 2;
        range_begin = v3.begin();
        range_end = v3.end();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        v1.insert(it1, range_begin, range_end);
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.end();
        range_begin = v4.begin();
        range_end = v4.end();
        v1.insert(it1, range_begin, range_end);
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        v1.insert(it1, range_begin, range_end);
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "Value inserted : " << *it1 << std::endl;
            it1++;
        }
    }
    {
        std::cout << "Testing erase a value from int vector" << std::endl;
        NAMESPACE::vector<int> v1(5, 42);
        NAMESPACE::vector<int>::iterator it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        std::cout << "Iterator following last removed el: " << *(v1.erase(it1)) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
        it1 = v1.begin() + 2;
        std::cout << "Iterator following last removed el: " << *(v1.erase(it1)) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
        it1 = v1.end() - 1;
        std::cout << "Iterator following last removed el is v1.end(): " << (v1.erase(it1) == v1.end()) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
    }
    {
        std::cout << "Testing erase a value from str vector" << std::endl;
        NAMESPACE::vector<std::string> v1(5, "banana");
        NAMESPACE::vector<std::string>::iterator it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        std::cout << "Iterator following last removed el: " << *(v1.erase(it1)) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
        it1 = v1.begin() + 2;
        std::cout << "Iterator following last removed el: " << *(v1.erase(it1)) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
        it1 = v1.end() - 1;
        std::cout << "Iterator following last removed el is v1.end(): " << (v1.erase(it1) == v1.end()) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
    }
    {
        std::cout << "Testing erase a range of values from int vector" << std::endl;
        NAMESPACE::vector<int> v1;
        std::size_t i = 0;
        while (i < 20){
            v1.push_back(i);
            i++;
        }
        NAMESPACE::vector<int>::iterator it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        std::cout << "Iterator following last removed el: " << *(v1.erase(it1, it1 + 1)) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
        it1 = v1.begin() + 7;
        std::cout << "Iterator following last removed el: " << *(v1.erase(it1, v1.end())) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
        it1 = v1.end();
        std::cout << "Iterator following last removed el is v1.end(): " << (v1.erase(it1 - 4, it1) == v1.end()) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
        it1 = v1.end();
        std::cout << "Iterator following last removed el is v1.end(): " << (v1.erase(it1, it1) == v1.end()) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
        it1 = v1.begin();
        std::cout << "Iterator following last removed el: " << *(v1.erase(it1, it1)) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
    }
    {
        std::cout << "Testing erase a range of values from std::string vector" << std::endl;
        NAMESPACE::vector<std::string> v1;
        std::size_t i = 0;
        std::string el = "apples";
        while (i < 20){
            v1.push_back(el);
            i++;
        }
        NAMESPACE::vector<std::string>::iterator it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        std::cout << "Iterator following last removed el: " << *(v1.erase(it1, it1 + 1)) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
        it1 = v1.begin() + 7;
        std::cout << "Iterator following last removed el: " << *(v1.erase(it1, v1.end())) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
        it1 = v1.end();
        std::cout << "Iterator following last removed el is v1.end(): " << (v1.erase(it1 - 4, it1) == v1.end()) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
        it1 = v1.end();
        std::cout << "Iterator following last removed el is v1.end(): " << (v1.erase(it1, it1) == v1.end()) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
        it1 = v1.begin();
        std::cout << "Iterator following last removed el: " << *(v1.erase(it1, it1)) << std::endl;
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        it1 = v1.begin();
        while (it1 != v1.end()){
            std::cout << "value in vector after erase : " << *it1 << std::endl;
            it1++;
        }
    }
    {
        std::cout << "Testing resize int vector" << std::endl;
        NAMESPACE::vector<int> v1;
        std::size_t i = 0;
        while (i < 20){
            v1.push_back(i);
            i++;
        }
        NAMESPACE::vector<int>::iterator it1 = v1.begin();
        v1.resize(30, 42);
        it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        while (it1 != v1.end()){
            std::cout << "value in vector after resize : " << *it1 << std::endl;
            it1++;
        }
        v1.resize(20, 42);
        it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        while (it1 != v1.end()){
            std::cout << "value in vector after resize : " << *it1 << std::endl;
            it1++;
        }
        v1.resize(10, 42);
        it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        while (it1 != v1.end()){
            std::cout << "value in vector after resize : " << *it1 << std::endl;
            it1++;
        }
    }
    {
        std::cout << "Testing resize str vector" << std::endl;
        NAMESPACE::vector<std::string> v1;
        std::size_t i = 0;
        std::string el = "potato";
        while (i < 20){
            v1.push_back(el);
            i++;
        }
        NAMESPACE::vector<std::string>::iterator it1 = v1.begin();
        v1.resize(30, "banana");
        it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        while (it1 != v1.end()){
            std::cout << "value in vector after resize : " << *it1 << std::endl;
            it1++;
        }
        v1.resize(20, "banana");
        it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        while (it1 != v1.end()){
            std::cout << "value in vector after resize : " << *it1 << std::endl;
            it1++;
        }
        v1.resize(10, "banana");
        it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        while (it1 != v1.end()){
            std::cout << "value in vector after resize : " << *it1 << std::endl;
            it1++;
        }
    }
    {
        std::cout << "Testing swap int vector" << std::endl;
        NAMESPACE::vector<int> v1;
        NAMESPACE::vector<int> v2(10, 42);
        NAMESPACE::vector<int>::iterator it2 = v2.begin();
        std::size_t i = 0;
        while (i < 20){
            v1.push_back(i);
            i++;
        }
        NAMESPACE::vector<int>::iterator it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        std::cout << "Size : " << v2.size() << " -- Capacity : " << v2.capacity() << std::endl;
        v1.swap(v2);
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        std::cout << "Size : " << v2.size() << " -- Capacity : " << v2.capacity() << std::endl;
        while (it1 != v2.end()){
            std::cout << "value in vector after swap : " << *it1 << std::endl;
            it1++;
        }
        while (it2 != v1.end()){
            std::cout << "value in vector after swap : " << *it2 << std::endl;
            it2++;
        }
        swap(v1, v2);
        while (it1 != v1.end()){
            std::cout << "value in vector after swap : " << *it1 << std::endl;
            it1++;
        }
        while (it2 != v2.end()){
            std::cout << "value in vector after swap : " << *it2 << std::endl;
            it2++;
        }
    }
    {
        std::cout << "Testing swap int vector" << std::endl;
        NAMESPACE::vector<std::string> v1;
        NAMESPACE::vector<std::string> v2(10, "world");
        NAMESPACE::vector<std::string>::iterator it2 = v2.begin();
        std::size_t i = 0;
        while (i < 20){
            v1.push_back("hello");
            i++;
        }
        NAMESPACE::vector<std::string>::iterator it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        std::cout << "Size : " << v2.size() << " -- Capacity : " << v2.capacity() << std::endl;
        v1.swap(v2);
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        std::cout << "Size : " << v2.size() << " -- Capacity : " << v2.capacity() << std::endl;
        //it1 = v1.begin();
        while (it1 != v2.end()){
            std::cout << "value in vector after swap : " << *it1 << std::endl;
            it1++;
        }
        //it2 = v2.begin();
        while (it2 != v1.end()){
            std::cout << "value in vector after swap : " << *it2 << std::endl;
            it2++;
        }
    }
    {
        std::cout << "Testing external swap int vector" << std::endl;
        NAMESPACE::vector<int> v1;
        NAMESPACE::vector<int> v2(10, 42);
        NAMESPACE::vector<int>::iterator it2 = v2.begin();
        std::size_t i = 0;
        while (i < 20){
            v1.push_back(i);
            i++;
        }
        NAMESPACE::vector<int>::iterator it1 = v1.begin();
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        std::cout << "Size : " << v2.size() << " -- Capacity : " << v2.capacity() << std::endl;
        NAMESPACE::swap(v1, v2);
        std::cout << "Size : " << v1.size() << " -- Capacity : " << v1.capacity() << std::endl;
        std::cout << "Size : " << v2.size() << " -- Capacity : " << v2.capacity() << std::endl;
        //it1 = v1.begin();
        while (it1 != v2.end()){
            std::cout << "value in vector after swap : " << *it1 << std::endl;
            it1++;
        }
        //it2 = v2.begin();
        while (it2 != v1.end()){
            std::cout << "value in vector after swap : " << *it2 << std::endl;
          it2++;
      }
    }
    {
        NAMESPACE::vector<int> s1;
        NAMESPACE::vector<int> s2;
        NAMESPACE::vector<int> s3(5, 42);
        NAMESPACE::vector<int> s4(5, 42);
        NAMESPACE::vector<int> s5(4, 42);
        NAMESPACE::vector<int> s6(5, 21);
        std::cout << "TESTING OPERATORS both empty vector" << std::endl;
        std::cout << "s1 < s2: " << (s1 < s2) << std::endl;
        std::cout << "s1 > s2: " << (s1 > s2) << std::endl;
        std::cout << "s1 == s2: " << (s1 == s2) << std::endl;
        std::cout << "s1 != s2: " << (s1 != s2) << std::endl;
        std::cout << "s1 <= s2: " << (s1 != s2) << std::endl;
        std::cout << "s1 >= s2: " << (s1 != s2) << std::endl;
        std::cout << "TESTING OPERATORS one empty vector" << std::endl;
        std::cout << "s1 < s3: " << (s1 < s3) << std::endl;
        std::cout << "s1 > s3: " << (s1 > s3) << std::endl;
        std::cout << "s1 == s3: " << (s1 == s3) << std::endl;
        std::cout << "s1 != s3: " << (s1 != s3) << std::endl;
        std::cout << "s1 <= s3: " << (s1 != s3) << std::endl;
        std::cout << "s1 >= s3: " << (s1 != s3) << std::endl;
        std::cout << "TESTING OPERATORS non empty" << std::endl;
        std::cout << "s6 < s3: " << (s6 < s3) << std::endl;
        std::cout << "s6 > s3: " << (s6 > s3) << std::endl;
        std::cout << "s6 == s3: " << (s6 == s3) << std::endl;
        std::cout << "s6 != s3: " << (s6 != s3) << std::endl;
        std::cout << "s6 <= s3: " << (s6 != s3) << std::endl;
        std::cout << "s6 >= s3: " << (s6 != s3) << std::endl;
        std::cout << "TESTING OPERATORS one vector is a subset of the other" << std::endl;
        std::cout << "s5 < s3: " << (s5 < s3) << std::endl;
        std::cout << "s5 > s3: " << (s5 > s3) << std::endl;
        std::cout << "s5 == s3: " << (s5 == s3) << std::endl;
        std::cout << "s5 != s3: " << (s5 != s3) << std::endl;
        std::cout << "s5 <= s3: " << (s5 != s3) << std::endl;
        std::cout << "s5 >= s3: " << (s5 != s3) << std::endl;
        std::cout << "TESTING OPERATORS equal vectors" << std::endl;
        std::cout << "s4 < s3: " << (s4 < s3) << std::endl;
        std::cout << "s4 > s3: " << (s4 > s3) << std::endl;
        std::cout << "s4 == s3: " << (s4 == s3) << std::endl;
        std::cout << "s4 != s3: " << (s4 != s3) << std::endl;
        std::cout << "s4 <= s3: " << (s4 != s3) << std::endl;
        std::cout << "s4 >= s3: " << (s4 != s3) << std::endl;
    }
}; //Namespace
    