#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include "../../under_test/includes/map.hpp"

int main (){

  {
    NAMESPACE::map<char,int> first;
    NAMESPACE::map<char,int> second;

    first['a'] = 97;
    first['b'] = 98;
    first['c'] = 99;
    first['d'] = 100;

    second['A'] = 65;
    second['B'] = 66;
    second['C'] = 67;
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
    first.swap(second);
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
    std::cout << "Value : " << first['A'] << std::endl;
    std::cout << "Value : " << first['B'] << std::endl;
    std::cout << "Value : " << first['C'] << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
    first['$'] = 100000;
  }
  return 0;
}