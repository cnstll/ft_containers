#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include "map.hpp"

int main (){

  //NAMESPACE::map<char, int>::iterator it;
  NAMESPACE::map<char, int> asciiTab;
  NAMESPACE::pair<NAMESPACE::map<char, int>::iterator, bool> ret = asciiTab.insert(NAMESPACE::make_pair('a', 97));
  std::cout << "Data was inserted ? : " << ret.second << std::endl;
  //std::cout << "Data inserted : " << (*ret.first).first << std::endl;
  asciiTab['b'] = 98;
  asciiTab['c'] = 99;
  asciiTab['d'] = 100;
  asciiTab[' '] = 32;
  //std::cout << "Data inserted : " << asciiTab['b'] << std::endl;
  //std::cout << "Data inserted : " << asciiTab['d'] << std::endl;
  //std::cout << "Data inserted : " << asciiTab['e'] << std::endl; //looking for a key that does not exist, insert the key with a default mapped_value
  //std::cout << "Data inserted : " << asciiTab[' '] << std::endl;
  NAMESPACE::map<char, int> asciiUpper;
  asciiUpper['B'] = 66;
  asciiUpper['C'] = 67;
  asciiUpper['D'] = 68;
  std::cout << "begin() value: " << (asciiUpper.begin())->second << std::endl;
  std::cout << "end() value: " << (asciiUpper.end())->second << std::endl;
  asciiTab.insert(asciiUpper.begin(), asciiUpper.end());
  std::cout << "Data inserted : " << asciiTab['d'] << std::endl;
  std::cout << "Data inserted : " << asciiTab['B'] << std::endl;  
  std::cout << "Data inserted : " << asciiTab['D'] << std::endl;
}