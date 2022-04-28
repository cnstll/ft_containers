#include "../includes/map.hpp"
#include <map>
#include <iostream>
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
  int numberOfElementInserted = 10000000;
  while (numberOfElementInserted > 0){
    asciiTab.insert(NAMESPACE::make_pair(genRandomNum(), 42));
    numberOfElementInserted--;
  }
  asciiTab.erase(asciiTab.begin(), asciiTab.end());
}