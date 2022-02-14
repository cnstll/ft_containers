#include <vector>
#include <iostream>

int main ()
{
    {
        std::vector<int> a;
        int maxIteration = 8;

        std::cout << "size: " << a.size() << " -- capacity: " << a.capacity(); 
        //a.reserve(2);
        std::cout << std::endl;
        for (int i = 0; i <= maxIteration; i++)
        {
            std::cout << "Adding one int.." << std::endl;
            a.push_back(i);
            std::cout << "size: " << a.size() << " -- capacity: " << a.capacity(); 
            std::cout << std::endl;
        }
        for (int i = maxIteration; i >= 0; i--)
        {
            std::cout << "Removing one int.." << std::endl;
            a.pop_back();
            std::cout << "size: " << a.size() << " -- capacity: " << a.capacity(); 
            std::cout << std::endl;
        }
        std::cout << "Element at 0: " << a[0] << std::endl;
        std::cout << "Element at 1: " << a[1] << std::endl;
        std::cout << "Element at 2: " << a[2] << std::endl;
        std::cout << "Element at 3: " << a[3] << std::endl;
        std::cout << "Element at 4: " << a[4] << std::endl;
        std::cout << "Element at 5: " << a[5] << std::endl;
        std::cout << "Element at front: " << a.front() << std::endl;
        std::cout << "Element at back: " << a.back() << std::endl;
        try { std::cout << "Element at 0 using at(): " << a.at(1) << std::endl;}
        catch (std::exception &e) {std::cout << e.what() << std::endl;};
        try { std::cout << "Pop back on empty array " << std::endl; a.pop_back(); }
        catch (std::exception &e) {std::cout << e.what() << std::endl;};
    }
    {
        std::vector<int> a(9, 42);

        std::cout << "size: " << a.size() << " -- capacity: " << a.capacity(); 
        std::cout << std::endl;
        a.push_back(42);
        std::cout << "size: " << a.size() << " -- capacity: " << a.capacity(); 
        std::cout << std::endl;
    }
    return 0;
}