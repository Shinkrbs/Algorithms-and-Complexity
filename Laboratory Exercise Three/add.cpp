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

// New node creation
avl_node *new_avlnode(int key) 
{
    avl_node *node = new avl_node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

int avl_max(int a, int b) 
{
    return (a > b) ? a : b;
}

// Calculate height
int avl_height(avl_node *N) 
{
    if (N == NULL)
        return 0;
    return N->height;
}

// Get the balance factor of each node
int avl_getBalanceFactor(avl_node *N) 
{
    if (N == NULL)
        return 0;
    return avl_height(N->left) - avl_height(N->right);
}

// Rotate right
avl_node *avl_rightRotate(avl_node *y) 
{
    avl_node *x = y->left;
    avl_node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = avl_max(avl_height(y->left), avl_height(y->right)) + 1;
    x->height = avl_max(avl_height(x->left), avl_height(x->right)) + 1;
    return x;
}

// Rotate left
avl_node *avl_leftRotate(avl_node *x) 
{
    avl_node *y = x->right;
    avl_node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = avl_max(avl_height(x->left), avl_height(x->right)) + 1;
    y->height = avl_max(avl_height(y->left), avl_height(y->right)) + 1;
    return y;
}

// Insert a node
avl_node *insert_avlnode(avl_node *node, int key) 
{
    // Find the correct postion and insert the node
    if (node == NULL)
        return (new_avlnode(key));
    if (key < node->key)
        node->left = insert_avlnode(node->left, key);
    else if (key > node->key)
        node->right = insert_avlnode(node->right, key);
    else
        return node;
        
    // Update the balance factor of each node and
    // balance the tree
    node->height = 1 + avl_max(avl_height(node->left), avl_height(node->right));
    int balanceFactor = avl_getBalanceFactor(node);

    if (balanceFactor > 1) 
    {
        if (key < node->left->key) 
            return avl_rightRotate(node);

        else if (key > node->left->key) 
        {
            node->left = avl_leftRotate(node->left);
            return avl_rightRotate(node);
        }
    }
    if (balanceFactor < -1) 
    {
        if (key > node->right->key) 
            return avl_leftRotate(node);
        else if (key < node->right->key) 
        {
            node->right = avl_rightRotate(node->right);
            return avl_leftRotate(node);
        }
    }
    return node;
}