#include <memory>
#include <iostream>
#include <limits>

class memTest : public std::allocator<int> {

    public:
        //memTest(std::size_t n) : currentSize(n) {
        //    myArray = std::allocator<int>::allocate(n);
        //    
        //    std::cout << "Sizeof: " << n* sizeof(myArray);
        //    std::cout << " -- Max_size: " << std::allocator<int>::max_size();
        //    std::cout << " -- Estimated max_size: " << std::numeric_limits<int>::max() / sizeof(int);
        //    std::cout << std::endl;
        //};

        memTest(std::size_t n, int value) : currentSize(n), currentCapacity(n) {
            myArray = std::allocator<int>::allocate(n);
            for (int i = 0; i < n; i++){
                myArray[i] = value;
            }
            //std::allocator<int>::construct(myArray, value);
            
            // std::cout << "Sizeof: " << n* sizeof(myArray);
            // std::cout << " -- Max_size: " << std::allocator<int>::max_size();
            // std::cout << " -- Estimated max_size: " << std::numeric_limits<int>::max() / sizeof(int);
            // std::cout << std::endl;
        };
        ~memTest() {
            std::allocator<int>::deallocate(myArray, currentCapacity); 
        }
        void push_back(int const &e){
            
            int tmpCapacity = currentCapacity;

            while (currentSize >= tmpCapacity) 
             tmpCapacity *= 2;
            if (tmpCapacity == currentCapacity) 
            {
                myArray[currentSize] = e;
                currentSize++;
            }
            else
            {
                int *tmpArray = std::allocator<int>::allocate(tmpCapacity);
                int i = 0;
                while (i < currentSize)
                {
                    tmpArray[i] = myArray[i];
                    i++;
                }
                std::allocator<int>::deallocate(myArray, currentSize); 
                tmpArray[currentSize] = e;
                currentSize++;
                myArray = std::allocator<int>::allocate(tmpCapacity);
                i = 0;
                while (i < currentSize)
                {
                    myArray[i] = tmpArray[i];
                    i++;
                }
                std::allocator<int>::deallocate(tmpArray, tmpCapacity); 
            }
            currentCapacity = tmpCapacity;
        };
        void pop_back(void){

            if (currentSize - 1 >= 0)
            {
                currentSize--;
                std::allocator<int>::destroy(&myArray[currentSize]);
                std::cout << "current size?: "<< currentSize << " crash?: " << myArray[currentSize] << std::endl;
            }
        };

        size_t getMaxSize(void){
            return (std::allocator<int>::max_size());
        }

        size_t getSize(void){
            return (currentSize);
        }

        size_t getCapacity(void){
            return (currentCapacity);
        }
    public:

        int *myArray;
        size_t currentSize;
        size_t currentCapacity;

};

int main (void){

    // for (size_t i = 0; i < 33; i++)
    // {
        // memTest a(i, 42);
        // std::cout << "MyMaxSize: " << a.memMaxSize() << std::endl;
    // }
    memTest a(1, 42);
    int max = 10;
    for (int i = 0; i < max; i++){
        std::cout << "mySize: " << a.getSize() << " -- myCapacity: " << a.getCapacity() << std::endl;
        a.push_back(i);
    }
    std::cout << "mySize: " << a.getSize() << " -- myCapacity: " << a.getCapacity() << std::endl;
    for (int i = max; i >= 0; i--)
    {
        std::cout << "mySize: " << a.getSize() << " -- myCapacity: " << a.getCapacity() << std::endl;
        a.pop_back();
    }
    std::cout << "mySize: " << a.getSize() << " -- myCapacity: " << a.getCapacity() << std::endl;
}