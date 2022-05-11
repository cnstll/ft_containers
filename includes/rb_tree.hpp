#ifndef RBTREE_HPP
#define RBTREE_HPP
#define red 1
#define black 0
#include "pair.hpp"
#include "utilities.hpp"
#include <functional>
#include <iostream> 
#include <memory> // mem allocation
#include <string>

namespace ft {
  /**
 * @brief Node structure used in RedBlackTree class that contains the parent of the node, right and left childs and the color stored in a boolean
 * 
 */
template <class T>
class mapNode {
  public:
  T data;
  mapNode<T> *parent;
  mapNode<T> *left;
  mapNode<T> *right;
  bool color; // change from int to bool
  bool isSentinel;
  mapNode<T> *lastUpdatedRoot; // Only valid for the sentinel node

  mapNode() : data(), parent(NULL), left(NULL), right(NULL), color(black), isSentinel(true), lastUpdatedRoot(NULL){}
  mapNode(const T& d) : data(d), parent(NULL), left(NULL), right(NULL), color(black), isSentinel(true), lastUpdatedRoot(NULL){}
  mapNode(const T& d, mapNode<T> *p, mapNode<T> *l, mapNode<T>* r, bool c, bool s, mapNode<T>* lastRoot) : data(d), parent(p), left(l), right(r), color(c), isSentinel(s), lastUpdatedRoot(lastRoot){}
  mapNode(const mapNode& other) : data(other.data), parent(other.parent), left(other.left), right(other.right), color(other.color), isSentinel(other.isSentinel), lastUpdatedRoot(other.lastUpdatedRoot){}
  ~mapNode(){}

  mapNode<T> *getSuccessor() {
    if (!right->isSentinel)
      return right->getMin();
    mapNode<T> *searchedParent = parent;
    mapNode<T> *tmp = this;
    while (!searchedParent->isSentinel && tmp == searchedParent->right)
    {
      tmp = searchedParent;
      searchedParent = searchedParent->parent;
    }
    return searchedParent;
  };

  mapNode<T> *getPredecessor() {
    if (!left->isSentinel)
      return left->getMax();
    mapNode<T> *searchedParent = parent;
    mapNode<T> *tmp = this;
    while (!searchedParent->isSentinel && tmp == searchedParent->left)
    {
      tmp = searchedParent;
      searchedParent = searchedParent->parent;
    }
    return searchedParent;
  };

  mapNode<T> *getMax() {
    mapNode<T> *tmp = this;
    if (tmp->isSentinel){
      tmp = tmp->lastUpdatedRoot;
    }
    while (!tmp->right->isSentinel)
      tmp = tmp->right;
    return tmp;
  };

  mapNode<T> *getMin() {
    mapNode<T> *tmp = this;
    if (tmp->isSentinel){
      tmp = tmp->lastUpdatedRoot;
    }
    while (!tmp->left->isSentinel)
      tmp = tmp->left;
    return tmp;
  };

};

template <typename T1, typename T2>
bool operator==(const mapNode<T1>& lhs, const mapNode<T2>& rhs) { return lhs.data == rhs.data; };


/**
 * @brief Red black tree handling data storing for map container. The tree is self-balancing.
 *        Search, insert and remove operations are performed in O(log n) time.
 * 
 * @param T value_type passed from map
 * @param Compare comp function passed from map in order to compare keys while operating on the tree. Std::less by default.
 * @param Allocator tree allocator rebinded to node allocator
 * @return iterator to the node where key was found or end() if no node with key was found
 */

template <
    class T,
    class Allocator,
    class Compare = std::less<T>
> class RedBlackTree {
  
  typedef T key_value_pair;
  typedef typename ft::mapNode<T> node;
  typedef Compare key_compare;
  typedef std::size_t size_type;
  typedef Allocator tree_allocator_type;
  typedef typename tree_allocator_type::template rebind<node>::other node_allocator_type;

  node *root;
  node *sentinel;
  node *lastInsertedNode;
  node_allocator_type nodeAllocator;
  key_compare comp;
  std::size_t countNode;

  void _preOrderTraversal(node * node) {
    if (node != sentinel) {
      std::cout << node->data.first << " ";
      _preOrderTraversal(node->left);
      _preOrderTraversal(node->right);
    }
  }

  void _inOrderTraversal(node * node) {
    if (node != sentinel) {
      _inOrderTraversal(node->left);
      std::cout << node->data << " ";
      _inOrderTraversal(node->right);
    }
  }

  void _postOrderTraversal(node * node) {
    if (node != sentinel) {
      _postOrderTraversal(node->left);
      _postOrderTraversal(node->right);
      std::cout << node->data << " ";
    }
  }

  bool _isRed(node *current){
    return (current->color == red);
  };

  bool _isBlack(node *current){
    return (current->color == black);
  };

  bool _hasLeftChild(node *current){
    return (current->left != sentinel);
  };

  bool _hasRightChild(node *current){
    return (current->right != sentinel);
  };

  void _setColor(node *current, bool redOrBlack){
      current->color = redOrBlack;
  };

  bool _isLeftChild(node *current, node *parent){
    return (current == parent->left);
  };

  bool _isRightChild(node *current, node *parent){
    return (current == parent->right);
  };

  /**
   * @brief search tree with in order traversal method
   * 
   * @param node active node
   * @param data pair of key and value. The key is searched in the tree
   * @return address of the node found 
   */
  
  node *_searchTree(node * node,  key_value_pair data) const {
    if (node == sentinel || data.first == node->data.first) {
      return node;
    }
    //If data.first < node->data.first
    if (comp(data.first, node->data.first)) {
      return _searchTree(node->left, data);
    }
    return _searchTree(node->right, data);
  }

  void _timber(node *root){
    if (root->isSentinel)
      return;
    {
        _timber(root->left);
        _timber(root->right);
        --countNode;
        _nodeDeletionHelper(root);
    }
  };

  void _printTree(const std::string& padding, node* current, bool hasRight){ 
    if(!current->isSentinel)
    {
      std::cerr << padding << (hasRight ? "|__" : "└──" );
      if (current->color == red)
        std::cerr << current->data.first << "," << current->data.second << std::endl;
      else
        std::cerr << current->data.first << "." << current->data.second << std::endl;
      _printTree(padding + (hasRight ? "│   " : "    "), current->left, (!current->right->isSentinel));
      _printTree(padding + (hasRight ? "│   " : "    "), current->right, false);
    }
  };

  /* 
   *  INSERTION SECTION
   */
  void _recolorAndBalanceTreeAfterInsert(node * current) {
    node *u;
    while (_isRed(current->parent)) {
      if (_isRightChild(current->parent, current->parent->parent)) {
        u = current->parent->parent->left;
        if (_isRed(u)) {
          _setColor(u, black);
          _setColor(current->parent, black);
          _setColor(current->parent->parent, red);
          current = current->parent->parent;
        } else {
          if (_isLeftChild(current, current->parent->left)) {
            current = current->parent;
            _rightRotate(current);
          }
          _setColor(current->parent, black);
          _setColor(current->parent->parent, red);
          _leftRotate(current->parent->parent);
        }
      } else {
        u = current->parent->parent->right;
        if (_isRed(u)) {
          _setColor(u, black);
          _setColor(current->parent, black);
          _setColor(current->parent->parent, red);
          current = current->parent->parent;
        } else {
          if (_isRightChild(current, current->parent)) {
            current = current->parent;
            _leftRotate(current);
          }
          _setColor(current->parent, black);
          _setColor(current->parent->parent, red);
          _rightRotate(current->parent->parent);
        }
      }
      if (current == root) {
        break;
      }
    }
    root->color = black;
  }

  void _leftRotate(node * rotatedParent) {
    node * rotatedChild = rotatedParent->right;
    rotatedParent->right = rotatedChild->left;
    if (rotatedChild->left != sentinel) {
      rotatedChild->left->parent = rotatedParent;
    }
    rotatedChild->parent = rotatedParent->parent;
    if (rotatedParent->parent == sentinel) {
      this->root = rotatedChild;
    } else if (rotatedParent == rotatedParent->parent->left) {
      rotatedParent->parent->left = rotatedChild;
    } else {
      rotatedParent->parent->right = rotatedChild;
    }
    rotatedChild->left = rotatedParent;
    rotatedParent->parent = rotatedChild;
  }

  void _rightRotate(node * rotatedParent) {
    node * rotatedChild = rotatedParent->left;
    rotatedParent->left = rotatedChild->right;
    if (rotatedChild->right != sentinel) {
      rotatedChild->right->parent = rotatedParent;
    }
    rotatedChild->parent = rotatedParent->parent;
    if (rotatedParent->parent == sentinel) {
      root = rotatedChild;
    } else if (rotatedParent == rotatedParent->parent->right) {
      rotatedParent->parent->right = rotatedChild;
    } else {
      rotatedParent->parent->left = rotatedChild;
    }
    rotatedChild->right = rotatedParent;
    rotatedParent->parent = rotatedChild;
  }

  bool _insert(const key_value_pair& data, node *hint){
      try {
        node *insertedNode = _nodeCreationHelper(data);
        node *savedParent = sentinel;
        node *savedRoot = hint;

        if (hint != root){
          savedRoot = root;
        }  
        while (!savedRoot->isSentinel)
        {
          savedParent = savedRoot;
          if (insertedNode->data.first == savedRoot->data.first)
          {
            lastInsertedNode = savedRoot;
            _nodeDeletionHelper(insertedNode);
            return false;
          }
          else if (comp(insertedNode->data.first, savedRoot->data.first))
            savedRoot = savedRoot->left;
          else
            savedRoot = savedRoot->right;
        }
        insertedNode->parent = savedParent;
        if (savedParent->isSentinel) {
          root = insertedNode;
        } else if (comp(insertedNode->data.first, savedParent->data.first)) {
          savedParent->left = insertedNode;
        } else {
          savedParent->right = insertedNode;
        }
        lastInsertedNode = insertedNode;
        ++countNode;
        if (insertedNode->parent->isSentinel) {
          insertedNode->color = black;
          return true;
        }
        if (insertedNode->parent->parent->isSentinel) {
          return true;
        }
        _recolorAndBalanceTreeAfterInsert(insertedNode);
        lastInsertedNode = insertedNode;
        return true;
      } catch (...){
        return false;
      }
  };
  /* 
   *  END INSERTION SECTION
   */

  /* 
   *  REMOVE SECTION
   */  
  void _recolorAndBalanceTreeAfterDelete(node * current){
    node * s;
    while (current != root && current->color == black) {
      if (current == current->parent->left) {
        s = current->parent->right;
        //D3 case
        if (_isRed(s)) {
          _setColor(s, black);
          _setColor(current->parent, red);
          _leftRotate(current->parent);
          s = current->parent->right;
        }
        //D1 Case
        if (_isBlack(s->left) && _isBlack(s->right)) {
          _setColor(s, red);
          current = current->parent;
        } else {
          if (_isBlack(s->right)) {
            _setColor(s->left, black);
            _setColor(s, black);
            _rightRotate(s);
            s = current->parent->right;
          }
          _setColor(s, current->parent->color);
          _setColor(current->parent, black);
          _setColor(s->right, black);
          _leftRotate(current->parent);
          current = root;
        }
      } else {
        s = current->parent->left;
        //D3
        if (_isRed(s)) {
          _setColor(s, black);
          _setColor(current->parent, red);
          _rightRotate(current->parent);
          s = current->parent->left;
        }
        //D1
        if (_isBlack(s->left) && _isBlack(s->right)) {
          _setColor(s, red);
          current = current->parent;
        } else {
          if (_isBlack(s->left)) {
            _setColor(s->right, black);
            _setColor(s,red);
            _leftRotate(s);
            s = current->parent->left;
          }
          _setColor(s, current->parent->color);
          _setColor(current->parent, black);
          _setColor(s->left, black);
          _rightRotate(current->parent);
          current = root;
        }
      }
    }
    _setColor(current, black);
  };

  /**
   * @brief reconnect relinkedNode to the deletedNode parent from the parent point of view and the deletedNode point of view
   * 
   * @param deletedNode node being replaced by relinkdeNode 
   * @param relinkedNode node that need to be reconnected to the parent of deletedNode
   */
  void relinkNode(node *deletedNode, node *relinkedNode) {
    if (deletedNode->parent->isSentinel) {
      root = relinkedNode;
    } else if (deletedNode == deletedNode->parent->left) {
      deletedNode->parent->left = relinkedNode;
    } else {
      deletedNode->parent->right = relinkedNode;
    }
    relinkedNode->parent = deletedNode->parent;
  }

  bool _deleteNode(node * current, key_value_pair data) {
    node *deletedNode = sentinel;
    node *replacingNode; 
    node *successorOfDeletedNode;
    deletedNode = _searchTree(current, data);
    if (deletedNode->isSentinel) {
      return 0;
    }
    successorOfDeletedNode = deletedNode;
    bool deletedNodeOriginalColor = deletedNode->color;
    if (deletedNode->left->isSentinel) {
      replacingNode = deletedNode->right;
      relinkNode(deletedNode, deletedNode->right);
    } else if (deletedNode->right->isSentinel) {
      replacingNode = deletedNode->left;
      relinkNode(deletedNode, deletedNode->left);
    } else {
      successorOfDeletedNode = getMin(deletedNode->right);
      deletedNodeOriginalColor = successorOfDeletedNode->color;
      replacingNode = successorOfDeletedNode->right;
      //is successor a child of the deletedNode?
      if (successorOfDeletedNode->parent == deletedNode) {
        replacingNode->parent = successorOfDeletedNode;
      } else {
        relinkNode(successorOfDeletedNode, successorOfDeletedNode->right);
        successorOfDeletedNode->right = deletedNode->right;
        successorOfDeletedNode->right->parent = successorOfDeletedNode;
      }
      relinkNode(deletedNode, successorOfDeletedNode);
      successorOfDeletedNode->left = deletedNode->left;
      successorOfDeletedNode->left->parent = successorOfDeletedNode;
      successorOfDeletedNode->color = deletedNode->color;
    }
    --countNode;
    _nodeDeletionHelper(deletedNode);
    if (deletedNodeOriginalColor == black) {
      _recolorAndBalanceTreeAfterDelete(replacingNode);
    }
    return 1;
  }

  node *_nodeCreationHelper(const key_value_pair& data){
    node *newNode;
    try {
          newNode = nodeAllocator.allocate(1);
          nodeAllocator.construct(newNode, node(data, NULL, sentinel, sentinel, red, false, NULL));
    } catch (...){
      throw std::bad_alloc();
    }
    return newNode;
  }

  void _nodeDeletionHelper(node *deletedNode){
      nodeAllocator.destroy(deletedNode);
      nodeAllocator.deallocate(deletedNode, 1);
  }

  void _deepCopyNodes(node * node) {
    if (node->isSentinel)
      return;
    {
      this->_insert(node->data, root);
      _deepCopyNodes(node->left);
      _deepCopyNodes(node->right);
    }
  }
  /* 
   *  END REMOVE SECTION
   */
public:

  RedBlackTree(const key_compare& comp = key_compare()) : comp(comp), countNode(0){
      sentinel = nodeAllocator.allocate(1);
      nodeAllocator.construct(sentinel, node());
      root = sentinel;
      lastInsertedNode = root;
  }
  RedBlackTree(const RedBlackTree &other){
      countNode = other.countNode;
      comp = Compare(other.comp);
      nodeAllocator = Allocator(other.nodeAllocator);
      sentinel = nodeAllocator.allocate(1);
      nodeAllocator.construct(sentinel, node());
      root = sentinel;
      lastInsertedNode = root;
      // If other tree is not empty then insert its content in instanciated tree
      if (other.getNodeCount()){
        _deepCopyNodes(other.root);
        lastInsertedNode = _searchTree(root, other.lastInsertedNode->data);
      }
  }
  RedBlackTree& operator=( const RedBlackTree& other ){
    if (this != &other){
        if (countNode != 0 || !other.getNodeCount()){
          clearTree();
        }
        clearTreeSentinel();
        comp = Compare(other.comp);
        nodeAllocator = Allocator(other.nodeAllocator);
        sentinel = nodeAllocator.allocate(1);
        nodeAllocator.construct(sentinel, node());
        root = sentinel;
        lastInsertedNode = root;
        // If other tree is not empty then insert its content in instanciated tree
        if (other.getNodeCount()){
          _deepCopyNodes(other.root);
          lastInsertedNode = _searchTree(root, other.lastInsertedNode->data);
        }
    }
    return *this;
  };

  ~RedBlackTree(){
    if (getNodeCount() > 0)
      clearTree();
    clearTreeSentinel();
  };

  size_type getNodeCount() const {
    return countNode;
  };

  key_compare getComp() const {
    return comp;
  }
  
  void clearTree(){
    _timber(root);
    root = sentinel;
  };

  void clearTreeSentinel(){
    _nodeDeletionHelper(sentinel);
  };

  node *searchTree(key_value_pair data) const {
    node *tmp = _searchTree(this->root, data);
    if (tmp->isSentinel)
      return sentinel;
    else
      return tmp;
  };

  node *getMin(node * current) const {
    while (!current->isSentinel && !current->left->isSentinel) {
      current = current->left;
    }
    return current;
  };

// Recursive function to find an inorder successor for the given key in a BST.
// Note that successor `succ` is passed by reference to the function
  node *getSuccessor(node *root, node *successor, const key_value_pair &key) const
  {
    // base case
    if (root->isSentinel)
      return successor;
    // if a node with the desired value is found, the successor is the minimum value
    // node in its right subtree (if any)
    if (root->data.first == key.first)
    {
      if (!root->right->isSentinel)
        return getMin(root->right);
    }
    // if the given key is less than the root node, recur for the left subtree
    else if (comp(key.first, root->data.first))
    {
      // update successor to the current node before recursing in the left subtree
      successor = root;
      return getSuccessor(root->left, successor, key);
    }
    // if the given key is more than the root node, recur for the right subtree
    else
      return getSuccessor(root->right, successor, key);
    return successor;
  }

  node *getLowerBound(const key_value_pair &data) const {
    node *nodeProcessed;
    if ((nodeProcessed = searchTree(data)) == sentinel)
      if (nodeProcessed == sentinel)
        nodeProcessed = getSuccessor(root, sentinel, data);
    return nodeProcessed;
  }

  node *getUpperBound(const key_value_pair &data) const {
    node *nodeProcessed = getSuccessor(root, sentinel, data);
    return nodeProcessed;
  }

  node *getRoot() const{
    return this->root;
  };

  node *getSentinel() const {
    return this->sentinel;
  };

  node *getLastInsertedNode() const {
    return this->lastInsertedNode;
  }

  bool insert(const key_value_pair &data) {
    return insert(data, root);
  };

  bool insert(const key_value_pair &data, node *hint) {
    bool hasBeenInserted = _insert(data, hint);
    if (hasBeenInserted)
      sentinel->lastUpdatedRoot = getRoot(); 
    return hasBeenInserted;
  };

  bool remove(const key_value_pair &data){
    int hasBeenDeleted =_deleteNode(this->root, data);
    if (hasBeenDeleted){
      if(countNode == 0)
        root = sentinel;
      sentinel->lastUpdatedRoot = getRoot();
    }
    return hasBeenDeleted;
  };

  void printTree(){
    if (root) {
      _printTree("", getRoot(), true);
    }
  };

  size_t maxSize() const{
    return nodeAllocator.max_size();
  }

  void treeSwap(RedBlackTree &other){
    baseSwap(root, other.root);
    baseSwap(sentinel, other.sentinel);
    baseSwap(countNode, other.countNode);
  }
};
}; //NAMESPACE

#endif