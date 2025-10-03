#include "common.h"

// Structure to represent each
// node in a red-black tree
struct node {
	int data; // data
	int color; // 1-red, 0-black
	node* parent; // parent
	node* right; // right-child
	node* left; // left child
    node(int data): data(data), color(1), parent(nullptr), right(nullptr), left(nullptr) {}
};

class RedBlackTree
{
    // global root for the entire tree
    node* root = nullptr;

public:
    typedef node* ptr;

    // Constructor
    RedBlackTree();

    // Helper Update Functions
    const ptr getRoot() const;


    // function to perform BST insertion of a node.
    // returns a pointer to the newly inserted node
    ptr insert(int data);

    // auxiliary function to insert a node
    // start is the root of the tree/subtree in which
    // the node (pointed to my newnodePtr) is to be inserted
    void insert(ptr start, ptr newnodePtr);

    // Credits to Adrian Schneider
    // Function to pretty print the tree
    void printRBT(ptr start, const std::string& prefix="", bool isLeftChild=false) const;

    // Function performing right rotation
    // of the passed node
    void rightrotate(ptr loc);

    // Function performing left rotation
    // of the passed node
    void leftrotate(ptr loc);

    // This function fixes violations
    // caused by BST insertion
    void fixup(ptr loc);

    // Function to print inorder traversal
    // of the fixated tree
    void inorder(ptr start) const;

};