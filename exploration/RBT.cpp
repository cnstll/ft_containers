#include <iostream>
#include <vector>
#define black true
#define red   false

class binarySearchTree {

    struct node {
      int data;
      node *parentNode;
      node *leftChild;
      node *rightChild;
      bool color;
    };

    node *root;

    node *_createNewNode(int data, node *parent){
      node *createdNode = new node;
      createdNode->data = data;
      createdNode->parentNode = parent;
      createdNode->leftChild = NULL;
      createdNode->rightChild = NULL;
      return createdNode;
    };

    void _timber(node *root){

      //std::cout << "d" << std::endl;
      if (!root)
        return;
      {
          _timber(root->leftChild);
          _timber(root->rightChild);
          delete root;
      }
    };

    bool _isLeftChild(node *current, node *parent){
      return (current == parent->leftChild);
    };

    bool _isRightChild(node *current, node *parent){
      return (current == parent->rightChild);
    };

    bool _isRoot(node *current){
      return (current->parentNode == NULL);
    };

    bool _isRed(node *current){
      return (current->color == red);
    };

    bool _isBlack(node *current){
      return (current->color == red);
    };

    bool _hasLeftChild(node *current){
      return (current->leftChild != NULL);
    };

    bool _hasRightChild(node *current){
      return (current->rightChild != NULL);
    };

    void _setColor(node *current, bool redOrBlack){
        current->color = redOrBlack;
    };
    
    void _leftRotate(node *rotatedParent){
      node *rotatedChild = rotatedParent->rightChild;
      rotatedParent->rightChild = rotatedChild->leftChild ? rotatedChild->leftChild : NULL;
      if (_hasLeftChild(rotatedChild)){
        rotatedChild->leftChild->parentNode = rotatedParent;
      }
      if (_isRoot(rotatedParent)){
        root = rotatedChild;
      } else if (_isLeftChild(rotatedParent, rotatedParent->parentNode)){
        rotatedParent->parentNode->leftChild = rotatedChild;
      } else {
        rotatedParent->parentNode->rightChild = rotatedChild;
      }
      rotatedChild->leftChild = rotatedParent;
      rotatedParent->parentNode = rotatedChild;
    };

    void _rightRotate(node *rotatedParent){
      node *rotatedChild = rotatedParent->leftChild;
      rotatedParent->leftChild = rotatedChild->rightChild ? rotatedChild->rightChild : NULL;
      if (_hasRightChild(rotatedChild)){
        rotatedChild->rightChild->parentNode = rotatedParent;
      }
      rotatedChild->parentNode = rotatedParent->parentNode;
      if (_isRoot(rotatedParent)){
        root = rotatedChild;
      } else if (_isRightChild(rotatedParent, rotatedParent->parentNode)){
        rotatedParent->parentNode->rightChild = rotatedChild;
      } else {
        rotatedParent->parentNode->leftChild = rotatedChild;
      }
      rotatedChild->rightChild = rotatedParent;
      rotatedParent->parentNode = rotatedChild;
    };

    void _balanceTreeAfterInsertion(node *current){
      while (!_isRoot(current) && _isRed(current->parentNode)){
        node *parent = current->parentNode;
        node *grandpa = current->parentNode->parentNode;
        node *u;
        if (_isRightChild(parent, grandpa)){
          if (_hasLeftChild(grandpa) && _isRed(parent->leftChild)){
            _setColor(grandpa->leftChild, black);
            _setColor(parent, black);
            _setColor(grandpa, red);
            current = grandpa;
          } else {
              if (_isLeftChild(current, parent)){
              current = parent;
              _rightRotate(current);
            }
            _setColor(parent, black);
            _setColor(grandpa, red);
            _leftRotate(grandpa);
          }
        } else {
          if (_hasRightChild(grandpa) && _isRed(grandpa->rightChild)){
            _setColor(grandpa->rightChild, black);
            _setColor(parent, black);
            _setColor(grandpa, red);
            current = grandpa;
          } else {
            if (_isRightChild(current, parent)){
              current = parent;
              _leftRotate(current);
            }
            _setColor(parent, black);
            _setColor(grandpa, red);
            _rightRotate(grandpa);
          }
        }                    
        if (current == root){
          break;
        }
      } 
      root->color = black;
    };
    
    void _insert(int dataToInsert){
      node *current = _createNewNode(dataToInsert, NULL);
      node *rootCopy = root;
      node *parent = NULL;
      while(rootCopy){
        parent = rootCopy;
        if (current->data < rootCopy->data)
          rootCopy = rootCopy->leftChild;
        else
          rootCopy = rootCopy->rightChild;
      }
      current->parentNode = parent;
      if (parent == NULL){
        root = current;
      } else if (parent->data > current->data){
        parent->leftChild = current;
      } else {
        parent->rightChild = current;
      }
      parent == NULL ? current->color = black : current->color = red;
      _balanceTreeAfterInsertion(current);
    };

    node *_remove(node *toRemove){
    
      node *tmp;
      if (!toRemove)
        return NULL;
      if (toRemove->leftChild == NULL){
        tmp = toRemove->rightChild;
        _subTreeShift(toRemove, tmp);
      }
      else if (toRemove->rightChild == NULL){
        tmp = toRemove->leftChild;
        _subTreeShift(toRemove, tmp);
      }
      else {
        tmp = _getSuccessor(toRemove);
        //std::cout << tmp->data << " is successor.\n";
        if (tmp->parentNode != toRemove){
          _subTreeShift(tmp, tmp->rightChild);
          tmp->rightChild = toRemove->rightChild;
          tmp->rightChild->parentNode = tmp;
        }
        //std::cout << "looking for successor\n";
        _subTreeShift(toRemove, tmp);
        tmp->leftChild = toRemove->leftChild;
        tmp->leftChild->parentNode = tmp;
      }
      delete toRemove;
      return root;
    };

    void _subTreeShift(node *removed, node *replacing){
    
      if (removed->parentNode == NULL){
        root = replacing; 
      }
      else if (removed == removed->parentNode->leftChild)
        removed->parentNode->leftChild = replacing;
      else
        removed->parentNode->rightChild = replacing;
      if (replacing != NULL)
        replacing->parentNode = removed->parentNode;
    }


    node *_getSuccessor(node *current){
      if (current->rightChild != NULL){
        return _getMin(current->rightChild);
      }
      node *parent = current->parentNode;
      while(parent != NULL && current == parent->rightChild){
        current = parent;
        parent = parent->parentNode;
      }
      return current;
    };

    node *_getPredecessor(node *current){
      while (current->leftChild != NULL){
        return _getMax(current->leftChild);
      }
      node *parent = current->parentNode;
      while(parent != NULL && current == parent->leftChild){
        current = parent;
        parent = parent->parentNode;
      }
      return current;
    };

    node *_getMin(node *root){
      node *minNode = root;
      while (root && minNode->leftChild){
        minNode = minNode->leftChild;
      }
      return minNode;
    };

    node *_getMax(node *root){
      node *maxNode = root;
      while (root && maxNode->rightChild){
        maxNode = maxNode->rightChild;
      }
      return maxNode;
    };

    std::size_t _getNodeLevel(node *current){
      std::size_t level = 0;
      node *tmp = current;
      while (tmp->parentNode){
        tmp = tmp->parentNode;
        ++level;
      }
      return level;
    }

    node *_search(node *current, int dataToFind){
      if (current == NULL)
        return NULL;
      else if (current->data < dataToFind)
        return _search(current->rightChild, dataToFind);
      else if (current->data > dataToFind)
        return _search(current->leftChild, dataToFind);
      else
        return current;
    };

    // void _printingTreeImage(node *current){
    //  if (current){
    //    if (current->parentNode && current->parentNode->rightChild == current){
    //      img.insert(_getNodeLevel(current) + 1, _size(current) * 4, current->data);
    //      img.insert(_getNodeLevel(current) + 2, _size(current) * 4, "/ \\");
    //    }
    //    else if (current->parentNode && current->parentNode->leftChild == current){
    //      img.insert(_getNodeLevel(current), _size(current), current->data);
    //      img.insert(_getNodeLevel(current) + 1, _size(current), "/ \\");
    //    }
    //    else {
    //      img.insert(_getNodeLevel(current), _size(current), current->data);
    //      img.insert(_getNodeLevel(current) + 1, _size(current), "/ \\");
    //    }
    //    _printingTreeImage(current->leftChild);
    //    _printingTreeImage(current->rightChild);
    //  }
    //  if (current && current == _getMax(root)){
    //    img.displayImg();
    //  }
    //};

    void _printBinaryTree(const std::string& padding, node* current, bool hasRight)
    { 
      if( current != NULL )
      {
          std::cout << padding << (hasRight ? "|__" : "└──" );
          // print the value of the node
          if (current->color == red)
            std::cout << "\033[31m" << current->data << "\033[0m"<< std::endl;
          else
            std::cout << current->data << std::endl;
          _printBinaryTree(padding + (hasRight ? "│   " : "    "), current->leftChild, (current->rightChild != NULL));
          _printBinaryTree(padding + (hasRight ? "│   " : "    "), current->rightChild, false);
      }
    };

    //void _preOrderTraversal(node *current, std::vector<int> *result){
    //  if (current){
    //    result->push_back(current->getData());
    //    inOrderTraversal(current->leftChild, result);
    //    inOrderTraversal(current->rightChild, result);
    //  }
    //};
    //
    //void _postOrderTraversal(node *current, std::vector<int> *result){
    //  if (current){
    //    inOrderTraversal(current->leftChild, result);
    //    inOrderTraversal(current->rightChild, result);
    //    result->push_back(current->getData());
    //   }
    //};

    bool _isBalanced(node *root){
      return ((_getMaxHigh(root) - _getMinHigh(root)) <= 1);
    };
//
    //bool _isValid(node *previousNode){
    //    // Recurse on left child without breaking if not failing
    //    if (this->leftChild && !this->leftChild->isValid(previousNode))
    //      return false;
    //    // First node retrieve - assign
    //    if (!previousNode)
    //      previousNode = this;
    //    // Previous data does not compare well to the current one - BST not valid
    //    else if (previousNode->data != this->data)
    //      return false;
    //    // Set current node
    //    previousNode = this;
    //    // Recurse on right child
    //    if (this->rightChild && !this->rightChild->isValid(previousNode))
    //      return false;
    //    return true;
    //};
//
    int _size(node *current){
      if (current == NULL){ return 0;}
      int rightSize = _size(current->rightChild);
      int leftSize = _size(current->leftChild);
      return rightSize + leftSize + 1;
    }

    int _getMinHigh(node *current){
      if (current == NULL){
        return 0;
      }
      int lowestHeightLeft = _getMinHigh(current->leftChild);
      int lowestHeightRight = _getMinHigh(current->rightChild);
      return std::min(lowestHeightLeft, lowestHeightRight) + 1;
    };

    int _getMaxHigh(node *current){
      if (current == NULL){
        return 0;
      }
      int lowestHeightLeft = _getMaxHigh(current->leftChild);
      int lowestHeightRight = _getMaxHigh(current->rightChild);
      return std::max(lowestHeightLeft, lowestHeightRight) + 1;
    };



    public:

      binarySearchTree() : root(NULL) {};
      ~binarySearchTree(){
        _timber(root);
        root = NULL;
      };

      int getData(node *current){ return current->data; };
      void insert(int dataToInsert){
        _insert(dataToInsert);
      }

      void remove(int dataToRemove){
        root = _remove(_search(root, dataToRemove));
      }

      void search(int dataToSearch){
        _search(root, dataToSearch);
      }

      void displayTree(){
        _printBinaryTree("", root, false);
        std::cout << std::endl;
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

int main(){

  std::vector<int> v;
  int i = 0;
  int max_size = 15;
  while(i < max_size){
    v.push_back(genRandomNumber());
    i++;
  }
  binarySearchTree tree;
  i = 0;
  while (i < max_size){
    //std::cout << v[i] << " inserted.\n";
    tree.insert(v[i++]);
    tree.displayTree();
  }
  //tree.search(1000);
  //std::cout << "Removing " << v[1] << std::endl;
  //tree.remove(v[0]);
  //tree.displayTree();
  //std::cout << "Removing " << v[3] << std::endl;
  //tree.remove(v[3]);
  //tree.displayTree();
  //std::cout << "Removing " << v[2] << std::endl;
  //tree.remove(v[2]);
  //tree.displayTree();
  return (0);
}