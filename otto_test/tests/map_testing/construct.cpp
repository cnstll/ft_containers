#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include "map.hpp"

int main (){

  {
    NAMESPACE::map<char,int> first;
    NAMESPACE::map<char,int> second(first);
  }
  {
    NAMESPACE::map<char,int> first;
    NAMESPACE::map<char,int> second(first);
    first['b'] = 23;
    second['$'] = 42;
  }
  {
    NAMESPACE::map<char,int> first;
    first['b'] = 23;
    first['c'] = 32;
    NAMESPACE::map<char,int> second(first);
    second['$'] = 42;
    first['d'] = 33;
  }
  {
    NAMESPACE::map<char,int> first;
    first['b'] = 23;
    first['c'] = 32;
    NAMESPACE::map<char,int> second = first;
    second['$'] = 42;
    first['d'] = 33;
  }
  {
    NAMESPACE::map<char,int> first;
    first['b'] = 23;
    first['c'] = 32;
    first['d'] = 33;
    NAMESPACE::map<char,int> second(first.begin(), first.end());
    NAMESPACE::map<char,int>::iterator it = second.begin();
    while(it != second.end()){
      std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
      ++it;
    }
  }
  return 0;
}