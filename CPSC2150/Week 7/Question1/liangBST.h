#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

class TreeNode
{
public:
  int element; // Element contained in the node
  TreeNode* left; // Pointer to the left child
  TreeNode* right; // Pointer to the right child

  TreeNode() // default constructor
  {
    element = 0;
    left = nullptr;
    right = nullptr;
  }

  TreeNode(const int& e) // defined constructor
  {
    this->element = e;
    left = nullptr;
    right = nullptr;
  }
};

class BST
{
public:
  BST() // default constructor
  {
    root = nullptr;
    size = 0;
  }

  BST(int *elements, int arraySize) // defined constructor
  {
    root = nullptr;
    size = 0;

    for (int i = 0; i < arraySize; i++)
    {
      insert(elements[i]);
    }
  }

  /* Copy constructor */
  BST(const BST& tree)
  {
    root = nullptr;
    size = 0;
    copy(tree.root); // Recursively copy nodes to this tree
  }

/////EXERCISE
  /* Copies the element from the specified tree to this tree */
  void copy(const TreeNode* givenRoot)
  {
    if (givenRoot == nullptr)
      return;
    root = copyRecursively(givenRoot);
  }
  
  TreeNode* copyRecursively(const TreeNode* node){
    if (node == nullptr){
      return nullptr;
    }
    TreeNode* thisNode = new TreeNode(node->element);
    size++;
    thisNode->left = copyRecursively(node->left);
    thisNode->right = copyRecursively(node->right);
    return thisNode;
  }

  /* Destructor */
  ~BST()
  {
    clear();
  }

  bool isEmpty(){
    return size==0;
  }

/////EXERCISE
  /* Return the address of the node if the element is in the tree; returns nullptr otherwise */
  TreeNode* search(const int& e) const
  {
    TreeNode* find = searchNodes(root, e);
    return find;
  }

  TreeNode* searchNodes(TreeNode* node, const int& e) const{
    if (node == nullptr)
      return nullptr;

    if (node->element == e)
      return node;
    else if (node->element > e){
      return searchNodes(node->left, e);
    }
    else
      return searchNodes(node->right,e);
  }

  TreeNode* createNewNode(const int& e)
  {
    return new TreeNode(e);
  }

  // Insert element e into the binary tree
  // Return true if the element is inserted successfully
  // Return false if the element is already in the list
  bool insert(const int& e)
  {
    if (root == nullptr)
      root = createNewNode(e); // Create a new root
    else
    {
      // Locate the parent node
      TreeNode* parent = nullptr;
      TreeNode* current = root;
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

  /* Inorder traversal */
  void inorder() const
  {
    inorder(root);
  }

  /* Inorder traversal from a subtree */
  void inorder(const TreeNode* someNode) const
  {
    if (someNode == nullptr) return;

    inorder(someNode->left); // process all nodes in left sub-tree of someNode
    cout << someNode->element << " "; // process someNode
    inorder(someNode->right); // process all nodes in right sub-tree of someNode
  }

  /* Postorder traversal */
  void postorder() const
  {
    postorder(root);
  }

/////EXERCISE
  /** Postorder traversal from a subtree */
  void postorder(const TreeNode* someNode) const
  {
    if (someNode == nullptr) return;

    postorder(someNode->left);
    postorder(someNode->right);
    cout << someNode->element << " ";
  }

  /* Preorder traversal */
  void preorder() const
  {
    preorder(root);
  }

/////EXERCISE
  /* Preorder traversal from a subtree */
  void preorder(const TreeNode* someNode) const
  {
    if (someNode == nullptr) return;

    cout << someNode->element << " ";
    preorder(someNode->left);
    preorder(someNode->right);
  }

  /* Get the number of nodes in the tree */
  int getSize() const
  {
    return size;
  }

/////EXERCISE
  /* Remove all nodes from the tree */
  void clear()
  {
    if (root==nullptr) return;
    root = clearNodes(root);
  }

  TreeNode* clearNodes(TreeNode* node){
    if (node == nullptr)
      return nullptr;
    node->left = clearNodes(node->left);
    node->right = clearNodes(node->right);

    delete node;
    size--;
    return nullptr;
  }

/////EXERCISE
  /* Return a path from the root leading to the specified element.
  If specified element does not exist in the tree then add a nullptr 
  to the end.*/
  vector<TreeNode*>* path(const int& e) const
  {
    /*
      since this is a path, I assume that we will store vector of the original nodes (not a copy of them).
    */
    vector<TreeNode*>* result = new vector<TreeNode*>;
    TreeNode* current = root;
    while (current != nullptr && current->element != e){
      result->push_back(current);
      if (current->element > e)
        current = current->left;
      else
        current = current->right;
    }
    result->push_back(current);
    return result;
  }

  /* Delete an element e from the binary tree.
   * Return true if the element is deleted successfully
   * Return false if the element is not in the tree */
  bool remove(const int& e)
  {
    // Locate the node to be deleted and also locate its parent node
    TreeNode* parent = nullptr;
    TreeNode* current = root;
    while (current != nullptr)
    {
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
        break; // Element e is in the tree pointed by current
    }

    if (current == nullptr)
      return false; // Element e is not in the tree

    // Case 1: current has no left children
    if (current->left == nullptr)
    {
      // Connect the parent with the right child of the current node
      if (parent == nullptr)
      {
        root = current->right;
      }
      else
      {
        if (e < parent->element)
          parent->left = current->right;
        else
          parent->right = current->right;
      }

      delete current; // Delete current
    }
    else
    {
      // Case 2: The current node has a left child
      // Locate the rightmost node in the left subtree of
      // the current node and also its parent
      TreeNode* parentOfRightMost = current;
      TreeNode* rightMost = current->left;

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
        // Special case: parentOfRightMost->right == current
        parentOfRightMost->left = rightMost->left;

      delete rightMost; // Delete rightMost
    }

    size--;
    return true; // Element inserted
  }

/////ADDITIONAL EXERCISES/////

    // returns the height of the tree
    int GetHeight(){
        if(root == nullptr){
            return 0;
        }
        else{
            return GetHeight(root);
        }
    }

/////EXERCISE
    // returns the height of someNode
    int GetHeight(TreeNode* someNode){
        if (someNode == nullptr){
          return 0;
        }
        else{
          int leftHeight = GetHeight(someNode->left);
          int rightHeight = GetHeight(someNode->right);

          if (leftHeight > rightHeight){
            return leftHeight + 1;
          }
          else{
            return rightHeight + 1;
          }
        }
    }

    // Increment each node's value by 1
    void IncrementByOne(){
        InorderIncrementByOne(root);
    }

/////EXERCISE
    // Increment each node (that is part of the tree rooted at someNode) by 1
    void InorderIncrementByOne(TreeNode* someTreeNode){
        if (someTreeNode == nullptr)
          return;
        someTreeNode->element += 1;
        InorderIncrementByOne(someTreeNode->left);
        InorderIncrementByOne(someTreeNode->right);
    }

    // returns the number of nodes in the tree
    int NodeCount(){
        return InOrderNodeCount(root);
    }

/////EXERCISE
    // returns the number of nodes in the tree rooted at someNode
    int InOrderNodeCount(TreeNode* someNode){
        if (someNode == nullptr)
          return 0;
        return 1 + InOrderNodeCount(someNode->left) + InOrderNodeCount(someNode->right);
    }

    // returns the number of nodes in the tree with odd values
    int NodesWithOddValues(){
      return InOrderNodesWithOddValues(root);
    }

/////EXERCISE
    // returns the number of nodes in the tree rooted at someNode with odd values
    int InOrderNodesWithOddValues(TreeNode* someNode){
        if (someNode == nullptr)
          return 0;
        return ((someNode->element%2)==1) + InOrderNodesWithOddValues(someNode->left) + InOrderNodesWithOddValues(someNode->right);
    }

  // level order display
    void LevelOrderDisplay(){
        LevelOrderDisplay(root);
    }

/////EXERCISE
    // level order display of the tree rooted at someNode
    void LevelOrderDisplay(TreeNode* someNode){
        // use a queue, STL queue is fine
        if (root == nullptr) return;
        queue<TreeNode*> q;
        TreeNode* curr;
        TreeNode* newLine = new TreeNode(INT_MIN);
        // Enqueue Root and NULL node.
        q.push(root);
        q.push(newLine);
        while (q.size() > 1)
        {
            curr = q.front();
            q.pop();
            if (curr == newLine){
              cout << endl;
              q.push(newLine);
            }
            else{
              if(curr->left != nullptr)
                q.push(curr->left);
              if(curr->right != nullptr)
                q.push(curr->right);
              cout << curr->element << "\t";
            }
        }
        cout << endl;
        delete newLine;
    }

    // display tree like a tree horizontally
    void DisplayTreeHorizontally(){
        DisplayTreeHorizontally(root, 0);
    }

    // display the tree rooted at someNode like a tree, horizontally
    void DisplayTreeHorizontally(TreeNode* someNode, int space){
        if(someNode == nullptr){
            return;
        }
        else{
            space += 10;

            DisplayTreeHorizontally(someNode->right, space);

            cout << endl;
            for(int i = 10; i < space; i++){
                cout << " ";
            }
            cout << someNode->element << endl;

            DisplayTreeHorizontally(someNode->left, space);
        }
    }
  ///////// Wk7HW
  void LoadTreeFromFile(string fileName){
    // in what format?
    // I assume that it's
    // size
    // arr[0] arr[1] arr[2] arr[3] ...
    ifstream file(fileName);
    if(file.is_open()){
      int size;
      file >> size;
      if (size > 0){
        this->clear();
        int value=INT_MIN;
        while (file >> value){
          this->insert(value);
        }
        if (value == INT_MIN){
          cout << "Does not have data for the array." << endl;
        }
      }
      else{
        cout << "Size must be >= 0" << endl;
      }
      file.close();            
    }
    else{
      cout << "File not found" << endl;
    }
  }

  TreeNode* kthSmallest(int k){
    if (k < 1 || k > size) return nullptr;
    TreeNode* current = nullptr;
    kthSmallestHelper(root, k, current);
    return current;
  }

  void kthSmallestHelper(TreeNode* someNode, int& k, TreeNode*& current) 
  {
    if (someNode == nullptr || current != nullptr) return;
    kthSmallestHelper(someNode->left, k, current); // process all nodes in left sub-tree of someNode
    if (--k == 0){
      current = someNode;
      return;
    }
    kthSmallestHelper(someNode->right, k, current); // process all nodes in right sub-tree of someNode
  }

  TreeNode* ClosestCommonAncestor(TreeNode* node1, TreeNode* node2){
    vector<TreeNode*>* path1 = this->path(node1->element);
    vector<TreeNode*>* path2 = this->path(node2->element);

    TreeNode* closestCommonAncestor = nullptr;
    for (int i =0; i < (*path1).size()-1; i++){
      for (int j = 0; j < (*path2).size()-1; j++){
        if ((*path1)[i] == (*path2)[j]){
          closestCommonAncestor = (*path1)[i];
        }
      }
    }

    delete path1;
    delete path2;

    return closestCommonAncestor;
  }

  bool operator==(BST const& rhs) const 
  {
    if (this == &rhs) return true;
    return compareBST(this->root, rhs.root);
  }

  bool compareBST(TreeNode* node1, TreeNode* node2) const{
    if ((node1 == nullptr) && (node2 == nullptr))
      return true;
    else if (node1 == nullptr || node2 == nullptr)
      return false;
  
    return ((node1->element==node2->element) && compareBST(node1->left, node2->left) && compareBST(node1->right, node2->right));
  }

  BST& operator=(BST const& rhs) {
    if (this != &rhs){
      this->root = this->clearNodes(this->root);
      this->root = this->copyRecursively(rhs.root);
    }
    return *this;
  }

  ////

  BST(int *elements, int arraySize, bool balanced) // defined constructor
  {
    root = nullptr;
    size = 0;
    if (!balanced){
      for (int i = 0; i < arraySize; i++)
      {
        insert(elements[i]);
      }
    }
    else{
      // Using BST to sort the array (JFF)
      BST tempTree(elements, arraySize);
      int* sortedArray = sortToArray(tempTree, arraySize);
      //
      insertTreeBalance(sortedArray, 0, arraySize-1);

      delete[] sortedArray;
      //tempTree will call its destructor by itself.
    }
  }

  void insertTreeBalance(int* arr, int start, int end){
    if (start > end){
      return;
    }
    int mid = start + (end-start)/2;
    insert(arr[mid]);
    insertTreeBalance(arr, start, mid-1);
    insertTreeBalance(arr, mid+1, end);
  }

  int* sortToArray(BST& tempTree, int arraySize){
    if (arraySize <= 0)
      return nullptr;

    int* result = new int[arraySize];
    int index = 0;
    inOrderSort(tempTree.root, result, index);
    return result;
  }

  void inOrderSort(TreeNode* someNode, int* elements, int& index){
      if (someNode == nullptr) return;
      inOrderSort(someNode->left, elements, index);
      elements[index++] = someNode->element;
      inOrderSort(someNode->right, elements, index);
  }

private:
  TreeNode* root;
  int size;
};

#endif
