#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft {

template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 ){
  InputIt1 it1 = first1;
  InputIt2 it2 = first2;

  while (it1 != last1){
    if (it2 == last2 || *it1 > *it2)
      return (false);
    else if (*it1 < *it2)
      return (true);
    ++it1;
    ++it2;
  }
  return (it2 != last2);
};

template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare cmp ){
  InputIt1 it1 = first1;
  InputIt2 it2 = first2;

  while (it1 != last1){
    if (it2 == last2 || cmp(*it2, *it1))
      return (false);
    else if (cmp(*it1, *it2))
      return (true);
    ++it1;
    ++it2;
  }
  return (it2 != last2);
};
}; //namespace
#endif