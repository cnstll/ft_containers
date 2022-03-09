#include <utility>

int main(){
  std::pair<const char, int> asciiA = std::make_pair('a', 97);
  std::pair<char, int> asciiB = asciiA;
}