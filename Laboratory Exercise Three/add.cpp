#include <iostream>
using namespace std;

// Binary Search Tree
struct bst_node 
{
    int key;
    struct bst_node *left, *right;
};

// Create a node
struct bst_node *bst_newNode(int item) 
{
    struct bst_node *temp = (struct bst_node *)malloc(sizeof(struct bst_node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert for BST
struct bst_node *insert_bst(struct bst_node *node, int key) 
{
    // Return a new node if the tree is empty
    if (node == NULL) return bst_newNode(key);
  
    // Traverse to the right place and insert the node
    if (key < node->key)
      node->left = insert_bst(node->left, key);
    else
      node->right = insert_bst(node->right, key);
  
    return node;
}

// AVL Tree
class avl_node 
{
    public:
        int key;
        avl_node *left;
        avl_node *right;
        int height;
};