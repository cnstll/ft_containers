#include <iterator>
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

class binarySearchTree {



    struct node {
      int data;
      node *parentNode;
      node *leftChild;
      node *rightChild;
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
    }

    node *_insert(node *current, node *parent, int dataToInsert){
      if (current == NULL){
        std::cout << "Parent: "<< parent->data << std::endl;
        current = _createNewNode(dataToInsert, parent);
        return current;
      }
      else if (current->data < dataToInsert){
          current->rightChild = _insert(current->rightChild, current, dataToInsert);
      }
      else {
          current->leftChild = _insert(current->leftChild, current, dataToInsert);
      }
      return current;
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
        std::cout << tmp->data << " is successor.\n";
        if (tmp->parentNode != toRemove){
          _subTreeShift(tmp, tmp->rightChild);
          tmp->rightChild = toRemove->rightChild;
          tmp->rightChild->parentNode = tmp;
        }
        std::cout << "looking for successor\n";
        _subTreeShift(toRemove, tmp);
        tmp->leftChild = toRemove->leftChild;
        tmp->leftChild->parentNode = tmp;
      }
      delete toRemove;
      return root;
    };

    void _subTreeShift(node *removed, node *replacing){
    
      if (removed->parentNode == NULL){
        std::cout << "Removing root \n";
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


    void _inOrderTraversal(node *current){
      if (current){

        _inOrderTraversal(current->leftChild);
        std::cout << current->data << " ";
        _inOrderTraversal(current->rightChild);
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

      int getData(node *current){ return current->data; }
      void insert(int dataToInsert){
        if (root == NULL)
          root = _createNewNode(dataToInsert, NULL);
        else
          root = _insert(root, root->parentNode, dataToInsert);
      }

      void remove(int dataToRemove){
        root = _remove(_search(root, dataToRemove));
      }

      void search(int dataToSearch){
        root = _search(root, dataToSearch);
      }

      void displayTree(){
        _inOrderTraversal(root);
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
  int max_size = 6;
  while(i < max_size){
    v.push_back(genRandomNumber());
    i++;
  }
  binarySearchTree tree;
  i = 0;
  while (i < max_size){
    std::cout << v[i] << " inserted.\n";
    tree.insert(v[i++]);
  }
  tree.displayTree();
  std::cout << "Removing " << v[1] << std::endl;
  tree.remove(v[0]);
  tree.displayTree();
  std::cout << "Removing " << v[3] << std::endl;
  tree.remove(v[3]);
  tree.displayTree();
  std::cout << "Removing " << v[2] << std::endl;
  tree.remove(v[2]);
  tree.displayTree();
  return (0);
}