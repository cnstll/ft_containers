//#include "vector.hpp"
#include <iostream> 
#include <vector>

int main (void){

    {
        int ft = 42;
        std::vector<int> tw1(5, 21);
        std::vector<int> s1;
        std::vector<int> s2(s1);
        std::vector<int> s3(5, 42);
        std::vector<int> s4;
        std::vector<int> s5;

        //Assign
        s1.assign(5, 84);
        s5.assign(tw1.begin(), tw1.end());
        s4 = s3;
        //Allocator
        s1.get_allocator();
        s2.get_allocator();
        s3.get_allocator();
        s4.get_allocator();
        s5.get_allocator();

        // At
        try{
            int pos = 0;
            int value = s1.at(pos);
            std::cout << "Vector value at pos " << pos << " is : " << value << std::endl;
        }
        catch(std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        try{
            int pos = 42;
            int value = s1.at(pos);
            std::cout << "Vector value at pos " << pos << " is : " << value << std::endl;
        }
        catch(std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        try{
            int pos = 5;
            int value = s1.at(pos);
            std::cout << "Vector value at pos " << pos << " is : " << value << std::endl;
        }
        catch(std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        // Multiple functions on empty vector 
        {
            std::cout << "Failing functions on empty vector" << std::endl;
            std::vector<int> s6;
            std::cout << "max_size ? : " << s6.max_size() << std::endl;
            std::cout << "operator[].." << std::endl;
            s6[2];
            std::cout << "front.." << std::endl;
            s6.front();
            std::cout << "back.." << std::endl;
            s6.back();
            std::cout << "pointer ? : " << s6.data() << std::endl;
            std::cout << "size ? : " << s6.size() << std::endl;
            std::cout << "max_size ? : " << s6.max_size() << std::endl;
            std::cout << "capacity ? : " << s6.capacity() << std::endl;
        }
        // Multiple functions on empty vector 
        {
            std::cout << "Failing reserve function" << std::endl;
            std::vector<int> s6;
            try{
                long int cap = 2305843009213693951;
                s6.reserve(cap);
            }
            catch(std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
        std::cout << "Vector is empty ? : " << s1.empty() << std::endl;
	    std::cout << "Vector size ? : " << s1.size() << std::endl;
	    //std::cout << "Vector top ? : " << s1.top() << std::endl; // Segfault
        s1.push_back(ft);
        ft /= 2;
        s1.push_back(ft);
        ft /= 2;
        s1.push_back(ft);
        ft /= 2;
        s1.push_back(ft);

        std::cout << "Vector is empty ? : " << s1.empty() << std::endl;
	    std::cout << "Vector size ? : " << s1.size() << std::endl;
        s1.pop_back();
	    std::cout << "Vector size after pop ? : " << s1.size() << std::endl;
        s3 = s1;
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