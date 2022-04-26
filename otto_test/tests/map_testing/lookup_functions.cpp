#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include "../includes/map.hpp"

int main (){

  {
    NAMESPACE::map<char, int> asciiTab;
    NAMESPACE::map<char, int>::iterator it;
    asciiTab.insert(NAMESPACE::make_pair('a', 97));
    asciiTab.insert(NAMESPACE::make_pair('b', 98));
    asciiTab.insert(NAMESPACE::make_pair('c', 99));
    asciiTab.insert(NAMESPACE::make_pair('d', 100));
    asciiTab['e'] = 101;
    asciiTab['f'] = 102;
    asciiTab[' '] = 32;
    it = asciiTab.find('a');
    if (it != asciiTab.end()){
      std::cout << "Found value: " << (it->second) << std::endl;
    } else {
      std::cout << "key not found" << std::endl;
    }
    it = asciiTab.find('$');
    if (it != asciiTab.end()){
      std::cout << "Found value: " << (it->second) << std::endl;
    } else {
      std::cout << "key not found" << std::endl;
    }
    std::cout << "Key exist ?: " << asciiTab.count('d') << std::endl;
    std::cout << "Key exist ?: " << asciiTab.count('$') << std::endl;
    std::cout << "Lower bound ?: " << (asciiTab.lower_bound('a'))->second << std::endl;
    std::cout << "Lower bound ?: " << (asciiTab.lower_bound('b'))->second << std::endl;
    std::cout << "Lower bound ?: " << (asciiTab.lower_bound('c'))->second << std::endl;
    std::cout << "Lower bound ?: " << (asciiTab.lower_bound('d'))->second << std::endl;
    std::cout << "Lower bound ?: " << (asciiTab.lower_bound('e'))->second << std::endl;
    std::cout << "Lower bound ?: " << (asciiTab.lower_bound('f'))->second << std::endl;
    std::cout << "Lower bound ?: " << (asciiTab.lower_bound(' '))->second << std::endl;
    std::cout << "Upper bound ?: " << (asciiTab.upper_bound('a'))->second << std::endl;
    std::cout << "Upper bound ?: " << (asciiTab.upper_bound('b'))->second << std::endl;
    std::cout << "Upper bound ?: " << (asciiTab.upper_bound('c'))->second << std::endl;
    std::cout << "Upper bound ?: " << (asciiTab.upper_bound('d'))->second << std::endl;
    std::cout << "Upper bound ?: " << (asciiTab.upper_bound('e'))->second << std::endl;
    std::cout << "Upper bound ?: " << (asciiTab.upper_bound(' '))->second << std::endl;
    std::cout << "Upper bound ?: " << (asciiTab.upper_bound('f'))->second << std::endl;
    if (asciiTab.upper_bound('f') == asciiTab.end()){
      std::cout << "Upper bound set to end()\n";
    } else {
      std::cout << "Error with upper bound\n";
    }
    std::cout << "Equal range - lower bound value: " << (asciiTab.equal_range('a')).first->second << " - upper bound value: " << (asciiTab.equal_range('a')).second->second << std::endl;
    std::cout << "Equal range - lower bound value: " << (asciiTab.equal_range('b')).first->second << " - upper bound value: " << (asciiTab.equal_range('b')).second->second << std::endl;
    std::cout << "Equal range - lower bound value: " << (asciiTab.equal_range('c')).first->second << " - upper bound value: " << (asciiTab.equal_range('c')).second->second << std::endl;
    std::cout << "Equal range - lower bound value: " << (asciiTab.equal_range('d')).first->second << " - upper bound value: " << (asciiTab.equal_range('d')).second->second << std::endl;
    std::cout << "Equal range - lower bound value: " << (asciiTab.equal_range('e')).first->second << " - upper bound value: " << (asciiTab.equal_range('e')).second->second << std::endl;
    std::cout << "Equal range - lower bound value: " << (asciiTab.equal_range(' ')).first->second << " - upper bound value: " << (asciiTab.equal_range(' ')).second->second << std::endl;
    std::cout << "Equal range - lower bound value: " << (asciiTab.equal_range('f')).first->second << " - upper bound value: " << (asciiTab.equal_range('f')).second->second << std::endl;
  }
  return 0;
}