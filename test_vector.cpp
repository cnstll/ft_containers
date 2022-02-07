#include "vector.hpp"
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
        std::size_t max_size = 100;
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
};