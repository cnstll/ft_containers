#include <stack>
#include <vector>
#include <iostream>
#include <utility>
#include "../includes/stack.hpp"


int main (){

  {
    //capacity on empty stack
    NAMESPACE::stack<int, std::vector<int> > first;
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
  }
  {
    NAMESPACE::stack<int, std::vector<int> > first;
    first.push(97);
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
    first.push(98);
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
  }

  return 0;
}