#include "BinarySearchTree.hpp"
#include <iostream>
#include <cmath>
using namespace std;

  BinarySearchTree::Node::Node(DataType newval)
  {
  val = newval;
  left = right = NULL;
  }
  
  BinarySearchTree::BinarySearchTree()
  {
  root_ = NULL;
  size_ = 0;                                    
  }
  
  // Destructor.
  BinarySearchTree::~BinarySearchTree()
  {
  while (size_!=0)
  remove(max());                          
  }
  
  // Inserts value "val" into the tree. Returns false if failed (i.e., "val"
  // already exists in the tree), and true otherwise.
  bool BinarySearchTree::insert(DataType val)
  {
  Node* key = new Node (val);
  if (size_ == 0)
  {
      root_ = key;
      size_ ++;
      key = NULL;
      return true;       
  }
  Node* visitor = root_;
  Node* parent = NULL;     
  while (visitor != NULL && (visitor->left!=NULL || visitor->right!=NULL))
  {
        parent = visitor;
        if (val < visitor->val) visitor = visitor->left;
        else visitor = visitor->right;
  }
  if (visitor == NULL)
  {
   if (val >= parent->val) parent->right=key;
   else parent->left = key;
   }
  else
  {
   if (val < visitor->val) visitor->left = key; 
   else visitor->right = key;
  }
  size_ ++;
  visitor = NULL;
  key = NULL;
  return true;
  }
  
  // Removes the node with value "val" from the tree. Returns true if successful,
  // false otherwise.
  bool BinarySearchTree::remove(DataType val)
  {
  if (size_ == 0) return false;
  Node* visitor = root_;
  Node* parent = visitor;
  bool reached = false;
  while (visitor->val != val && (visitor->left!= NULL || visitor->right!= NULL))
  {
        
        parent = visitor;
        if (val < visitor->val) visitor = visitor->left;
        else visitor = visitor->right;
  }
  if (val == visitor->val) reached = true;
  if (!reached) return false;
  if (visitor->left == NULL && visitor->right==NULL)
  {
      if (visitor == root_) root_ = NULL;
      else if (parent-> left == visitor) parent->left = NULL;
      else parent->right = NULL;
      delete visitor;                   
  }
  else if (visitor->left!= NULL && visitor->right == NULL)
  {
       if (visitor == root_) root_ = root_->left;
       else if (parent->left == visitor) parent->left = visitor->left;
       else parent->right = visitor->left;
       visitor -> left = visitor -> right = NULL;
       delete visitor;
  }      
   else if (visitor->left == NULL && visitor->right != NULL)
  {
       if (visitor == root_) root_ = root_->right;
       else if (parent->right == visitor) parent->right = visitor->right;
       else parent->left = visitor->right;
       visitor -> left = visitor -> right = NULL;
       delete visitor;
  }      
  else 
  {
       Node* smallest = visitor->right;
       parent = smallest; 
       while (smallest->left != NULL)
       {
             parent = smallest;
             smallest = smallest->left;
       }
       if (smallest->right==NULL)
       {
       parent->left = NULL;
       visitor->val = smallest->val;
       if (visitor->right == smallest) visitor->right = NULL;
       }
       else 
       {
        if (parent == smallest) visitor->right = parent->right;
        else parent->left = smallest->right;
        visitor->val = smallest->val;    
       }
   delete smallest;    
   smallest = NULL;
  }
  visitor = NULL;
  parent = NULL;
  size_--;
  return true;
}
  // Returns true if a node with value "val" exists in the tree; false otherwise.
  bool BinarySearchTree::exists(DataType val) const
  {
  if (size_ == 0) return false;
  Node* visitor = root_;
  while (visitor!=NULL && (visitor->left!=NULL || visitor->right!=NULL))
  {
        if (val == visitor->val) return true;
        else if (val < visitor->val) visitor = visitor->left;
        else visitor = visitor->right;
  }
  if (visitor==NULL) return false;
  if (val == visitor->val) return true;
  else return false;                                      
  }
  
  // Returns the minimum value of the tree. You can assume that this function
  // will never be called on an empty tree.
  BinarySearchTree::DataType BinarySearchTree::min() const
  {
  Node* visitor = root_;
  while (visitor->left != NULL)
        visitor = visitor->left;
  return visitor->val;                                      
  }
  
  // Returns the maximum value of the tree. You can assume that this function
  // will never be called on an empty tree.
  BinarySearchTree::DataType BinarySearchTree::max() const
  {
  Node* visitor = root_;
  while (visitor->right != NULL)
        visitor = visitor->right;
  return visitor->val;                                    
  }
  
  // Returns the number of nodes in the tree.
  unsigned int BinarySearchTree::size() const
  {
  return size_;                                   
  }
  
  // Returns the maximum depth of the tree. A tree with only the root node has a
  // depth of 0. You can assume that this function will never be called on an 
  // empty tree.
  unsigned int BinarySearchTree::depth() const
  {
   return BinarySearchTree::getNodeDepth(root_);                         
  }
  
  // You can print the tree in which ever manner you like, however methods such
  // as in-order, level-order, etc. might be the most useful for debugging
  // purposes.
  
 /* void BinarySearchTree::print() const
  {
    Node* list = new Node [size_];
    unsigned int l_size = 0;
    Node* visitor = root_;
    while (visitor->left!=NULL || visitor->right!=NULL || l_size > 0)
    {
    if (visitor->right!=NULL) 
    {
     list[l_size]=visitor->right;
     l_size++;
    }
    cout << visitor->val << "_";
    if (visitor->left!=NULL)
    {
    visitor = visitor->left;
    }
    else
    {
    visitor = list[l_size-1];
    list[l_size-1] = NULL;
    l_size--;
    if (l_size == 0) cout << visitor->val << "_";
    }                                     
    }
  }
*/
  // Optional function.
  // Recursively get the maximum depth from a given node. Call on root_ first.
  // This might be of great value to you in depth().
  int BinarySearchTree::getNodeDepth(Node* n) const
  {
    if (n->left==NULL && n->right==NULL) return 0;
    else if (n->right == NULL) return 1+BinarySearchTree::getNodeDepth(n->left);
    else if (n->left == NULL) return 1+BinarySearchTree::getNodeDepth(n->right);
    else 
    {
     unsigned int leftST = BinarySearchTree::getNodeDepth(n->left);
     unsigned int rightST = BinarySearchTree::getNodeDepth(n->right);
     if (leftST >= rightST) return 1+leftST;
     else return 1+rightST;
    }
  }
