// (Extended) Binary tree implementation
// Note: Some of these are outdated functions that don't work - I need to revisit and delete them.
//        This started off as a practice problem from Jumping into C++ (Allain) before I did a few
// 		  problems from Introdution to Algorithms (Cormen)

#include <iostream>
#include <deque>
#include <string>

using namespace std;

struct Node{
  int key;
  int height; //new addition
  Node* p; //direct precessor
  Node* rhs; //lower level node to right
  Node* lhs; //lower level node to left
};

bool search(Node* root, int key); //returns true if found
Node* iterative_tree_search(Node* root, int input);//returns node position if found else NULL
void inorder_print(Node** root, int key); //prints root, then lhs, then rhs
void preorder_print(Node* root);  //prints lhs, then root, then rhs
void postorder_print(Node* root); //prints rhs, then root, then lhs
void count_nodes(Node* root, int& counter);  //returns number of nodes in subtrees
void check_balance(Node* root); //compares rhs and lhs # of nodes using count_nodes()
void check_lhs_lesser(Node* root); //checks every subtree having a left and right node has lhs < rhs
void check_rhs_lesser(Node* root); //same as above in vice-versa
void kill(Node** root);  //returns all memory to freestore
void tree_delete(Node** root, Node** z);
Node* tree_min(Node* x);
Node* tree_max(Node* x);
Node* tree_successor(Node* x);
void tree_print(Node* root, string space);
void transplant(Node** root, Node** u, Node** v);
void tree_delete(Node** root, Node** z);
//BELOW ARE OLD
void left_rotate(Node** root, Node** x);
void right_rotate(Node** root, Node** y);
//THESE ARE NEW
void rotate_left(Node** root, Node** x);
void rotate_right(Node** root, Node** x);

//USING THIS SPLAY SUBROUTINE WILL CAUSE A CORE DUMP OF A VALUE DOESN'T EXIST!
void splay(Node** root, Node** x); //this will turn the BST into a Splay Tree
int depth(Node** root); //compute the depth of the deepest node...
int left_nodes(Node** root, int& left);
int right_nodes(Node** root, int& right);
int total_nodes(Node** root, int& left, int& right);
void left_right_nodes(Node** root, int& lefty, int& righty);
void level_order(Node** root, int level);
void level_order_print(Node* root, int alpha);
float density(Node** root);


void insert(Node** root, int input){  //this will create a Binary Search Tree
  Node* z = new Node;
  z->key = input;
  z->height = 0;
  Node* y = NULL;
  Node* x = *root;
  while (x != NULL){
    y = x;   //HAHA!
    if (z->key < x->key)
      x = x->lhs;
    else
      x = x->rhs;
  }
  z->p = y;
  if (y == NULL){  //tree is empty
    *root = z;
  }
  else if (z->key < y->key)
    y->lhs = z;
  else
    y->rhs = z;

  if (z != *root){
    z->height = z->p->height + 1;
  }
  cout << "key::" << z->key << "\t height::" << z->height << endl;
  return;
}

void rotate_right(Node** root, Node** x){
  Node* leftnode = (*x)->lhs;
  (*x)->lhs = leftnode->rhs;
  if (leftnode->rhs != NULL)
    leftnode->rhs->p = (*x);
  leftnode->p = (*x)->p;
  if ((*x)->p == NULL)
    (*root) = leftnode;
  else if ((*x) == (*x)->p->lhs)
    (*x)->p->lhs = leftnode;
  else
    (*x)->p->rhs = leftnode;
  leftnode->rhs = (*x);
  (*x)->p = leftnode;
}


void rotate_left(Node** root, Node** x){
  Node* rightnode = (*x)->rhs;
  (*x)->rhs = rightnode->lhs;
  if (rightnode->lhs != NULL)
    rightnode->lhs->p = (*x);
  rightnode->p = (*x)->p;
  if ((*x)->p == NULL)
    (*root) = rightnode;
  else if ((*x) == (*x)->p->lhs)
    (*x)->p->lhs = rightnode;
  else
    (*x)->p->rhs = rightnode;
  rightnode->lhs = (*x);
  (*x)->p = rightnode;
}

void splay(Node** root, Node** x){ //this will turn the BST into a Splay Tree
  while ((*x)->p){  //x->parent isnt null
    if (!((*x)->p->p)){
      if ((*x)->p->lhs == *x){
		Node* temp1 = (*x)->p;
		rotate_right(root, &temp1); //note there may be 2 similar sounding function calls to this name
      }
      else if ((*x)->p->rhs == *x){
		Node* temp2 = (*x)->p;
		rotate_left(root, &temp2);
      }
    }
    else if ((*x)->p->lhs == *x && (*x)->p->p->lhs == (*x)->p){
      Node* temp3 = (*x)->p->p;
      Node* temp4 = (*x)->p;
      rotate_right(root, &temp3);
      rotate_right(root, &temp4);
    }
    else if ((*x)->p->rhs == *x && (*x)->p->p->rhs == (*x)->p){
      Node* temp5 = (*x)->p->p;
      Node* temp6 = (*x)->p;
      rotate_left(root, &temp5);
      rotate_left(root, &temp6);
    }
    else if ((*x)->p->lhs == *x && (*x)->p->p->rhs == (*x)->p){
      Node* temp7 = (*x)->p;
      rotate_right(root, &temp7);
      rotate_left(root, &temp7);
    }
    else{
      Node* temp8 = (*x)->p;
      rotate_left(root, &temp8);
      rotate_right(root, &temp8);
    }
  }
  return;
}

Node* tree_min(Node* x){
  while (x->lhs != NULL)
    x = x->lhs;
  return x;
}

Node* tree_max(Node* x){
  while (x->rhs != NULL)
    x = x->rhs;
  return x;
}

Node* tree_successor(Node* x){
  if (x->rhs != NULL)
    return tree_min(x->rhs);
  Node* y = x->p;
  while (y != NULL || x == y->rhs){
    x = y;
    y = y->p;
  }
  return y;
}

Node* iterative_tree_search(Node* root, int k){
  Node* x = root;
  while (x != NULL && x->key != k){
    if (k < x->key){
      x = x->lhs;
    }
    else if (k > x->key){
      x = x->rhs;
    }
  }
  return x;
}


void tree_print(Node* root, string space){
  if (root == NULL)
    return;
  cout << space << root->key << endl;
  space += "  ";
  tree_print(root->lhs, space);
  tree_print(root->rhs, space);
  return;
}


void inorder_print(Node* root){
  if (root == NULL)
    return;
  cout << root->key << endl;
  inorder_print(root->lhs);
  inorder_print(root->rhs);
  return;
}

void preorder_print(Node* root){  //not bad, not bad at all...
  if (root == NULL)
    return;
  preorder_print(root->lhs);
  cout << root->key << endl;
  preorder_print(root->rhs);
  return;
}

void postorder_print(Node* root){  //THIS IS SO FREAKING EASY!!!
  if (root == NULL)
    return;
  postorder_print(root->rhs);
  cout << root->key << endl;
  postorder_print(root->lhs);
  return;
}

void transplant(Node** root, Node** u, Node** v){
  if ((*u)->p == NULL)
    (*root) = *v;
  else if (*u == (*u)->p->lhs)
    (*u)->p->lhs = *v;
  else
    (*u)->p->rhs = *v;
  if (*v != NULL)
    (*v)->p = (*u)->p;
  return;
}

void tree_delete(Node** root, Node** z){
  if ((*z)->lhs == NULL)
    transplant(root, z, &((*z)->rhs));
  else if ((*z)->rhs == NULL)
    transplant(root, z, &((*z)->lhs));
  else{
    Node* y = tree_min((*z)->rhs);
    if (y->p != *z){
      transplant(root, &y, &(y->rhs));
      y->rhs = (*z)->rhs;
      y->rhs->p = y;
    }
    transplant(root, z, &y);
    y->lhs = (*z)->lhs;
    y->lhs->p = y;
  }
  return;
}

void count_nodes(Node* root, int& counter){ //responsibility of caller to set this
  if (root == NULL)
    return;
  counter++;
  count_nodes(root->lhs, counter);
  count_nodes(root->rhs, counter);
  return;
}

void check_balance(Node* root){
  int lhs, rhs;
  count_nodes(root->lhs, lhs);
  count_nodes(root->rhs, rhs);
  if (rhs != lhs)
    cout << "Nodes are not perfectly balanced from the root node\n";
  else
    cout << "Nodes are perfectly balanced from the root node\n";
  return;
}

void check_lhs_lesser(Node* root){
  if (root == NULL)
    return;
  if (root->lhs != NULL && root->rhs != NULL){
    if (root->lhs > root->rhs){
       cout << "lhs: " << root->lhs->key << " at node " << root->key << " is greater than rhs: " << root->rhs->key << endl;
      check_lhs_lesser(root->lhs);
    }
  }
  return;
}

void check_rhs_lesser(Node* root){
  if (root == NULL)
    return;
  if (root->lhs != NULL && root->rhs != NULL){
    if (root->lhs > root->rhs){
       cout << "rhs: " << root->rhs->key << " at node " << root->key << " is lesser than lhs: " << root->lhs->key << endl;
      check_rhs_lesser(root->rhs);
    }
  }
  return;
}

void kill(Node** root){
  if (*root == NULL)
    return;
  kill(&(*root)->rhs);
  kill(&(*root)->lhs);
  if ((*root)->rhs != NULL){
    delete (*root)->rhs;
    (*root)->rhs = NULL;
  }
  if ((*root)->lhs != NULL){
    delete (*root)->lhs;
    (*root)->lhs = NULL;
  }
  delete (*root);
  (*root) = NULL;
  return;
}


void left_rotate(Node** root, Node** x){  //note!!! assumes right of x isnt nill!!!
  Node* y = (*x)->rhs;  //set y
  (*x)->rhs = y->lhs;  //turn y's left subtree into x's right subtree
  if (y->lhs != NULL)   //can also be pointed to sentinal node for red-black trees
    y->lhs->p = *x;
  y->p = (*x)->p; //link x's parent to y
  if ((*x)->p == NULL)
    (*root) = y;
  else if ((*x) == (*x)->p->lhs)
    (*x)->p->lhs = y;
  else
    (*x)->p->rhs = y;
  y->lhs = (*x);
  (*x)->p = y;
  return;
}

void right_rotate(Node** root, Node** y){  //note!!! assumes right of x isnt nill!!!
  Node* x = (*y)->lhs;  //set y
  (*y)->lhs = x->rhs;  //turn y's left subtree into x's right subtree
  if (x->rhs != NULL)   //can also be pointed to sentinal node for red-black trees
    x->rhs->p = *y;
  x->p = (*y)->p; //link y's parent to x
  if ((*y)->p == NULL)
    (*root) = x;
  else if ((*y) == (*y)->p->rhs)
    (*y)->p->rhs = x;
  else
    (*y)->p->lhs = x;
  x->rhs = (*y);
  (*y)->p = x;
  return;
}

int depth(Node** root){ //compute the depth of the deepest node...
  if ((*root) == NULL)
    return 0;
}

int left_nodes(Node** root, int& left){
  cout << "left: " << left << endl;
  if (*root == NULL)
    return left;
  ++left;
  (*root) = (*root)->lhs;
  left = left_nodes(root, left);
  return left;
}

int right_nodes(Node** root, int& right){
  cout << "right: " << right << endl;
  if (*root == NULL)
    return right;
  ++right;
  (*root) = (*root)->rhs;
  right = right_nodes(root, right);
  return right;
}

int total_nodes(Node** root, int& left, int& right){
  if (root == NULL)
    return 0;
  Node* temp1 = (*root);
  Node* temp2 = (*root);
  right = right_nodes(&temp1, right);
  left = left_nodes(&temp2, left);
  return left+right+1;  //+1 for root node
}

void level_order(Node** root, int level){
  if ((*root) == NULL)
    return;
  if (level == 1){
    cout << (*root)->key << endl;

  }
  else if (level > 1){
    level_order(&(*root)->lhs, level-1);
    level_order(&(*root)->rhs, level-1);
  }
  return;
}

int height(Node* root){// http://www.geeksforgeeks.org/level-order-tree-traversal/
  if (root == NULL)
    return 0;
  else{
    int lheight = height(root->lhs);
    int rheight = height(root->rhs);

    if (lheight > rheight)
      return (lheight+1);
    else
      return (rheight+1);
  }
}

//to count the depth of a node, we always compare the max level recorded to our current level; if it is greater, we incrememt our counter
void level_order_print(Node* root, int alpha){
  alpha = height(root) + 1; //yes this is needed
  for (int d = 0; d < alpha; d++){
    level_order(&root, d);
  }
}

void left_right_nodes(Node** root, int& lefty, int& righty){
  if ((*root) == NULL)
    return;
  left_right_nodes(&(*root)->lhs, ++lefty, righty);
  left_right_nodes(&(*root)->rhs, lefty, ++righty);
  return;
}

int density(Node* root, int& beta){
  if (root == NULL)
    return 0; //base case for recursion
  else{
  cout << "Beta: " << beta << endl;
  ++beta;
  int lheight = density(root->lhs, beta); //only called once per level
  int rheight = density(root->rhs, beta); //same as above

  if (lheight > rheight)
    return (lheight + 1);
  else
    return (rheight +1);
  }
}

float calc_density(Node* root){
	int beta = 0, tempheight = density(root, beta);
  	float density = (float)tempheight/(float)beta;
  	return density;
}

int main(){
  int count = 0;
  Node* root = NULL;

  insert(&root, 5);
  insert(&root, 10);
  insert(&root, 7);
  insert(&root, 6);
  insert(&root, 9);
  insert(&root, 11);
  insert(&root, 1);
  cout << "--Original tree--\n";
  tree_print(root, " ");
  check_lhs_lesser(root);
  check_rhs_lesser(root);

  int alpha = 7;//9 and 10 will kill this
  Node* t = iterative_tree_search(root, alpha);
  if (t != NULL)
    cout << "We found " << alpha << " here!\n";
  cout << "printing...\n";
  tree_print(root, " ");

  cout << "printing...\n";
  tree_print(root, " ");
  count_nodes(root, count = 0);
  cout << "Number of nodes: " << count << endl;

  tree_print(root, " ");
  check_balance(root);
  check_lhs_lesser(root);
  check_rhs_lesser(root);

  count_nodes(root, count = 0);
  cout << "Number of nodes: " << count << endl;

  level_order_print(root, 5);
  float beta = calc_density(root);
  cout << "Testing beta\n" << beta << endl;

  int left = 0, right = 0;
  int total = total_nodes(&root, left, right);

  cout << "Nodes in left: " << left << endl;
  cout << "Nodes in right: " << right<< endl;
  
  cout << total << endl;
}