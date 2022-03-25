#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include "map.hpp"

int main()
{
  {
    NAMESPACE::map<char, int> asciiTab;
    asciiTab.insert(NAMESPACE::make_pair('a', 97));
    asciiTab.insert(NAMESPACE::make_pair('b', 98));
    asciiTab.insert(NAMESPACE::make_pair('c', 99));
    asciiTab.insert(NAMESPACE::make_pair('d', 100));
    NAMESPACE::map<char, int>::iterator it(asciiTab.begin());
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    ++it;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    --it;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    it++;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    it--;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    it++;
    ++it;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    it--;
    --it;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    ++it;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    it--;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    NAMESPACE::map<char, int>::iterator it2;
    it2 = asciiTab.end();
    it2--;
    it2--;
    std::cout << "it == ?" << (it == it2) << std::endl;
    std::cout << "it != ?" << (it != it2) << std::endl;
  }
  {
    NAMESPACE::map<char, int> asciiTab;
    asciiTab.insert(NAMESPACE::make_pair('a', 97));
    asciiTab.insert(NAMESPACE::make_pair('b', 98));
    asciiTab.insert(NAMESPACE::make_pair('c', 99));
    asciiTab.insert(NAMESPACE::make_pair('d', 100));
    NAMESPACE::map<char, int>::const_iterator it(asciiTab.begin());
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    ++it;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    --it;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    it++;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    it--;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    it++;
    ++it;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    it--;
    --it;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    ++it;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    it--;
    std::cout << "Key: " << (*it).first << "Value: " << (*it).second << std::endl;
    NAMESPACE::map<char, int>::const_iterator it2;
    it2 = asciiTab.end();
    it2--;
    it2--;
    std::cout << "it == ?" << (it == it2) << std::endl;
    std::cout << "it != ?" << (it != it2) << std::endl;
  }
};