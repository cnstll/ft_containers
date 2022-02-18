#include <vector>
#include <iterator>
#include <iostream>

int main(){
  std::vector<int> v1;
  for (int i = 0; i < 7; i++) {
    v1.push_back(i);
  }
  std::vector<int>::iterator it1 = v1.begin();
  std::vector<int>::reverse_iterator rit1(it1);
  std::cout << *rit1 << std::endl;
  std::cout << *it1 << std::endl;
  std::cout << *(rit1) << std::endl;
  --rit1;
  std::cout << *(rit1) << std::endl;
  --rit1;
  --rit1;
  --rit1;
  --rit1;
  std::cout << *(rit1) << std::endl;
  ++rit1;
  std::cout << *(rit1) << std::endl;
  std::cout << (*(++rit1.base())) << std::endl;
  rit1 = v1.rbegin();
  std::cout << *(rit1) << std::endl;
  rit1 = v1.rend();
  std::cout << *(rit1) << std::endl;
  std::cout << (rit1[-2]) << std::endl;
  std::cout << *(rit1->real()) << std::endl;
  
  }