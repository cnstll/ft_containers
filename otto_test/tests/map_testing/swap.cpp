#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include <string>
#include "../includes/map.hpp"

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
    first.swap(second);
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