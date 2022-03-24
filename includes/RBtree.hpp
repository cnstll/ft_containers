#ifndef RBTREE_HPP
#define RBTREE_HPP
#define red 1
#define black 0
#include "pair.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace ft {
  /**
 * @brief Node structure used in RedBlackTree class that contains the parent of the node, right and left childs and the color stored in a boolean
 * 
 */
template <class T>
struct mapNode {
  T data;
  mapNode<T> *parent;
  mapNode<T> *left;
  mapNode<T> *right;
  bool color; // change from int to bool
  bool isSentinel;

  mapNode() : data(), parent(NULL), left(NULL), right(NULL), color(black), isSentinel(true){}
  mapNode(const T& d, mapNode<T> *p, mapNode<T> *l, mapNode<T>* r, bool c, bool s) : data(d), parent(p), left(l), right(r), color(c), isSentinel(s){}
  mapNode(const mapNode& other) : data(other.data), parent(other.parent), left(other.left), right(other.right), color(other.color), isSentinel(other.isSentinel){}
  ~mapNode(){}
  mapNode &operator=(const mapNode& other){
    if (this != &other){
      data = other.data;
      parent = other.parent;
      left = other.left;
      right = other.right;
      color = other.color;
      isSentinel = other.isSentinel;
    }
    return *this;
  }

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

  mapNode<T> *getMin() {
    mapNode<T> *tmp = this;
    while (tmp->left != NULL && !tmp->left->isSentinel)
      tmp = tmp->left;
    return tmp;
  };
  // friend bool operator==(const mapNode<T>& lhs, const mapNode<T>& rhs) { return lhs.data == rhs.data; };

};

template <
    class T,
    class Compare,
    class Allocator
> class RedBlackTree {
  
  typedef T key_value_pair;
  typedef mapNode<key_value_pair> Node;
  typedef Compare key_compare;
  typedef std::size_t size_type;
  typedef Allocator tree_allocator_type;
  typedef typename tree_allocator_type::template rebind<Node>::other node_allocator_type;

  Node *root;
  Node *sentinel;
  Node *lastInsertedNode;
  node_allocator_type nodeAllocator;
  key_compare comp;
  std::size_t countNode;

  void _preOrderTraversal(Node * node) {
    if (node != sentinel) {
      std::cout << node->data.first << " ";
      _preOrderTraversal(node->left);
      _preOrderTraversal(node->right);
    }
  }

  void _inOrderTraversal(Node * node) {
    if (node != sentinel) {
      _inOrderTraversal(node->left);
      std::cout << node->data << " ";
      _inOrderTraversal(node->right);
    }
  }

  void _postOrderTraversal(Node * node) {
    if (node != sentinel) {
      _postOrderTraversal(node->left);
      _postOrderTraversal(node->right);
      std::cout << node->data << " ";
    }
  }

  bool _isRed(Node *current){
    return (current->color == red);
  };

  bool _isBlack(Node *current){
    return (current->color == black);
  };

  bool _hasLeftChild(Node *current){
    return (current->left != sentinel);
  };

  bool _hasRightChild(Node *current){
    return (current->right != sentinel);
  };

  void _setColor(Node *current, bool redOrBlack){
      current->color = redOrBlack;
  };

  bool _isLeftChild(Node *current, Node *parent){
    return (current == parent->left);
  };

  bool _isRightChild(Node *current, Node *parent){
    return (current == parent->right);
  };

  /**
   * @brief search tree with in order traversal method
   * 
   * @param node active node
   * @param data pair of key and value. The key is searched in the tree
   * @return address of the node found 
   */
  
  Node *_searchTree(Node * node,  key_value_pair data) const {
    if (node == sentinel || data.first == node->data.first) {
      return node;
    }
    if (comp(data.first, node->data.first)) {
      return _searchTree(node->left, data);
    }
    return _searchTree(node->right, data);
  }
  // ! should deallocate 1 by 1 or can it be done in bulk with getNodeCount() ? 
    void _timber(Node *root){
    if (root == sentinel)
      return;
    {
        _timber(root->left);
        _timber(root->right);
        //std::cout << "deleted key: " << root->data.first << std::endl;
        --countNode;
        _nodeDeletionHelper(root);
    }
  };

  void _printTree(const std::string& padding, Node* current, bool hasRight){ 
    if(current != sentinel)
    {
      std::cout << padding << (hasRight ? "|__" : "└──" );
      if (current->color == red)
        std::cout << current->data.first << "," << current->data.second << std::endl;
      else
        std::cout << current->data.first << "." << current->data.second << std::endl;
      _printTree(padding + (hasRight ? "│   " : "    "), current->left, (current->right != sentinel));
      _printTree(padding + (hasRight ? "│   " : "    "), current->right, false);
    }
  };

  /* 
   *  INSERTION SECTION
   */
  void _recolorAndBalanceTreeAfterInsert(Node * current) {
    Node *u;
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

  void _leftRotate(Node * rotatedParent) {
    Node * rotatedChild = rotatedParent->right;
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

  void _rightRotate(Node * rotatedParent) {
    Node * rotatedChild = rotatedParent->left;
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

  bool _insert(const key_value_pair& data){
      Node *insertedNode = _nodeCreationHelper(data);
      Node *savedParent = sentinel;
      Node *savedRoot = this->root;

      while (savedRoot != sentinel) {
        savedParent = savedRoot;
        if (insertedNode->data.first == savedRoot->data.first){
          lastInsertedNode = savedRoot;
          _nodeDeletionHelper(insertedNode);
          return false;
        }
        else if (comp(insertedNode->data.first, savedRoot->data.first)) {
          savedRoot = savedRoot->left;
        } else {
          savedRoot = savedRoot->right;
        }
      }
      insertedNode->parent = savedParent;
      if (savedParent == sentinel) {
        root = insertedNode;
      } else if (comp(insertedNode->data.first, savedParent->data.first)) {
        savedParent->left = insertedNode;
      } else {
        savedParent->right = insertedNode;
      }
      lastInsertedNode = insertedNode;
      ++countNode;
      if (insertedNode->parent == sentinel) {
        insertedNode->color = black;
        return true;
      }
      if (insertedNode->parent->parent == sentinel) {
        return true;
      }
      _recolorAndBalanceTreeAfterInsert(insertedNode);
      lastInsertedNode = insertedNode;
      return true;
  };
  /* 
   *  END INSERTION SECTION
   */

  /* 
   *  REMOVE SECTION
   */  
  void _recolorAndBalanceTreeAfterDelete(Node * current){
    Node * s;
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
  void relinkNode(Node *deletedNode, Node *relinkedNode) {
    if (deletedNode->parent == NULL) {
      root = relinkedNode;
    } else if (deletedNode == deletedNode->parent->left) {
      deletedNode->parent->left = relinkedNode;
    } else {
      deletedNode->parent->right = relinkedNode;
    }
    relinkedNode->parent = deletedNode->parent;
  }

  bool _deleteNode(Node * current, key_value_pair data) {
    Node *deletedNode = sentinel;
    Node *replacingNode; 
    Node *successorOfDeletedNode;
    deletedNode = _searchTree(current, data);
    if (deletedNode == sentinel) {
      return 0;
    }
    successorOfDeletedNode = deletedNode;
    bool deletedNodeOriginalColor = deletedNode->color;
    if (deletedNode->left == sentinel) {
      replacingNode = deletedNode->right;
      relinkNode(deletedNode, deletedNode->right);
    } else if (deletedNode->right == sentinel) {
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

  Node *_nodeCreationHelper(const key_value_pair& data){
    Node *newNode = nodeAllocator.allocate(1);
    nodeAllocator.construct(newNode, Node(data, NULL, sentinel, sentinel, red, false));
    return newNode;
  }

  void _nodeDeletionHelper(Node *deletedNode){
      nodeAllocator.destroy(deletedNode);
      nodeAllocator.deallocate(deletedNode, 1);
  }

  void _deepCopyNodes(Node * node) {
    if (node->isSentinel)
      return;
    {
      this->_insert(node->data);
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
    nodeAllocator.construct(sentinel, Node());
    root = sentinel;
    lastInsertedNode = root;
  }
  RedBlackTree(const RedBlackTree &other){
    countNode = other.countNode;
    comp = Compare(other.comp);
    nodeAllocator = Allocator(other.nodeAllocator);
    sentinel = nodeAllocator.allocate(1);
    nodeAllocator.construct(sentinel, Node());
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
      // 1. this is empty, other is empty >  clear tree and sentinel and swap other element
      // 2. this is empty, other is not empty >  clear tree and sentinel and swap other element and insert elements
      // 3. this is not empty, other is not empty >  clear tree and sentinel and swap other element and insert elements
      // 4. this is not empty, other is empty >  clear tree and sentinel and swap other element
      if (countNode != 0 || !other.getNodeCount()){
        clearTree();
        clearTreeSentinel();
      }
      comp = Compare(other.comp);
      nodeAllocator = Allocator(other.nodeAllocator);
      sentinel = nodeAllocator.allocate(1);
      nodeAllocator.construct(sentinel, Node());
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
  };

  void clearTreeSentinel(){
    _nodeDeletionHelper(sentinel);
  };

  Node *searchTree(key_value_pair data) const {
    Node *tmp = _searchTree(this->root, data);
    if (tmp == sentinel)
      return sentinel;
    else
      return tmp;
  };

  key_value_pair searchTreeWithBoundChecking(key_value_pair data) const {
      Node *searchResult = _searchTree(this->root, data);
      if (searchResult == getSentinel())
        throw std::out_of_range("OUT OF RANGE");
      return searchResult->data;
  }

  Node *getMin(Node * current) {
    while (current->left != sentinel) {
      current = current->left;
    }
    return current;
  };

  Node *getMax(Node * current) {
    while (current->right != sentinel) {
      current = current->right;
    }
    return current;
  };

  Node *getSuccessor(const key_value_pair &data) {
    Node *nodeProcessed;
    if ((nodeProcessed = _searchTree(root, data)) == sentinel)
      return sentinel;
    if (nodeProcessed->right != sentinel) {
      return getMin(nodeProcessed->right);
    }
    Node * searchedParent = nodeProcessed->parent;
    while (searchedParent != sentinel && nodeProcessed == searchedParent->right) {
      nodeProcessed = searchedParent;
      searchedParent = searchedParent->parent;
    }
    return searchedParent;
  };

  Node *getPredecessor(const key_value_pair &data){
    Node *nodeProcessed;
    if ((nodeProcessed = _searchTree(root, data)) == sentinel)
      return sentinel;
    if (nodeProcessed->left != sentinel) {
      return getMax(nodeProcessed->left);
    }
    Node * searchedParent = nodeProcessed->parent;
    while (searchedParent != sentinel && nodeProcessed == searchedParent->left) {
      nodeProcessed = searchedParent;
      searchedParent = searchedParent->parent;
    }
    return searchedParent;
  };

  Node *getLowerBound(const key_value_pair &data){
    Node *nodeProcessed;
    if ((nodeProcessed = _searchTree(root, data)) == sentinel)
      return sentinel;
    if (!comp(nodeProcessed->data.first, nodeProcessed->data.first)){
      return nodeProcessed;
    } else {
      std::cout << "ELSE IN getLowerBound\n";
      return nodeProcessed;
    }
  }

  Node *getRoot(){
    return this->root;
  };

  Node *getSentinel() const {
    return this->sentinel;
  };

  Node *getLastInsertedNode(){
    return this->lastInsertedNode;
  }

  T getData(Node *current){
    return current->data;
  };

  bool insert(const key_value_pair &data) {
    return _insert(data);
  };

  size_type remove(const key_value_pair &data){
    return _deleteNode(this->root, data);
  };

  void printTree(){
    if (root) {
      _printTree("", getRoot(), true);
    }
  };

  Node *_duplicateNode(Node *srcNode){
    Node *dup = nodeAllocator->allocate(1);
    dup->color = srcNode->color;
    dup->data = srcNode->data;
    dup->left = srcNode->left;
    dup->right = srcNode->right;
    dup->parent = srcNode->parent;
    return dup;
  }
  //template <class _T, class _Compare, class _Allocator>
  //friend void copyTree(RedBlackTree<_T, _Compare, _Allocator> *destination, RedBlackTree<_T, _Compare, _Allocator> *source);
  
  //void *_copyTreeHelper(Node *destNode, Node *srcNode){
  //  Node *tmp;
  //  if (destNode != sentinel)
  //    destNode = _duplicateNode(srcNode);
  //    tmp = srcNode;
  //  else
  //    return;
  //  if (srcNode->left != sentinel){
  //    destNode->left = _duplicateNode(srcNode->left);
  //  }
  //  if (srcNode->right != sentinel){
  //    destNode->right = _duplicateNode(srcNode->right);
  //  }
  //}
};
//template <class T, class Compare, class Allocator>
//void copyTree(RedBlackTree<T, Compare, Allocator> *destination, RedBlackTree<T, Compare, Allocator> *source){
//  Node<T> *rootSource = source->getRoot();
//  Node<T> *rootDestination = destination->getRoot();
//  _
//}
}; //NAMESPACE

#endif