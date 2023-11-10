/*
  Danny
*/

#ifndef AVLTREE_H
#define AVLTREE_H
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

class AVLTreeNode
{
public:
  int element;        // Element contained in the node
  int height;         // height of the node
  AVLTreeNode *left;  // Pointer to the left child
  AVLTreeNode *right; // Pointer to the right child

  AVLTreeNode(int element)
  {
    this->element = element;
    height = 0;
    left = nullptr;
    right = nullptr;
  }
};

class AVLTree
{
public:
  AVLTree()
  {
    root = nullptr;
    size = 0;
    height = 0;
  }

  AVLTree(int elements[], int arraySize)
  {
    root = nullptr;
    size = 0;

    for (int i = 0; i < arraySize; i++)
    {
      insert(elements[i]);
    }
  }

  /* Inorder traversal */
  void inorder() const
  {
    inorder(root);
  }

  /* Inorder traversal from a subtree */
  void inorder(const AVLTreeNode *root) const
  {
    if (root == nullptr)
      return;
    inorder(root->left);
    cout << root->element << " ";
    inorder(root->right);
  }

///////EXERCISE////////
  // return a queue of nodes in level order
  queue<AVLTreeNode *> LevelOrderNodes(AVLTreeNode *someNode)
  {
    queue<AVLTreeNode*> q;
    q.push(someNode);
    if (someNode == nullptr) return q;
    q.push(nullptr);
    AVLTreeNode* temp = nullptr;
    queue<AVLTreeNode*> result;
    while (q.size()>1)
    {
        temp = q.front();
        q.pop();
        result.push(temp);
        if (temp == nullptr){
          q.push(nullptr);
        }
        else{
          if(temp->left!=nullptr)
            q.push(temp->left);
          if(temp->right!=nullptr)
            q.push(temp->right);
        }
    }
    return result;
  }

///////EXERCISE////////
  // display tree with level indices
  void DisplayTreeWithLevelIndices(queue<AVLTreeNode *> q)
  {
    if (!q.front()){
      cout << "It's empty" << endl;
      return;
    }
    AVLTreeNode* temp = nullptr;
    int count = 0;
    cout << "Level " << count << ": ";
    while (!q.empty())
    {
        temp = q.front();
        q.pop();
        if (temp == nullptr){
          cout << endl << "Level " << ++count << ": ";
        }
        else{
          cout << temp->element << " ";
        }
    }
    cout << endl;
    return;
  }

  // level order display
  void LevelOrderDisplay()
  {
    if (root == nullptr)
    {
      cout << "Tree is empty." << endl;
    }
    else
    {
      queue<AVLTreeNode *> q = LevelOrderNodes(root);
      DisplayTreeWithLevelIndices(q);
    }

    /** SAMPLE OUTPUT
After inserting 25, 20, 5:
level 0: 20
level 1: 5 25

After inserting 34, 50:
level 0: 20
level 1: 5 34
level 2: 25 50

After inserting 30
level 0: 25
level 1: 20 34
level 2: 5 30 50

After inserting 10
level 0: 25
level 1: 10 34
level 2: 5 20 30 50

After removing 34, 30, 50:
level 0: 10
level 1: 5 25
level 2: 20

After removing 5:
level 0: 20
level 1: 10 25
     */
  }

  // display tree like a tree, horizontally
  void DisplayTreeHorizontally()
  {
    cout << "==========tree/horizontal view==========\n";
    DisplayTreeHorizontally(root, 0);
  }

  // display the tree rooted at someNode like a tree, horizontally
  void DisplayTreeHorizontally(AVLTreeNode *someNode, int space)
  {
    if (someNode == nullptr)
    {
      return;
    }
    else
    {
      space += 10;

      DisplayTreeHorizontally(someNode->right, space);

      cout << endl;
      for (int i = 10; i < space; i++)
      {
        cout << " ";
      }
      cout << someNode->element << endl;

      DisplayTreeHorizontally(someNode->left, space);
    }
  }

  /* Get the number of nodes in the tree */
  int getSize() const
  {
    return size;
  }

  // Insert element e into the binary tree
  // Return true if the element is inserted successfully
  // Return false if the element is already in the list
  bool binaryTreeInsert(const int &e)
  {
    if (root == nullptr)
      root = createNewNode(e); // Create a new root
    else
    {
      // Locate the parent node
      AVLTreeNode *parent = nullptr;
      AVLTreeNode *current = root;
      while (current != nullptr)
        if (e < current->element)
        {
          parent = current;
          current = current->left;
        }
        else if (e > current->element)
        {
          parent = current;
          current = current->right;
        }
        else
          return false; // Duplicate node not inserted

      // Create the new node and attach it to the parent node
      if (e < parent->element)
        parent->left = createNewNode(e);
      else
        parent->right = createNewNode(e);
    }

    size++;
    return true; // Element inserted
  }

  // Return a path from the root leading to the specified element
  vector<AVLTreeNode *> *path(const int &e) const
  {
    vector<AVLTreeNode *> *v = new vector<AVLTreeNode *>();
    AVLTreeNode *current = root;

    while (current != nullptr)
    {
      v->push_back(current);
      if (e < current->element)
        current = current->left;
      else if (e > current->element)
        current = current->right;
      else
        break;
    }

    return v;
  }

  // insert element into AVLTree
  bool insert(int element)
  {
    bool successful = binaryTreeInsert(element);
    if (!successful)
      return false; // element is already in the tree
    else
      // Balance from element to the root if necessary
      balancePath(element);

    return true; // element is inserted
  }

  // remove element from AVLTree
  bool remove(int element)
  {
    if (root == nullptr)
      return false; // Element is not in the tree

    // Locate the node to be deleted and also locate its parent node
    AVLTreeNode *parent = nullptr;
    AVLTreeNode *current = root;
    while (current != nullptr)
    {
      if (element < current->element)
      {
        parent = current;
        current = current->left;
      }
      else if (element > current->element)
      {
        parent = current;
        current = current->right;
      }
      else
        break; // Element is in the tree pointed by current
    }

    if (current == nullptr)
      return false; // Element is not in the tree

    // Case 0: current is a leaf
    if(current->left == nullptr && current->right == nullptr){
      if (parent == nullptr)
      {
        root = nullptr;
      }
      else
      {
        if (element < parent->element)
          parent->left = nullptr;
        else
          parent->right = nullptr;
        balancePath(parent->element);
      }

      delete current; // Delete current
    }
    // Case 1: current has no left children
    else if (current->left == nullptr)
    {
      // Connect the parent with the right child of the current node
      if (parent == nullptr)
        root = current->right;
      else
      {
        if (element < parent->element)
          parent->left = current->right;
        else
          parent->right = current->right;

        // Balance the tree if necessary
        balancePath(parent->element);
      }

      delete current; // Delete current
    }
    else
    {
      // Case 2: The current node has a left child
      // Locate the rightmost node in the left subtree of
      // the current node and also its parent
      AVLTreeNode *parentOfRightMost = current;
      AVLTreeNode *rightMost = current->left;

      while (rightMost->right != nullptr)
      {
        parentOfRightMost = rightMost;
        rightMost = rightMost->right; // Keep going to the right
      }

      // Replace the element in current by the element in rightMost
      current->element = rightMost->element;

      // Eliminate rightmost node
      if (parentOfRightMost->right == rightMost)
        parentOfRightMost->right = rightMost->left;
      else
        // Special case: parentOfRightMost is current
        parentOfRightMost->left = rightMost->left;

      // Balance the tree if necessary
      balancePath(parentOfRightMost->element);

      delete rightMost; // Delete rightMost
    }

    size--;
    return true; // Element inserted
  }

///////EXERCISE////////
  /* Return the address of the node if the element is in the tree; returns nullptr otherwise */
  AVLTreeNode *search(const int &e) const
  {
    if (!root){
      cout << "Tree is empty." << endl;
      return nullptr;
    }
    else{
      AVLTreeNode* curr = root;
      while (curr != nullptr){
        if (curr->element == e)
          return curr;
        else if (curr->element < e)
          curr = curr->right;
        else
          curr = curr->left;
      }
      return curr;
    }
  }

  // create a new AVLTreeNode
  AVLTreeNode *createNewNode(int element)
  {
    return new AVLTreeNode(element);
  }

///////EXERCISE////////
  /** Balance the nodes in the path from the specified node to the root if necessary */
  void balancePath(int element)
  {
    vector<AVLTreeNode *> *p = path(element);
    for (int i = p->size() - 1; i >= 0; i--)
    {
      AVLTreeNode *A = (*p)[i];
      AVLTreeNode *parentOfA = (A == root) ? nullptr : (*p)[i - 1];

      updateHeight(A); // ensure that height is updated first
      // WRITE CODE HERE
      // hint: we need to check if the tree is balanced at A i.e. use balanceFactors of A and A's children to determine if rotations are needed (if needed then perform rotations by calling the appropriate balance methods [SEE BELOW])
      int balanceFactorA = balanceFactor(A);
      int balanceFactorALeft = balanceFactor(A->left);
      int balanceFactorARight = balanceFactor(A->right);
      if (balanceFactorA == -2 && (balanceFactorALeft == -1 || balanceFactorALeft == 0)){
        balanceLL(A, parentOfA);
      }
      else if(balanceFactorA == 2 && (balanceFactorARight == 1 || balanceFactorARight == 0)){
        balanceRR(A, parentOfA);
      }
      else if (balanceFactorA == -2 && balanceFactorALeft == 1){
        balanceLR(A, parentOfA);
      }
      else if (balanceFactorA == 2 && balanceFactorARight == -1){
        balanceRL(A, parentOfA);
      }
    }
  }

  /** Update the height of a specified node */
  void updateHeight(AVLTreeNode *node)
  {
    if (node->left == nullptr && node->right == nullptr) // node is a leaf
      node->height = 1;
    else if (node->left == nullptr) // node has no left subtree
      node->height = 1 + (*(node->right)).height;
    else if (node->right == nullptr) // node has no right subtree
      node->height = 1 + (*(node->left)).height;
    else
      node->height = 1 + max((*(node->right)).height, (*(node->left)).height);
  }

///////EXERCISE////////
  /** Return the balance factor of the node */
  int balanceFactor(AVLTreeNode *node)
  {
    // use right subtree height - left subtree height
    if (node){
      if (node->right && node->left)
        return node->right->height - node->left->height;
      else if(node->right && !node->left)
        return node->right->height;
      else if (!node->right && node->left)
        return -node->left->height;
      else
        return 0;
    }
    else{
      return 0;
    }
  }

  /** Balance LL */
  void balanceLL(AVLTreeNode *A, AVLTreeNode *parentOfA)
  {
    RotateRight(A, parentOfA);
  }

  /** Balance LR */
  void balanceLR(AVLTreeNode *A, AVLTreeNode *parentOfA)
  {
    RotateLeft(A->left, A);
    RotateRight(A, parentOfA);
  }

///////EXERCISE////////
  /** Balance RR */
  void balanceRR(AVLTreeNode *A, AVLTreeNode *parentOfA)
  {
    RotateLeft(A, parentOfA);
  }

///////EXERCISE////////
  /** Balance RL */
  void balanceRL(AVLTreeNode *A, AVLTreeNode *parentOfA)
  {
    RotateRight(A->right, A);
    RotateLeft(A, parentOfA);
  }

  // returns the number of nodes at level level in the tree
  int CountNodesAtLevel(int level)
  {
    int count = 0;
    CountNodesAtLevel(root, level, count);
    return count;
  }

///////EXERCISE////////
  // helper function for CountNodesAtLevel
  void CountNodesAtLevel(AVLTreeNode *someNode, int level, int &count)
  {
    if (level < 0 || !someNode) return;
    queue<AVLTreeNode*> q;
    q.push(someNode);
    q.push(nullptr);
    int currentLevel = 0;
    AVLTreeNode* temp = nullptr;
    while (!q.empty() && currentLevel < level){
      temp = q.front();
      q.pop();
      if (temp == nullptr){
        q.push(nullptr);
        currentLevel++;
      }
      else{
        if (temp->left)
          q.push(temp->left);
        if (temp->right)
          q.push(temp->right);
      }
    }
    while (q.size()>1){
      count++;
      q.pop();
    }
  }

  // returns the number of nodes in the tree that are between min and max (inclusive)
  int Count(int min, int max)
  {
    int count = 0;
    Count(root, min, max, count);
    return count;
  }

///////EXERCISE////////
  // helper function for Count
  void Count(AVLTreeNode *someNode, int min, int max, int &count)
  {
    if(!someNode) return;
    if (someNode->element >= min && someNode->element <= max) count++;
    Count(someNode->left, min, max, count);
    Count(someNode->right, min, max, count);
  }

///////EXERCISE////////
  // right rotates the tree at node someNode if possible (if someNode is nullptr or someNode->left is nullptr, no rotation is performed)
  void RotateRight(AVLTreeNode *someNode, AVLTreeNode* parentOfSomeNode)
  {
    //Can call a getParent() function to get parentOfSomeNode instead of passing variable.
    if (!someNode || !someNode->left) return;
    AVLTreeNode *someNodeLeft = someNode->left; 

    if (someNode == root)
      root = someNodeLeft;
    else if (parentOfSomeNode->left == someNode)
      parentOfSomeNode->left = someNodeLeft;
    else
      parentOfSomeNode->right = someNodeLeft;

    someNode->left = someNodeLeft->right; 
    someNodeLeft->right = someNode;
    updateHeight(someNode);
    updateHeight(someNodeLeft);
  }

///////EXERCISE////////
  // left rotates the tree at node someNode if possible (if someNode is nullptr or someNode->right is nullptr, no rotation is performed)
  void RotateLeft(AVLTreeNode* someNode, AVLTreeNode* parentOfSomeNode)
  {
    //Can call a getParent() function to get parentOfSomeNode instead of passing variable.
    if (!someNode || !someNode->right) return;
    AVLTreeNode *someNodeRight = someNode->right; 
    
    if (someNode == root)
      root = someNodeRight;
    else if (parentOfSomeNode->right == someNode)
      parentOfSomeNode->right = someNodeRight;
    else
      parentOfSomeNode->left = someNodeRight;

    someNode->right = someNodeRight->left; 
    someNodeRight->left = someNode;
    updateHeight(someNode);
    updateHeight(someNodeRight);
  }

  // returns the diameter of the tree
  // diameter is the number of nodes along the longest path between any two leaves in the tree
  // see https://leetcode.com/problems/diameter-of-binary-tree/
  int Diameter()
  {
    return Diameter(root);
  }

/*
IDEA: keep splitting tree into two halves and look for the longest possible path.
Complexity: O(n^2)
This function is possible to be O(n)
*/

///////EXERCISE////////
  // helper function for Diameter
  int Diameter(AVLTreeNode *someNode)
  {
    if (!someNode) return 0;

    //Get height of both subtrees. leftHeight + rightHeight + 1 could be the length of the diameter
    int leftHeight = (someNode->left)?someNode->left->height:0;
    int rightHeight = (someNode->right)?someNode->right->height:0;

    //Look for the Diameter of the left sub tree, then right sub tree; we choose the longer one
    int longestDiameter = max(Diameter(someNode->left),Diameter(someNode->right));

    //in case leftHeight+rightHeight+1 is the actual longer diamter
    if (leftHeight+rightHeight+1 > longestDiameter){
      return leftHeight+rightHeight+1;
    }
    return longestDiameter;
  }
  
private:
  AVLTreeNode *root;
  int size;
  int height;
  vector<AVLTreeNode*> backups;
};

#endif
