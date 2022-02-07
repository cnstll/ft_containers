#include "vector.hpp"
#include <iostream> 

template <typename T>
void sprint_vector(std::vector<T> const &vec){

    typename std::vector<T>::const_iterator it = vec.begin();

    while (it != vec.end())
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << "\n";
};

int main (void){

    {
        int ft = 42;
        ft::vector<int> tw1(5, 21);
        ft::vector<int> s1;
        ft::vector<int> s2(tw1);
        ft::vector<int> s3(5, 42);

        //Assign
        s1.push_back(ft);
        //ft /= 2;
        s1.push_back(ft);
        //ft /= 2;
        s1.push_back(ft);
        //ft /= 2;
        s1.push_back(ft);

        std::cout << "Vector is empty ? : " << s1.empty() << std::endl;
	    std::cout << "Vector size ? : " << s1.size() << std::endl;
        s1.pop_back();
	    std::cout << "Vector size after pop ? : " << s1.size() << std::endl;
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