#include <stack>
#include <vector>
#include <iostream>
#include <utility>
#include "../includes/stack.hpp"

int main (){

  {
    NAMESPACE::stack<int, std::vector<int> > first;
    NAMESPACE::stack<int, std::vector<int> > second(first);
    std::cout << "== ?" << (first == second) << std::endl;
    std::cout << "!= ?" << (first != second) << std::endl;
    std::cout << "<  ?" << (first < second)  << std::endl;
    std::cout << ">  ?" << (first > second)  << std::endl;
    std::cout << "<= ?" << (first <= second) << std::endl;
    std::cout << ">= ?" << (first >= second) << std::endl;
  }
  {
    NAMESPACE::stack<int, std::vector<int> > first;
    NAMESPACE::stack<int, std::vector<int> > second;
    first.push(23);
    second.push(23);
    std::cout << "== ?" << (first == second) << std::endl;
    std::cout << "!= ?" << (first != second) << std::endl;
    std::cout << "<  ?" << (first < second)  << std::endl;
    std::cout << ">  ?" << (first > second)  << std::endl;
    std::cout << "<= ?" << (first <= second) << std::endl;
    std::cout << ">= ?" << (first >= second) << std::endl;
  }
  {
    NAMESPACE::stack<int, std::vector<int> > first;
    first.push(23);
    first.push(24);
    NAMESPACE::stack<int, std::vector<int> > second(first);
    second.push(42);
    std::cout << "== ?" << (first == second) << std::endl;
    std::cout << "!= ?" << (first != second) << std::endl;
    std::cout << "<  ?" << (first < second)  << std::endl;
    std::cout << ">  ?" << (first > second)  << std::endl;
    std::cout << "<= ?" << (first <= second) << std::endl;
    std::cout << ">= ?" << (first >= second) << std::endl;
  }

  return 0;
}