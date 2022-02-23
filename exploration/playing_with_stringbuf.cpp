// stringstream::rdbuf
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf
#include <iomanip>

//int main () {
//  static std::string canvas;
//  canvas.insert(0, 1024, ' ');
//  canvas.replace(0, 1024, 1024, '0');
//  std::cout  << std::setprecision(10) << canvas << std::endl;
//  return 0;
//}

class treeImage {
  
  std::size_t size;
  std::size_t width;
  std::string canvas;

  std::string buildCanvas(std::size_t size){
    std::string tmp(size, ' ');
    return tmp;
  };

  std::size_t numSize(int num){
    std::size_t size = 0;
    while (num != 0){
      num /= 10;
      size++;
    }
    return size++;
  }
  int tenToThePowerOf(std::size_t exponent){
    int tmp = 10;
    if (exponent == 0){
      return 1;
    }
    while (--exponent > 0){
      tmp *= tmp;
    }
    return tmp;
  };

  std::string toString(int val){
    std::string tmp;
    std::size_t size = numSize(val);
    while (val / 10 != 0){
      tmp.push_back((val / tenToThePowerOf(size - 1)) + '0');
      val %= tenToThePowerOf(size - 1);
      size--;
    }
    tmp.push_back(val + '0');
    return tmp;
  }

  public:

    treeImage(std::size_t size, std::size_t width) : size(size), width(width), canvas(buildCanvas(size)){};
    ~treeImage(){};

    void displayImg(){
      std::size_t index = 0;
      while (index < size){
        if (index % width == 0){
         std::cout << std::endl;
        }
        std::cout << canvas[index];
        index++;
      }
    };

    void insert(std::size_t line, std::size_t column, std::string str, std::size_t len){
      std::size_t index = 0;
      const std::size_t initialPosition = line * width + column;
      if (initialPosition + len < this->size){
          while (index < len){
            canvas[initialPosition + index] = str[index];
            index++;
          }
      }
    }

    void insert(std::size_t line, std::size_t column, int num){
      std::size_t index = 0;
      std::cout << "toString output : " << toString(num) << std::endl;
      std::string strNum(toString(num));
      size_t len = strNum.length();
      const std::size_t initialPosition = line * width + column;
      if (initialPosition + len < this->size){
          while (index < len){
            canvas[initialPosition + index] = strNum[index];
            index++;
          }
      }
    }
};

int main () {
  std::size_t imgSize = 1024;
  std::size_t imgWidth = 64;
  treeImage img(imgSize, imgWidth);
  img.insert(0, imgWidth / 2, 245);
  img.insert(0, imgWidth )
  img.displayImg();
  return 0;
}
