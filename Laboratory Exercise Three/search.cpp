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

// Search for BST
struct bst_node* bst_search(struct bst_node* root, int key) 
{
    if (root == NULL || root->key == key)
        return root;  
    if (key < root->key)
        return bst_search(root->left, key); 

    return bst_search(root->right, key);  
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

// Search for AVL 
avl_node* avl_search(avl_node* root, int key) 
{
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return avl_search(root->left, key); 

    return avl_search(root->right, key); 
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

    public:
    NodePtr getTNULL() 
    { 
        return TNULL; 
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

    // Search for Red-Black Trees
    NodePtr searchTreeHelper(NodePtr node, int key) 
    {
        if (node == TNULL || key == node->data) 
            return node;
        if (key < node->data) 
            return searchTreeHelper(node->left, key);

        return searchTreeHelper(node->right, key);
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

    NodePtr rbt_search(int k) 
    {
        return searchTreeHelper(this->root, k);
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

// Generate random data
vector<int> rand_data(int size) 
{
    vector<int> data(size);
    for (int &val : data) 
        val = rand() % 100000; 
    return data;
}

// Functions for recording in file
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
    // // BST test
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

    // if (bst_search(bst_root, 9))
    //     cout << "BST: found in the tree.\n";
    // else
    //     cout << "BST: not found in the tree.\n";

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

    // if (avl_search(avl_root, 6))
    //     cout << "AVL: found in the tree.\n";
    // else
    //     cout << "AVL: not found in the tree.\n";

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

    // NodePtr result = test.rbt_search(100);
    // if (result == test.getTNULL()) 
    //     cout << "Key not found!" << endl;
    // else
    //     cout << "Found key: " << result->data << endl;

    // Array sizes to test
    vector<int> sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    vector<double> result_bst, result_avl, result_rbt;
    bst_node *bst_root = nullptr;
    avl_node *avl_root = nullptr;
    RedBlackTree rbt;
    
    // Perform Insertion
    for (int size : sizes) 
    {
        vector<int> data = rand_data(size);
        
        // BST insertion

        for (int val : data) 
            bst_root = insert_bst(bst_root, val);

        // AVL insertion
        for (int val : data) 
            avl_root = insert_avlnode(avl_root, val);

        // RBT insertion
        for (int val : data) 
            rbt.insert(val);
    }

    // Perform Searching 
    for (int size : sizes) 
    {
        vector<int> search_data = rand_data(size);
        
        // BST search
        auto start = chrono::high_resolution_clock::now();
        for (int val : search_data) 
            bst_search(bst_root, val);
        
        auto end = chrono::high_resolution_clock::now();
        result_bst.push_back(chrono::duration<double, milli>(end - start).count());

        // AVL search
        start = chrono::high_resolution_clock::now();
        for (int val : search_data) 
            avl_search(avl_root, val);
        
        end = chrono::high_resolution_clock::now();
        result_avl.push_back(chrono::duration<double, milli>(end - start).count());

        // RBT search
        start = chrono::high_resolution_clock::now();
        for (int val : search_data) 
            rbt.rbt_search(val);
        
        end = chrono::high_resolution_clock::now();
        result_rbt.push_back(chrono::duration<double, milli>(end - start).count());
    }

    rec_to_text("BSTSearchingTimes.txt", result_bst);
    rec_to_text("AVLSearchingTimes.txt", result_avl);
    rec_to_text("RBTSearchingTimes.txt", result_rbt);
    return 0;
}