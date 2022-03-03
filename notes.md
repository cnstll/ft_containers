## Notions
* Duck typing: "If it walks like a duck and it quacks like a duck, then it must be a duck" In duck type, a data structure is considered of given type if it has the properties and the methods of that type. The duck test can be checked statically or dynamically.
* Binary Search Trees: "is a rooted binary tree data structure whose internal nodes each store a key greater than all the keys in the node's left subtree and less than those in its right subtree" (wikipedia). Time complexity is bound to the tree height and is usually logarithmic. Though in the worst case, unbalanced tree can become a single linked list with a linear complexity.
* Red-Black Tree: red-black tree is a self-balancing binary search tree. It's a typical BST whose nodes are labeled as "Red" or "Black" and each node is "recolored" and may rebalanced after the tree is modified (insertion or removal). Balancing the tree is done through these set of rules:
  "1- Each node is either red or black. 
  2- All NIL nodes (figure 1) are considered black. 
  3- A red node does not have a red child. 
  4- Every path from a given node to any of its descendant NIL nodes goes through the same number of black nodes."(wikipedia)   

## Sources
* [Google Guide on CPP conventions](https://google.github.io/styleguide/cppguide.html)
* [Why should you use explicit keyword ?](https://google.github.io/styleguide/cppguide.html#Implicit_Conversions)
* [On duck typing](https://en.wikipedia.org/wiki/Duck_typing)
* [Creating your own containers](https://stdcxx.apache.org/doc/stdlibug/16-3.html)
* [On building a vector container](https://medium.com/@vgasparyan1995/how-to-write-an-stl-compatible-container-fc5b994462c6)
* [Clockwise / Spiral Rule](http://c-faq.com/decl/spiral.anderson.html)
* [Iterator implementation](https://stackoverflow.com/questions/3582608/how-to-correctly-implement-custom-iterators-and-const-iterators)
* [Strong exception guarantee](https://stackoverflow.com/questions/12137555/strong-exception-guarantee-vs-basic-exception-guarantee)
* [Compiler flags](https://gcc.gnu.org/onlinedocs/gcc-11.2.0/gcc/Overall-Options.html#Overall-Options)
* [On iterator traits](https://www.fluentcpp.com/2018/05/08/std-iterator-deprecated/)
* [Wikipedia on Binary Trees](https://en.wikipedia.org/wiki/Binary_search_tree)
* [Wikipedia on Red Black Tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)
* [About Binary Tree Sentinel](https://en.wikipedia.org/wiki/Sentinel_node#Search_in_a_binary_tree)
* [Implementation of a simple BST](https://hurna.io/fr/academy/data_structures/bst.html)
* [Implementation of a RBT in C++](https://www.programiz.com/dsa/red-black-tree)
* [Implementation of a RBT in python](https://brilliant.org/wiki/red-black-tree/)
* [About Invariant in Code](https://en.wikipedia.org/wiki/Loop_invariant)
* [Good Post on rebinding an allocator](https://stackoverflow.com/questions/14148756/what-does-template-rebind-do)