#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
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

// Find the inorder successor
struct bst_node *bst_minValueNode(struct bst_node *node) 
{
    struct bst_node *current = node;

    // Find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

  // Deleting a node
struct bst_node *bst_deleteNode(struct bst_node *root, int key) 
{
    // Return if the tree is empty
    if (root == NULL) return root;

    // Find the node to be deleted
    if (key < root->key)
        root->left = bst_deleteNode(root->left, key);
    else if (key > root->key)
        root->right = bst_deleteNode(root->right, key);
    else 
    {
        // If the node is with only one child or no child
        if (root->left == NULL) 
        {
            struct bst_node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) 
        {
            struct bst_node *temp = root->left;
            free(root);
            return temp;
        }

        // If the node has two children
        struct bst_node *temp = bst_minValueNode(root->right);
        
        // Place the inorder successor in position of the node to be deleted
        root->key = temp->key;
    
        // Delete the inorder successor
        root->right = bst_deleteNode(root->right, temp->key);
    }
    return root;
}

// Inorder Traversal; To print
void bst_inorder(struct bst_node *root) 
{
    if (root != NULL) 
    {
        // Traverse left
        bst_inorder(root->left);
        // Traverse root
        cout << root->key << " -> ";
        // Traverse right
        bst_inorder(root->right);
    }
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

// Node with minimum value
avl_node *avl_nodeWithMimumValue(avl_node *node) 
{
    avl_node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

  // Delete a node
avl_node *avl_deleteNode(avl_node *root, int key) 
{
    // Find the node and delete it
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = avl_deleteNode(root->left, key);
    else if (key > root->key)
        root->right = avl_deleteNode(root->right, key);
    else 
    {
        if ((root->left == NULL) || (root->right == NULL)) 
        {
            avl_node *temp = root->left ? root->left : root->right;
            if (temp == NULL) 
            {
                temp = root;
                root = NULL;
            } 
            else
                *root = *temp;
            free(temp);
        } 
        else 
        {
           avl_node *temp = avl_nodeWithMimumValue(root->right);
            root->key = temp->key;
            root->right = avl_deleteNode(root->right, temp->key);
        }
    }
    if (root == NULL)
        return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + avl_max(avl_height(root->left), avl_height(root->right));
    int balanceFactor = avl_getBalanceFactor(root);
    if (balanceFactor > 1) 
    {
        if (avl_getBalanceFactor(root->left) >= 0)
            return avl_rightRotate(root);
        else 
        {
            root->left = avl_leftRotate(root->left);
            return avl_rightRotate(root);
        }
    }
    if (balanceFactor < -1) 
    {
        if (avl_getBalanceFactor(root->right) <= 0)
            return avl_leftRotate(root);
        else 
        {
            root->right = avl_rightRotate(root->right);
            return avl_leftRotate(root);
        }
    }
    return root;
}  

// Print the tree
void print_avltree(avl_node *root, string indent, bool last) 
{
    if (root != nullptr) 
    {
        cout << indent;
        if (last) 
        {
            cout << "R----";
            indent += "   ";
        } 
        else 
        {
            cout << "L----";
            indent += "|  ";
        }

        cout << root->key << endl;
        print_avltree(root->left, indent, false);
        print_avltree(root->right, indent, true);
    }
}

// Red-Black Tree
struct rbt_node 
{
    int data;
    rbt_node *parent;
    rbt_node *left;
    rbt_node *right;
    int color;
};

typedef rbt_node *NodePtr;

class RedBlackTree 
{
    private:
        NodePtr root;
        NodePtr TNULL;
    
    public:
    RedBlackTree() 
    {
        TNULL = new rbt_node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void initializeNULLNode(NodePtr node, NodePtr parent) 
    {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    // Rotation left
    void leftRotate(NodePtr x) 
    {
        NodePtr y = x->right;
        x->right = y->left;

        if (y->left != TNULL) 
            y->left->parent = x;

        y->parent = x->parent;
        if (x->parent == nullptr) 
            this->root = y;
        else if (x == x->parent->left) 
            x->parent->left = y;
        else 
            x->parent->right = y;
        
        y->left = x;
        x->parent = y;
    }

    // Rotation right
    void rightRotate(NodePtr x) 
    {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL) 
            y->right->parent = x;

        y->parent = x->parent;
        if (x->parent == nullptr) 
            this->root = y;
        else if (x == x->parent->right) 
            x->parent->right = y;
        else 
            x->parent->left = y;
        
        y->right = x;
        x->parent = y;
    }

    // For balancing the tree after insertion
    void insertFix(NodePtr k) 
    {
        NodePtr u;
        while (k->parent->color == 1) 
        {
            if (k->parent == k->parent->parent->right) 
            {
                u = k->parent->parent->left;
                if (u->color == 1) 
                {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } 
                else 
                {
                    if (k == k->parent->left) 
                    {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            } 
            else 
            {
                u = k->parent->parent->right;

                if (u->color == 1) 
                {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } 
                else 
                {
                    if (k == k->parent->right) 
                    {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) 
                break;
        }
        root->color = 0;
    }

    // Inserting a node
    void insert(int key) 
    {
        NodePtr node = new rbt_node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL) 
        {
            y = x;
            if (node->data < x->data) 
                x = x->left;
            else 
                x = x->right;
        }

        node->parent = y;
        if (y == nullptr) 
            root = node;
        else if (node->data < y->data) 
            y->left = node;
        else
            y->right = node;

        if (node->parent == nullptr) 
        {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) 
            return;

        insertFix(node);
    }

    // Print RBT
    void printHelper(NodePtr root, string indent, bool last) 
    {
        if (root != TNULL) 
        {
            cout << indent;
            if (last) 
            {
                cout << "R----";
                indent += "   ";
            } 
            else
            {
                cout << "L----";
                indent += "|  ";
            }
    
            string sColor = root->color ? "RED" : "BLACK";
            cout << root->data << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

    void printTree() 
    {
        if (root) 
            printHelper(this->root, "", true);
    }
};

// Functions for recording in file

// Generate random data
vector<int> rand_data(int size) 
{
    vector<int> data(size);
    for (int &val : data) 
        val = rand() % 100000; 
    return data;
}

void rec_to_text(std::string file_name, std::vector<double> &result) 
{
    std::ofstream file(file_name);
    if (!file) 
    {
        std::cout << "Error: Unable to Open File." << std::endl;
        return;
    }
    file << std::fixed << std::setprecision(10);
    for (const auto &results : result)
        file << results << "\n";

    std::cout << "Results have been written to " << file_name << "\n";
    file.close();
}

int main()
{
    // BST test
    // struct bst_node *bst_root = NULL;
    // bst_root = insert_bst(bst_root, 8);
    // bst_root = insert_bst(bst_root, 3);
    // bst_root = insert_bst(bst_root, 1);
    // bst_root = insert_bst(bst_root, 6);
    // bst_root = insert_bst(bst_root, 7);
    // bst_root = insert_bst(bst_root, 10);
    // bst_root = insert_bst(bst_root, 14);
    // bst_root = insert_bst(bst_root, 4);

    // cout << "Binary Search Tree Inorder traversal: ";
    // bst_inorder(bst_root);
    // cout << endl;

    // // Avl Test
    // avl_node *avl_root = NULL;
    // avl_root = insert_avlnode(avl_root, 33);
    // avl_root = insert_avlnode(avl_root, 13);
    // avl_root = insert_avlnode(avl_root, 53);
    // avl_root = insert_avlnode(avl_root, 9);
    // avl_root = insert_avlnode(avl_root, 21);
    // avl_root = insert_avlnode(avl_root, 61);
    // avl_root = insert_avlnode(avl_root, 8);
    // avl_root = insert_avlnode(avl_root, 11);
    // cout << "AVL tree traversal:\n ";
    // print_avltree(avl_root, "", true);
    // cout << endl;

    // // RBT test
    // RedBlackTree test;
    // test.insert(55);
    // test.insert(40);
    // test.insert(65);
    // test.insert(60);
    // test.insert(75);
    // test.insert(57);

    // cout << "Red Black Tree Traversal:\n";
    // test.printTree();
    // cout << endl;

    return 0;
}