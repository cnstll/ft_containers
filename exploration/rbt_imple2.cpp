// Implementing Red-Black Tree in C++

#include <iostream>
#include <cstdlib>
#define red 1
#define black 0
using namespace std;

struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};

//typedef Node *Node *;

class RedBlackTree {
   private:
  Node *root;
  Node *sentinel;

  // Preorder
  void preOrderHelper(Node * node) {
    if (node != sentinel) {
      cout << node->data << " ";
      preOrderHelper(node->left);
      preOrderHelper(node->right);
    }
  }

  // Inorder
  void inOrderHelper(Node * node) {
    if (node != sentinel) {
      inOrderHelper(node->left);
      cout << node->data << " ";
      inOrderHelper(node->right);
    }
  }

  // Post order
  void postOrderHelper(Node * node) {
    if (node != sentinel) {
      postOrderHelper(node->left);
      postOrderHelper(node->right);
      cout << node->data << " ";
    }
  }

  Node * searchTreeHelper(Node * node, int key) {
    if (node == sentinel || key == node->data) {
      return node;
    }

    if (key < node->data) {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }

  // For balancing the tree after deletion
  void deleteFix(Node * x) {
    Node * s;
    while (x != root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          _leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            _rightRotate(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          _leftRotate(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          _rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            _leftRotate(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          _rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = 0;
  }

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

  void deleteNodeHelper(Node * current, int key) {
    Node *z = sentinel;
    Node *parentOfDeletedNode; 
    Node *nodeToBeDeleted;
    //search algo for the node to be deleted which will be "z"
    while (current != sentinel) {
      if (current->data == key) {
        z = current;
      }
      if (current->data <= key) {
        current = current->right;
      } else {
        current = current->left;
      }
    }

    if (z == sentinel) {
      cout << "Key not found in the tree" << endl;
      return;
    }

    nodeToBeDeleted = z;
    bool deletedNodeOriginalColor = z->color;
    if (z->left == sentinel) {
      parentOfDeletedNode = z->right;
      relinkNode(z, z->right);
    } else if (z->right == sentinel) {
      parentOfDeletedNode = z->left;
      relinkNode(z, z->left);
    } else {
      nodeToBeDeleted = getMin(z->right);
      deletedNodeOriginalColor = nodeToBeDeleted->color;
      parentOfDeletedNode = nodeToBeDeleted->right;
      if (nodeToBeDeleted->parent == z) {
        parentOfDeletedNode->parent = nodeToBeDeleted;
      } else {
        relinkNode(nodeToBeDeleted, nodeToBeDeleted->right);
        nodeToBeDeleted->right = z->right;
        nodeToBeDeleted->right->parent = nodeToBeDeleted;
      }

      relinkNode(z, nodeToBeDeleted);
      nodeToBeDeleted->left = z->left;
      nodeToBeDeleted->left->parent = nodeToBeDeleted;
      nodeToBeDeleted->color = z->color;
    }
    delete z;
    if (y_original_color == 0) {
      deleteFix(parentOfDeletedNode);
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

  // For balancing the tree after insertion
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
    root->color = 0;
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

  void _timber(Node *root){

      //std::cout << "d" << std::endl;
      if (root == sentinel)
        return;
      {
          _timber(root->left);
          _timber(root->right);
          delete root;
      }
  };

  public:

  RedBlackTree() {
    sentinel = new Node;
    sentinel->color = 0;
    sentinel->left = NULL;
    sentinel->right = NULL;
    root = sentinel;
  }

  ~RedBlackTree(){
    _timber(root);
    delete sentinel;
  }

  void preorder() {
    preOrderHelper(this->root);
  }

  void inorder() {
    inOrderHelper(this->root);
  }

  void postorder() {
    postOrderHelper(this->root);
  }

  Node * searchTree(int k) {
    return searchTreeHelper(this->root, k);
  }

// Node *getMin(Node * node) {
  //   while (node->left != sentinel) {
  //     node = node->left;
  //   }
  //   return node;
  // }
  //
  // Node *getMax(Node * node) {
  //   while (node->right != sentinel) {
  //     node = node->right;
  //   }
  //   return node;
  // }
  //
  // Node *getSuccessor(Node * x) {
  //   if (x->right != sentinel) {
  //     return getMin(x->right);
  //   }
  //
  //   Node * y = x->parent;
  //   while (y != sentinel && x == y->right) {
  //     x = y;
  //     y = y->parent;
  //   }
  //   return y;
  // }
  //
  // Node *getPredecessor(Node * x) {
  //   if (x->left != sentinel) {
  //     return getMax(x->left);
  //   }
  //
  //   Node * y = x->parent;
  //   while (y != sentinel && x == y->left) {
  //     x = y;
  //     y = y->parent;
  //   }
  //
  //   return y;
//  // }

  void insert(int key) {
    Node *insertedNode = new Node;
    insertedNode->parent = NULL;
    insertedNode->data = key;
    insertedNode->left = sentinel;
    insertedNode->right = sentinel;
    insertedNode->color = 1;
    Node *savedParent = NULL;
    Node *savedRoot = this->root;

    while (savedRoot != sentinel) {
      savedParent = savedRoot;
      if (insertedNode->data < savedRoot->data) {
        savedRoot = savedRoot->left;
      } else {
        savedRoot = savedRoot->right;
      }
    }
    insertedNode->parent = savedParent;
    if (savedParent == NULL) {
      root = insertedNode;
    } else if (insertedNode->data < savedParent->data) {
      savedParent->left = insertedNode;
    } else {
      savedParent->right = insertedNode;
    }
    if (insertedNode->parent == NULL) {
      insertedNode->color = 0;
      return;
    }
    if (insertedNode->parent->parent == NULL) {
      return;
    }

    _recolorAndBalanceTreeAfterInsert(insertedNode);
  }

  Node * getRoot() {
    return this->root;
  }

  void remove(int data) {
    deleteNodeHelper(this->root, data);
  }
  void _printBinaryTree(const std::string& padding, Node* current, bool hasRight)
    { 
      if( current != NULL && current != sentinel)
      {
          std::cout << padding << (hasRight ? "|__" : "└──" );
          // print the value of the node
          if (current->color == 1)
            std::cout << "\033[31m" << current->data << "\033[0m"<< std::endl;
          else
            std::cout << current->data << std::endl;
          _printBinaryTree(padding + (hasRight ? "│   " : "    "), current->left, (current->right != sentinel));
          _printBinaryTree(padding + (hasRight ? "│   " : "    "), current->right, false);
      }
  };
  void printTree() {
    if (root) {
      _printBinaryTree("", this->root, true);
    }
  }
};
int genRandomNumber(){

  static bool done = false;

	if (done == false){
  	std::srand(time(NULL));
		done = true;
	}
  int randomNum = std::rand() % 1000;
  return randomNum;
}
#include <vector>
int main() {
  RedBlackTree bst;

  std::vector<int> v;
  int i = 0;
  int max_size = 54;
  while(i < max_size){
    v.push_back(genRandomNumber());
    i++;
  }
  RedBlackTree tree;
  i = 0;
  while (i < max_size){
    //std::cout << v[i] << " inserted.\n";
    tree.insert(v[i++]);
  }
  tree.printTree();

  bst.printTree();
//  cout << endl
//     << "After deleting" << endl;
//  bst.remove(40);
//  bst.printTree();
}