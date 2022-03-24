#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include "map.hpp"

bool fncomp (char lhs, char rhs) {return lhs<rhs;};

struct classcomp {
    bool operator() (const char& lhs, const char& rhs) const
    {return lhs<rhs;}
};

int main (){

  {
    NAMESPACE::map<char,int> first;
    first['a'] = 97;
    first['b'] = 98;
    first['c'] = 99;
    first['d'] = 100;
    first.clear();
  }
  {
    NAMESPACE::map<char,int> first;
    first['a'] = 97;
    first['b'] = 98;
    first['c'] = 99;
    first['d'] = 100;
    first.clear();
    //controll size
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
  }
  {
    NAMESPACE::map<char,int> first;
    first['a'] = 97;
    first['b'] = 98;
    first['c'] = 99;
    first['d'] = 100;
    std::cout << "Before erase: \n";
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
    std::cout << "Erase return: " << first.erase('c') << std::endl;
    std::cout << "Erase return: " << first.erase('$') << std::endl;
    std::cout << "After erase: \n";
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
  }
  return 0;
}