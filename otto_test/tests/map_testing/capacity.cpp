#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include "../includes/map.hpp"

int main (){

  {
    //capacity on empty map
    NAMESPACE::map<char,int> first;
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
    first.max_size();
  }
  {
    NAMESPACE::map<char, int> first;
    first['a'] = 97;
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
    first.max_size();
    first['b'] = 98;
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
    first.max_size();
  }

  return 0;
}