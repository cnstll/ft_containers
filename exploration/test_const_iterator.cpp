#include <vector>
#include <iterator>
#include <iostream>

int main ()
{
    {
        std::vector<int> a(15, 42);
        std::vector<int>::const_iterator cit;
        std::vector<int>::const_iterator cit2;
        std::vector<int>::const_iterator cit3;

        cit = a.begin() + 1;
        std::cout << *cit << std::endl;
        std::cout << cit[0] << std::endl;
        cit++;
        ++cit;
        cit--;
        --cit;
        cit + 1;
        cit2 = a.begin();
        cit - cit2;
        cit2+= 2;
        cit2-= 1;
        std::cout << (cit < cit2) <<std::endl;
        std::cout << (cit > cit2) <<std::endl;
        std::cout << (cit >= cit2) <<std::endl;
        std::cout << (cit <= cit2) <<std::endl;
        std::cout << (cit == cit2) <<std::endl;
        std::cout << (cit != cit2) <<std::endl;

        std::cout << "size: " << a.size() << " -- capacity: " << a.capacity(); 
        std::cout << std::endl;
        cit3 = cit;
    }

    return 0;
}