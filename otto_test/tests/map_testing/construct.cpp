#include <map>
#include <iterator>
#include <iostream>
#include <utility>
#include "map.hpp"

bool fncomp (char lhs, char rhs) {return lhs<rhs;};

struct classcomp {
    bool operator() (const char& lhs, const char& rhs) const
    {return lhs<rhs;}
};

int main (){

  {
    NAMESPACE::map<char,int> first;
    //NAMESPACE::map<char,int> second(first);
  }
  {

//
    //std::map<char,int> second (first.begin(),first.end());
    //std::map<char,int> third (second);
//
    //std::map<char,int,classcomp> fourth;
//
    //bool(*fn_pt)(char,char) = fncomp;
    //std::map<char,int,bool(*)(char,char)> fifth (fn_pt);
//
  }

  return 0;
}