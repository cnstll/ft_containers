#define red 1
#define black 0
#include <string>

namespace ft {

/**
 * @brief Node structure used in RedBlackTree class that contains the parent of the node, right and left childs and the color stored in a boolean
 * 
 */
struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};
/**
 * @brief RedBlack binary search tree that balance itself based on "coloration" of the tree.
 * Balancing operations will happen on insertion and removal of nodes
 * 
 */
//template <typename Key, typename 
class RedBlackTree {

  Node *root;
  Node *sentinel;
  /** 
   *  @brief functions that handle tree traversal RoLR, LRoR, LRRo
   */ 
  void _preOrderTraversal(Node * node);
  void _inOrderTraversal(Node * node);
  void _postOrderTraversal(Node * node);
  /**
   * @brief helper function
   */
  bool _isRed(Node *current);
  bool _isBlack(Node *current);
  bool _hasLeftChild(Node *current);
  bool _hasRightChild(Node *current);
  void _setColor(Node *current, bool redOrBlack);
  bool _isLeftChild(Node *current, Node *parent);
  bool _isRightChild(Node *current, Node *parent);
  /** 
   *  @brief functions used to search or print the tree in a pre-order traversal manner
   */ 
  Node *_searchTree(Node * node, int key);
  void _printTree(const std::string& padding, Node* current, bool hasRight);
  /** 
   *  @brief functions that handle the rotations of node during rebalancing sequences
   */ 
  void _leftRotate(Node * rotatedParent);
  void _rightRotate(Node * rotatedParent);
  /** 
   *  @brief function that free and delete nodes
   */ 
  void _timber(Node *root);
  /** 
   *  @brief functions used in the insertion of a node in the tree and its rebalancing afterwards
   */  
  void _recolorAndBalanceTreeAfterInsert(Node * current);
  void _insert(int key);
  /** 
   *  @brief functions used in removal of a node from the tree and its rebalancing afterwards
   */  
  void _recolorAndBalanceTreeAfterDelete(Node * current);
  void relinkNode(Node *deletedNode, Node *relinkedNode);
  void _deleteNode(Node * current, int key);

  public:

    RedBlackTree();
    ~RedBlackTree();

    Node * searchTree(int k);
    
    Node *getMin(Node * node);
    Node *getMax(Node * node);
    Node *getSuccessor(Node * x);
    Node *getPredecessor(Node * x);

    Node * getRoot();
    int getRootData();

    void insert(int key);
    void remove(int data);
    void printTree();
};
}; //NAMESPACE