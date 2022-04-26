#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include "../includes/map.hpp"

int main (){

  //NAMESPACE::map<char, int>::iterator it;
  NAMESPACE::map<char, int> asciiTab;
  NAMESPACE::pair<NAMESPACE::map<char, int>::iterator, bool> ret = asciiTab.insert(NAMESPACE::make_pair('a', 97));
  NAMESPACE::pair<NAMESPACE::map<char, int>::iterator, bool> ret1 = asciiTab.insert(NAMESPACE::make_pair('b', 98));
  NAMESPACE::pair<NAMESPACE::map<char, int>::iterator, bool> ret2 = asciiTab.insert(NAMESPACE::make_pair('c', 99));
  NAMESPACE::pair<NAMESPACE::map<char, int>::iterator, bool> ret3 = asciiTab.insert(NAMESPACE::make_pair('d', 100));
  
  std::cout << "Data was inserted ? : " << ret.second << std::endl;
  std::cout << "Data was inserted ? : " << ret1.second << std::endl;
  std::cout << "Data was inserted ? : " << ret2.second << std::endl;
  std::cout << "Data was inserted ? : " << ret3.second << std::endl;
  
  std::cout << "Data inserted : " << (*ret.first).first << std::endl;
  // Inserting new and already existing keys in the map
  asciiTab['e'] = 101;
  asciiTab['f'] = 102;
  asciiTab['a'] = 97;
  asciiTab[' '] = 32;
  std::cout << "Data inserted : " << asciiTab['b'] << std::endl;
  std::cout << "Data inserted : " << asciiTab['d'] << std::endl;
  std::cout << "Data inserted : " << asciiTab['e'] << std::endl; //looking for a key that does not exist, insert the key with a default mapped_value
  std::cout << "Data inserted : " << asciiTab[' '] << std::endl;
  NAMESPACE::map<char, int> asciiUpper;
  asciiUpper['B'] = 66;
  asciiUpper['C'] = 67;
  asciiUpper['D'] = 68;
  //testing beginning and end function for map
  std::cout << "begin() value: " << (asciiUpper.begin())->second << std::endl;
  std::cout << "end() value: " << (asciiUpper.end())->second << std::endl;
  //Inserting a map into another map
  asciiTab.insert(asciiUpper.begin(), asciiUpper.end());
  std::cout << "Data inserted : " << asciiTab['a'] << std::endl;
  std::cout << "Data inserted : " << asciiTab['b'] << std::endl;
  std::cout << "Data inserted : " << asciiTab['c'] << std::endl;
  std::cout << "Data inserted : " << asciiTab['d'] << std::endl;
  std::cout << "Data inserted : " << asciiTab['B'] << std::endl;  
  std::cout << "Data inserted : " << asciiTab['C'] << std::endl;  
  std::cout << "Data inserted : " << asciiTab['D'] << std::endl;
}