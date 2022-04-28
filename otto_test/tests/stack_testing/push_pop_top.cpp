#include <stack>
#include <vector>
#include <iostream>
#include <utility>
#include "../includes/stack.hpp"

int main (){

    NAMESPACE::stack<int, std::vector<int> > first;
    int numberOfElementToInsert = 10000;
    while (numberOfElementToInsert > 0){
      first.push(numberOfElementToInsert);
      std::cout << "Top ?: " << first.top() << std::endl;
      std::cout << "Size ? : " << first.size() << std::endl;
      numberOfElementToInsert--;
    }
    numberOfElementToInsert = 10000;
    while (numberOfElementToInsert > 0){
      std::cout << "Top ?: " << first.top() << std::endl;
      std::cout << "Size ? : " << first.size() << std::endl;
      first.pop();
      numberOfElementToInsert--;
    }
}