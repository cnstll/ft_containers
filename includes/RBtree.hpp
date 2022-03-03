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
};
  /*
  * HELPER FUNCTIONS
  */
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
  
  Node *_searchTree(Node * node,  key_value_pair data) {
    if (node == sentinel || data.first == node->data.first) {
      return node;
    }
    if (Compare(data.first, node->data.first)) {
      return _searchTree(node->left, data);
    }
    return _searchTree(node->right, data);
  }
  // ! should deallocate 1 by 1 or can it be done in bulk with getNodeCount() ? 
    void _timber(Node *root){
    //std::cout << "d" << std::endl;
    if (root == sentinel)
      return;
    {
        _timber(root->left);
        _timber(root->right);
        _nodeDeletionHelper(root, 1);
    }
  };

  void _printTree(const std::string& padding, Node* current, bool hasRight){ 
    if(current != sentinel)
    {
        std::cout << padding << (hasRight ? "|__" : "└──" );
        if (current->color == red)
          std::cout << "\033[31m" << current->data << "\033[0m"<< std::endl;
        else
          std::cout << current->data << std::endl;
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
    if (rotatedParent->parent == NULL) {
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
    if (rotatedParent->parent == NULL) {
      root = rotatedChild;
    } else if (rotatedParent == rotatedParent->parent->right) {
      rotatedParent->parent->right = rotatedChild;
    } else {
      rotatedParent->parent->left = rotatedChild;
    }
    rotatedChild->right = rotatedParent;
    rotatedParent->parent = rotatedChild;
  }

  void _insert(key_value_pair data){
      Node *insertedNode = _nodeCreationHelper(data);
      Node *savedParent = NULL;
      Node *savedRoot = this->root;

      while (savedRoot != sentinel) {
        savedParent = savedRoot;
        if (Compare(insertedNode->data.first, savedRoot->data.first)) {
          savedRoot = savedRoot->left;
        } else {
          savedRoot = savedRoot->right;
        }
      }
      insertedNode->parent = savedParent;
      if (savedParent == NULL) {
        root = insertedNode;
      } else if (Compare(insertedNode->data.first, savedParent->data.first)) {
        savedParent->left = insertedNode;
      } else {
        savedParent->right = insertedNode;
      }
      if (insertedNode->parent == NULL) {
        insertedNode->color = black;
        return;
      }
      if (insertedNode->parent->parent == NULL) {
        return;
      }

      _recolorAndBalanceTreeAfterInsert(insertedNode);
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

  void _deleteNode(Node * current, key_value_pair data) {
    Node *deletedNode = sentinel;
    Node *replacingNode; 
    Node *successorOfDeletedNode;
    deletedNode = _searchTree(current, data);
    if (deletedNode == sentinel) {
      std::cout << "Key not found in the tree" << std::endl;
      return;
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
    _nodeDeletionHelper(deletedNode);
    if (deletedNodeOriginalColor == black) {
      _recolorAndBalanceTreeAfterDelete(replacingNode);
    }
  }

  Node *_nodeCreationHelper(key_value_pair data){
    Node *newNode = nodeAllocator->allocate(1);
    newNode->color = red;
    newNode->data = data;
    newNode->left = sentinel;
    newNode->right = sentinel;
    newNode->parent = NULL;
    return newNode;
  }

  void _nodeDeletionHelper(Node *deletedNode, size_type numberOfNodeToDel){
      nodeAllocator.deallocate(deletedNode, numberOfNodeToDel);
  }
  /* 
   *  END REMOVE SECTION
   */
public:

  RedBlackTree(const key_compare& comp = key_compare()) : comp(comp), countNode(0){
    sentinel = nodeAllocator.allocate(1);
    sentinel->color = black;
    sentinel->left = NULL;
    sentinel->right = NULL;
    sentinel->parent = NULL;
    root = sentinel;
  }

  ~RedBlackTree(){};

  size_type getNodeCount(){
    return countNode;
  };

  key_compare getComp(){
    return comp;
  }
  
  void clearTree(){
    _timber(root);
  };

  void clearTreeSentinel(){
    _nodeDeletionHelper(sentinel, 1);
  };

  Node *searchTree(key_value_pair data) {
    return _searchTree(this->root, data);
  };

  Node *getMin(Node * node) {
    while (node->left != sentinel) {
      node = node->left;
    }
    return node;
  };

  Node *getMax(Node * node) {
    while (node->right != sentinel) {
      node = node->right;
    }
    return node;
  };

  Node *getSuccessor(Node * x) {
    if (x->right != sentinel) {
      return getMin(x->right);
    }
      Node * y = x->parent;
    while (y != sentinel && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  };

  Node *getPredecessor(Node * x) {
    if (x->left != sentinel) {
      return getMax(x->left);
    }
      Node * y = x->parent;
    while (y != sentinel && x == y->left) {
      x = y;
      y = y->parent;
    }
      return y;
  };

  Node *getRoot(){
    return this->root;
  };

  T getRootData(){
    return getRoot()->data;
  };

  void insert(key_value_pair data) {
    _insert(data);
  };

  void remove(key_value_pair data){
    _deleteNode(this->root, data);
  };

  void printTree(){
    if (root) {
      _printTree("", this->root, true);
    }
  };
};
}; //NAMESPACE

#endif