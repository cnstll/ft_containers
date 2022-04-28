#include <stack>
#include <vector>
#include <iostream>
#include <utility>
#include "../includes/stack.hpp"

int main (){

  {
    NAMESPACE::stack<int, std::vector<int> > first;
    NAMESPACE::stack<int, std::vector<int> > second(first);
  }
  {
    NAMESPACE::stack<int, std::vector<int> > first;
    first.push(23);
    first.push(24);
    NAMESPACE::stack<int, std::vector<int> > second(first);
  }
  {
    NAMESPACE::stack<int, std::vector<int> > first;
    first.push(23);
    first.push(24);
    NAMESPACE::stack<int, std::vector<int> > second = first;
  }
  return 0;
}