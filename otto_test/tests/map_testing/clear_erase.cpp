#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include "../includes/map.hpp"

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
  {
    NAMESPACE::map<char,int> first;
    first['a'] = 97;
    first['b'] = 98;
    first['c'] = 99;
    first['d'] = 100;
    NAMESPACE::map<char, int>::iterator it = first.begin();
    std::cout << "Before erase: \n";
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
    first.erase(it);
    std::cout << "After erase: \n";
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
  }
  {
    NAMESPACE::map<int, int> asciiTab;
    int numberOfElementInserted = 10;
    while (numberOfElementInserted > 0){
      asciiTab[numberOfElementInserted] = 42;
      numberOfElementInserted--;
    }
    asciiTab.erase(asciiTab.find(1), asciiTab.find(10));
  }
  return 0;
}