#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include "map.hpp"

int main (){

  {
    NAMESPACE::map<char,int> first;
    NAMESPACE::map<char,int> second(first);
    std::cout << "== ?" << (first == second) << std::endl;
    std::cout << "!= ?" << (first != second) << std::endl;
    std::cout << "<  ?" << (first < second)  << std::endl;
    std::cout << ">  ?" << (first > second)  << std::endl;
    std::cout << "<= ?" << (first <= second) << std::endl;
    std::cout << ">= ?" << (first >= second) << std::endl;
  }
  {
    NAMESPACE::map<char,int> first;
    NAMESPACE::map<char,int> second;
    first['b'] = 23;
    second['b'] = 23;
    std::cout << "== ?" << (first == second) << std::endl;
    std::cout << "!= ?" << (first != second) << std::endl;
    std::cout << "<  ?" << (first < second)  << std::endl;
    std::cout << ">  ?" << (first > second)  << std::endl;
    std::cout << "<= ?" << (first <= second) << std::endl;
    std::cout << ">= ?" << (first >= second) << std::endl;
  }
  {
    NAMESPACE::map<char,int> first;
    first['b'] = 23;
    first['c'] = 32;
    NAMESPACE::map<char,int> second(first);
    second['$'] = 42;
    std::cout << "== ?" << (first == second) << std::endl;
    std::cout << "!= ?" << (first != second) << std::endl;
    std::cout << "<  ?" << (first < second)  << std::endl;
    std::cout << ">  ?" << (first > second)  << std::endl;
    std::cout << "<= ?" << (first <= second) << std::endl;
    std::cout << ">= ?" << (first >= second) << std::endl;
  }
  {
    NAMESPACE::map<std::string, int> first;
    NAMESPACE::map<std::string, int> second;

    first["kitty1"] = 97;
    first["kitty2"] = 98;
    first["kitty3"] = 99;
    first["kitty4"] = 100;

    second["dog1"] = 65;
    second["dog2"] = 66;
    second["dog3"] = 67;
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
    std::cout << "Size ? : " << second.size() << std::endl;
    swap(first, second);
    std::cout << "Empty ? : " << first.empty() << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
    std::cout << "Value : " << first["dog1"] << std::endl;
    std::cout << "Value : " << first["dog2"] << std::endl;
    std::cout << "Value : " << first["dog3"] << std::endl;
    std::cout << "Size ? : " << first.size() << std::endl;
    std::cout << "Size ? : " << second.size() << std::endl;
    first["dog4"] = 200;
    second["kitty5"] = 2;
    std::cout << "Size ? : " << first.size() << std::endl;
    std::cout << "Size ? : " << second.size() << std::endl;
  }
  return 0;
}