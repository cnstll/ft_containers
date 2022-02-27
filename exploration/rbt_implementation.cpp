// Implementing Red-Black Tree in C++

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#define red 1
#define black 0

struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  bool color;
};

class RedBlackTree {
   private:
  Node * root;
  Node * sentinel;

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
//  void deleteFix(Node * x) {
//    Node * s;
//    while (x != root && x->color == 0) {
//      if (x == x->parent->left) {
//        s = x->parent->right;
//        if (s->color == 1) {
//          s->color = 0;
//          x->parent->color = 1;
//          leftRotate(x->parent);
//          s = x->parent->right;
//        }
//
//        if (s->left->color == 0 && s->right->color == 0) {
//          s->color = 1;
//          x = x->parent;
//        } else {
//          if (s->right->color == 0) {
//            s->left->color = 0;
//            s->color = 1;
//            rightRotate(s);
//            s = x->parent->right;
//          }
//
//          s->color = x->parent->color;
//          x->parent->color = 0;
//          s->right->color = 0;
//          leftRotate(x->parent);
//          x = root;
//        }
//      } else {
//        s = x->parent->left;
//        if (s->color == 1) {
//          s->color = 0;
//          x->parent->color = 1;
//          rightRotate(x->parent);
//          s = x->parent->left;
//        }
//
//        if (s->right->color == 0 && s->right->color == 0) {
//          s->color = 1;
//          x = x->parent;
//        } else {
//          if (s->left->color == 0) {
//            s->right->color = 0;
//            s->color = 1;
//            leftRotate(s);
//            s = x->parent->left;
//          }
//
//          s->color = x->parent->color;
//          x->parent->color = 0;
//          s->left->color = 0;
//          rightRotate(x->parent);
//          x = root;
//        }
//      }
//    }
//    x->color = 0;
//  }
//
//  void rbTransplant(Node * u, Node * v) {
//    if (u->parent == NULL) {
//      root = v;
//    } else if (u == u->parent->left) {
//      u->parent->left = v;
//    } else {
//      u->parent->right = v;
//    }
//    v->parent = u->parent;
//  }

//  void deleteNodeHelper(Node * node, int key) {
//    Node * z = sentinel;
//    Node * x, y;
//    while (node != sentinel) {
//      if (node->data == key) {
//        z = node;
//      }
//
//      if (node->data <= key) {
//        node = node->right;
//      } else {
//        node = node->left;
//      }
//    }
//
//    if (z == sentinel) {
//      cout << "Key not found in the tree" << endl;
//      return;
//    }
//    y = z;
//    int y_original_color = y->color;
//    if (z->left == sentinel) {
//      x = z->right;
//      rbTransplant(z, z->right);
//    } else if (z->right == sentinel) {
//      x = z->left;
//      rbTransplant(z, z->left);
//    } else {
//      y = minimum(z->right);
//      y_original_color = y->color;
//      x = y->right;
//      if (y->parent == z) {
//        x->parent = y;
//      } else {
//        rbTransplant(y, y->right);
//        y->right = z->right;
//        y->right->parent = y;
//      }
//
//      rbTransplant(z, y);
//      y->left = z->left;
//      y->left->parent = y;
//      y->color = z->color;
//    }
//    delete z;
//    if (y_original_color == 0) {
//      deleteFix(x);
//    }
//  }

    bool _isLeftChild(Node *current, Node *parent){
      return (current == parent->left);
    };

    bool _isRightChild(Node *current, Node *parent){
      return (current == parent->right);
    };

    bool _isRoot(Node *current){
      return (current->parent == sentinel);
    };

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
  void leftRotate(Node * rotatedParent) {
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

  void rightRotate(Node * rotatedParent) {
    Node * rotatedChild = rotatedParent->left;
    rotatedParent->left = rotatedChild->right;
    if (rotatedChild->right != sentinel) {
      rotatedChild->right->parent = rotatedParent;
    }
    rotatedChild->parent = rotatedParent->parent;
    if (rotatedParent->parent == NULL) {
      this->root = rotatedChild;
    } else if (rotatedParent == rotatedParent->parent->right) {
      rotatedParent->parent->right = rotatedChild;
    } else {
      rotatedParent->parent->left = rotatedChild;
    }
    rotatedChild->right = rotatedParent;
    rotatedParent->parent = rotatedChild;
  }
  // For balancing the tree after insertion
  void insertFix(Node * current) {
    Node * parentNode = current->parent;
    Node * u;
    while (_isRed(parentNode)) {
      if (_isRightChild(parentNode, parentNode->parent)) {
        u = parentNode->parent->left;
        if (_isRed(u)) {
          u->color = 0;
          parentNode->color = 0;
          parentNode->parent->color = 1;
          current = parentNode->parent;
        } else {
          if (_isLeftChild(current, parentNode)) {
            current = parentNode;
            rightRotate(current);
          }
          parentNode->color = 0;
          parentNode->parent->color = 1;
          leftRotate(parentNode->parent);
        }
      } else {
        u = parentNode->parent->right;

        if (_isRed(u)) {
          u->color = 0;
          parentNode->color = 0;
          parentNode->parent->color = 1;
          current = parentNode->parent;
        } else {
          if (_isRightChild(current, parentNode)) {
            current = parentNode;
            leftRotate(current);
          }
          parentNode->color = 0;
          parentNode->parent->color = 1;
          rightRotate(parentNode->parent);
        }
      }
      if (current == root) {
        break;
      }
    }
    root->color = 0;
  }
  void _printBinaryTree(const std::string& padding, Node* current, bool hasRight){ 
      if( current != NULL && current != sentinel)
      {
          std::cout << padding << (hasRight ? "|__" : "└──" );
          // print the value of the node
          if (current->color == red)
            std::cout << "\033[31m" << current->data << "\033[0m"<< std::endl;
          else
            std::cout << current->data << std::endl;
          _printBinaryTree(padding + (hasRight ? "│   " : "    "), current->left, (current->right != sentinel));
          _printBinaryTree(padding + (hasRight ? "│   " : "    "), current->right, false);
      }
  };

  void printHelper(Node * root, string indent, bool last) {
    if (root != sentinel) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }

      string sColor = root->color ? "RED" : "BLACK";
      cout << root->data << "(" << sColor << ")" << endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
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

  Node * minimum(Node * node) {
    while (node->left != sentinel) {
      node = node->left;
    }
    return node;
  }

  Node * maximum(Node * node) {
    while (node->right != sentinel) {
      node = node->right;
    }
    return node;
  }

  Node * successor(Node * x) {
    if (x->right != sentinel) {
      return minimum(x->right);
    }

    Node * y = x->parent;
    while (y != sentinel && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  Node * predecessor(Node * x) {
    if (x->left != sentinel) {
      return maximum(x->left);
    }

    Node * y = x->parent;
    while (y != sentinel && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }



  // Inserting a node
  void insert(int key) {
    Node * node = new Node;
    node->parent = NULL;
    node->data = key;
    node->left = sentinel;
    node->right = sentinel;
    node->color = 1;

    Node * parent = NULL;
    Node * rootCopy = this->root;

    while (rootCopy != sentinel) {
      parent = rootCopy;
      if (node->data < rootCopy->data) {
        rootCopy = rootCopy->left;
      } else {
        rootCopy = rootCopy->right;
      }
    }

    node->parent = parent;
    if (parent == NULL) {
      root = node;
    } else if (node->data < parent->data) {
      parent->left = node;
    } else {
      parent->right = node;
    }

    if (node->parent == NULL) {
      node->color = 0;
      return;
    }

    if (node->parent->parent == NULL) {
      return;
    }

    insertFix(node);
  }

  Node * getRoot() {
    return this->root;
  }

//  void deleteNode(int data) {
//    deleteNodeHelper(this->root, data);
//  }

  void printTree() {
    if (root) {
      _printBinaryTree("", root, true);
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

int main() {

  RedBlackTree bst;
  std::vector<int> v;
  int i = 0;
  int max_size = 25;
  while(i < max_size){
    v.push_back(genRandomNumber());
    i++;
  }
  RedBlackTree tree;
  i = 0;
  while (i < max_size){
    //std::cout << v[i] << " inserted.\n";
    bst.insert(v[i++]);
    bst.printTree();
  }
  bst.printTree();
  cout << endl
     << "After deleting" << endl;
  //bst.deleteNode(40);
  bst.printTree();
}