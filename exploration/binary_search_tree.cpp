#include <iterator>
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

class binarySearchTree {

  public:
    binarySearchTree(const int data) : data(data), parentNode(NULL), leftChild(NULL), rightChild(NULL){ std::cout << "Subtree with value " << data << " constructed.\n"; };
    
    static binarySearchTree* build(std::vector<int> &v){
      static binarySearchTree *root = new binarySearchTree(*(v.begin()));
      std::vector<int>::const_iterator it = v.begin() + 1;
      while (it != v.end()){
        root->insert(*it);
        it++;
      }
      return root;
    };

    void insert(int dataToInsert){
      if (this->data < dataToInsert){
        if (this->rightChild == NULL){
          binarySearchTree *insertedNode = new binarySearchTree(dataToInsert);
          this->rightChild = insertedNode;
          insertedNode->parentNode = this;
          std::cout << dataToInsert << " was right inserted.\n";
          return ;
        }
        else {
          this->rightChild->insert(dataToInsert);
        }
      }
      else {
        if (this->leftChild == NULL){
          binarySearchTree *insertedNode = new binarySearchTree(dataToInsert);
          this->leftChild = insertedNode;
          insertedNode->parentNode = this;
          std::cout << dataToInsert << " was left inserted.\n";
          return ;
        }
        else {
          this->leftChild->insert(dataToInsert);
        }
      }
    };
    /*
    Replaces the managed object.

1) Given current_ptr, the pointer that was managed by *this, performs the following actions, in this order:
Saves a copy of the current pointer old_ptr = current_ptr
Overwrites the current pointer with the argument current_ptr = ptr
If the old pointer was non-empty, deletes the previously managed object if(old_ptr) get_deleter()(old_ptr).
*/
//
//    void remove(binarySearchTree *node){
//      if (!node->leftChild && !node->rightChild){
//          delete node;
//      }
//      else if (node->leftChild && !node->rightChild){
//        binarySearchTree *oldNode = node;
//        node = node->leftChild;
//        delete oldNode;
//      }
//      else if (node->rightChild 11 !node->leftChild) {
//        binarySearchTree *oldNode = node;
//        node = node->rightChild;
//        delete oldNode;
//      }
//      else {
//        binarySearchTree *successor = getSuccessor(node);
//        if (successor == node->rightChild){
//          binarySearchTree *oldNode = node;
//          if (successor->leftChild)
//            successor->leftChild = node->leftChild;
//          else
//          node = successor;
//        }
//      }
//    };

    void remove(binarySearchTree *node){
    
      if (node->leftChild == NULL)
        subTreeShift(node, node->rightChild);
      else if (node->rightChild == NULL)
        subTreeShift(node, node->leftChild);
      else {
        binarySearchTree *successor = getSuccessor(node);
        if (successor->parentNode != node){
          subTreeShift(successor, successor->rightChild);
          successor->rightChild = node->rightChild;
          successor->rightChild->parentNode = successor; //necessary?
        }
        subTreeShift(node, successor);
        successor->leftChild = node->leftChild;
        node->leftChild->parentNode = successor; //necessary ?
      }
      delete node;
    };

    void subTreeShift(binarySearchTree *old, binarySearchTree *replacing){
    
      if (old->parentNode == NULL)
        ;//T.root := v c'est la root 
      else if (old == old->parentNode->leftChild)
        old->parentNode->leftChild = replacing;
      else
        old->parentNode->rightChild = replacing;
      if (replacing != NULL)
        replacing->parentNode = old->parentNode;
    }


    binarySearchTree *getSuccessor(binarySearchTree *node){
      while (node->rightChild != NULL){
        return node->rightChild->getMin();
      }
      binarySearchTree *parent = node->parentNode;
      while(parent != NULL && node == parent->rightChild){
        node = parent;
        parent = parent->parentNode;
      }
      return parent;
    };

    binarySearchTree *getPredecessor(binarySearchTree *node){
      while (node->leftChild != NULL){
        return node->leftChild->getMax();
      }
      binarySearchTree *parent = node->parentNode;
      while (parent != NULL && node == parent->leftChild){
        node = parent;
        parent = parent->parentNode;
      }
      return parent;
    };

    binarySearchTree *getMin(){
      binarySearchTree *minNode = this;
      while (minNode->leftChild){
        minNode = minNode->leftChild;
      }
      return minNode;
    };

    binarySearchTree *getMax(){
      binarySearchTree *maxNode = this;
      while (maxNode->rightChild){
        maxNode = maxNode->rightChild;
      }
      return maxNode;
    };

    binarySearchTree *search(int dataToFind){
      if (this->data == dataToFind)
        return this;
      if (this->data < dataToFind)
        return this->rightChild ? rightChild->search(dataToFind) : NULL;
      else 
        return this->leftChild ? leftChild->search(dataToFind) : NULL;
    };


    void inOrderTraversal(binarySearchTree *node, std::vector<int> *result){
      if (!node) { return; }
      inOrderTraversal(node->leftChild, result);
      result->push_back(node->getData());
      inOrderTraversal(node->rightChild, result);
    };

    bool isBalanced(){
      return ((getHighestHeight(this) - getLowestHeight(this)) == 1);
    };

    int Size(binarySearchTree *node){
      if (node == NULL){ return 0;}
      int rightSize = Size(node->rightChild);
      int leftSize = Size(node->leftChild);
      return rightSize + leftSize + 1;
    }

    int getLowestHeight(binarySearchTree *node){
      if (node == NULL){
        return 0;
      }
      int lowestHeightLeft = getLowestHeight(node->leftChild);
      int lowestHeightRight = getLowestHeight(node->rightChild);
      return std::min(lowestHeightLeft, lowestHeightRight) + 1;
    };

    int getHighestHeight(binarySearchTree *node){
      if (node == NULL){
        return 0;
      }
      int lowestHeightLeft = getHighestHeight(node->leftChild);
      int lowestHeightRight = getHighestHeight(node->rightChild);
      return std::max(lowestHeightLeft, lowestHeightRight) + 1;
    };

    //void printTree(binarySearchTree *node){
//
    //};

    int getData(){ return data; }

  private:
    int data;
    binarySearchTree *parentNode;
    binarySearchTree *leftChild;
    binarySearchTree *rightChild;
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
  int max_size = 19;
  while(i < max_size){
    v.push_back(genRandomNumber());
    i++;
  }
  binarySearchTree *root;
  binarySearchTree *max;
  binarySearchTree *min;
  int lowestHeight;
  int highestHeight;

  root = root->build(v);
  max = root->getMax();
  min = root->getMin();
  std::vector<int> result;
  lowestHeight = root->getLowestHeight(root);
  highestHeight = root->getHighestHeight(root);

  std::cout << "Max: " << max->getData() << std::endl;
  std::cout << "Min: " << min->getData() << std::endl;
  std::cout << "Lowest Height: " << lowestHeight << std::endl;
  std::cout << "Highest Height: " << highestHeight << std::endl;
  std::cout << "Is balanced?: " << root->isBalanced() << std::endl;
  std::cout << "Size: " << root->Size(root) << std::endl;
  std::cout << "Data in Tree:\n";
  result.erase(result.begin(), result.end());
  root->inOrderTraversal(root, &result);
  std::vector<int>::iterator it = result.begin();
  while (it != result.end()){
    std::cout << *it << std::endl;
    it++;
  }
  std::cout << "Removing: " << result[max_size/2] << "\n";
  root->remove(root->search(result[max_size/2]));
  max_size--;
  std::vector<int> result2;
  root->inOrderTraversal(root, &result2);
  std::cout << "Removing: " << result2[max_size/2] << "\n";
  root->remove(root->search(result2[max_size/2 - 1]));
  root->remove(root->search(result2[0]));
  root->insert(42);
  result2.erase(result2.begin(), result2.end());
  root->inOrderTraversal(root, &result2);
  std::vector<int>::iterator it2 = result2.begin();
  std::cout << "Data in Tree after remove:\n";
  while (it2 != result2.end()){
    std::cout << *it2 << std::endl;
    it2++;
  }
  
  return (0);
}