#include "stack.hpp"
#include <iostream> 
#include <stack>
#include <vector>

int main (void){

    {
        int ft = 42;
        ft::stack<int> s1; 
        ft::stack<int> s2(s1); 
        ft::stack<int> s3;

        s3 = s2;
        std::cout << "Stack is empty ? : " << s1.empty() << std::endl;
	    std::cout << "Stack size ? : " << s1.size() << std::endl;
	    //std::cout << "Stack top ? : " << s1.top() << std::endl; // Segfault
        s1.push(ft);
        ft /= 2;
        s1.push(ft);
        ft /= 2;
        s1.push(ft);
        ft /= 2;
        s1.push(ft);

        std::cout << "Stack is empty ? : " << s1.empty() << std::endl;
	    std::cout << "Stack size ? : " << s1.size() << std::endl;
        std::cout << "Stack top element ? : " << s1.top() << std::endl;
        s1.pop();
	    std::cout << "Stack size after pop ? : " << s1.size() << std::endl;
        std::cout << "Stack top element after pop ? : " << s1.top() << std::endl;
        s3 = s1;
        std::cout << "Stack top element in src stack ? : " << s1.top() << std::endl;
        std::cout << "Stack top element in copied stack ? : " << s3.top() << std::endl;
        std::cout << "TESTING OPERATORS" << std::endl;
        s3.pop();
        std::cout << "Poped one element from copied stack" << std::endl;
        std::cout << "s1 < s3: " << (s1 < s3) << std::endl;
        std::cout << "s1 > s3: " << (s1 > s3) << std::endl;
        std::cout << "s1 == s3: " << (s1 == s3) << std::endl;
        std::cout << "s1 != s3: " << (s1 != s3) << std::endl;
        std::cout << "s1 <= s3: " << (s1 != s3) << std::endl;
        std::cout << "s1 >= s3: " << (s1 != s3) << std::endl;
    }
    {
        int std = 42;
        std::stack<int, std::vector<int>> s1; 
        std::stack<int, std::vector<int>> s2(s1); 
        std::stack<int, std::vector<int>> s3;

        s3 = s2;
        std::cout << "Stack is empty ? : " << s1.empty() << std::endl;
	    std::cout << "Stack size ? : " << s1.size() << std::endl;
	    //std::cout << "Stack top ? : " << s1.top() << std::endl; // Segfault
        s1.push(std);
        std /= 2;
        s1.push(std);
        std /= 2;
        s1.push(std);
        std /= 2;
        s1.push(std);

        std::cout << "Stack is empty ? : " << s1.empty() << std::endl;
	    std::cout << "Stack size ? : " << s1.size() << std::endl;
        std::cout << "Stack top element ? : " << s1.top() << std::endl;
        s1.pop();
	    std::cout << "Stack size astder pop ? : " << s1.size() << std::endl;
        std::cout << "Stack top element astder pop ? : " << s1.top() << std::endl;
        s3 = s1;
        std::cout << "Stack top element in src stack ? : " << s1.top() << std::endl;
        std::cout << "Stack top element in copied stack ? : " << s3.top() << std::endl;
        std::cout << "TESTING OPERATORS" << std::endl;
        s3.pop();
        std::cout << "Poped one element from copied stack" << std::endl;
        std::cout << "s1 < s3: " << (s1 < s3) << std::endl;
        std::cout << "s1 > s3: " << (s1 > s3) << std::endl;
        std::cout << "s1 == s3: " << (s1 == s3) << std::endl;
        std::cout << "s1 != s3: " << (s1 != s3) << std::endl;
        std::cout << "s1 <= s3: " << (s1 != s3) << std::endl;
        std::cout << "s1 >= s3: " << (s1 != s3) << std::endl;
    }
};
