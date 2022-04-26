#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include "../includes/map.hpp"
#include <cstdlib>

int genRandomNum(){
	static bool done = false;
    if (done == false){
  		std::srand(time(NULL));
		done = true;
	}
	return std::rand();
}

int main (){

  NAMESPACE::map<int, int> asciiTab;
  int numberOfElementInserted = 1000000;
  while (numberOfElementInserted > 0){
    asciiTab.insert(NAMESPACE::make_pair(genRandomNum(), 42));
    numberOfElementInserted--;
  }
  // NAMESPACE::map<int, int>::iterator it = asciiTab.begin()
    asciiTab.erase(asciiTab.begin(), asciiTab.end());
}