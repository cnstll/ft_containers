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

  return 0;
}