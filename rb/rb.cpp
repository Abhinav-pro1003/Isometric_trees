#include "rb.h"
using ptr = RedBlackTree::ptr;

RedBlackTree::RedBlackTree(){}

const ptr RedBlackTree::getRoot() const
{ 
	return root; 
}

ptr RedBlackTree::insert(int data)
{
	ptr newnodePtr = new node(data);
	if (!root) {
		root = newnodePtr;
		root->color = 0; // set root color as black
		return newnodePtr;
	}
	insert(root, newnodePtr);
	return newnodePtr;
}

// auxiliary function to perform RBT insertion of a node
// you may assume start is not nullptr
void RedBlackTree::insert(ptr start, ptr newnodePtr)
{
	// choose direction
	ptr y=start;
	// recurse down the tree
	ptr p = nullptr;
	while(y!=nullptr) {
		p = y;
		if(y->data >= newnodePtr->data) y = y->left;
		else y = y->right;
	}

	if(p->data >= newnodePtr->data) p->left = newnodePtr;
	else p->right = newnodePtr;
	newnodePtr->parent = p;
	
	return;
}

// Credits to Adrian Schneider
void RedBlackTree::printRBT(ptr start, const std::string& prefix, bool isLeftChild) const
{
	if (!start) return;

	std::cout << prefix;
	std::cout << (isLeftChild ? "|--" : "|__" );
	// print the value of the node
	std::cout << start->data << "(" << start->color << ")" << std::endl;
	// enter the next tree level - left and right branch
	printRBT(start->left, prefix + (isLeftChild ? "│   " : "    "), true);
	printRBT(start->right, prefix + (isLeftChild ? "│   " : "    "), false);
}

// Function performing right rotation
// of the passed node
void RedBlackTree::rightrotate(ptr loc)
{
	if(loc==nullptr) return;

	ptr p = loc->parent;
	if(p == nullptr) return;

	p->left = loc->right;
	if(loc->right) (loc->right)->parent = p;

	loc->right = p;
	loc->parent = p->parent;
	if(p->parent) {
        if(p == p->parent->left)
            p->parent->left = loc;
        else
            p->parent->right = loc;
    }
	p->parent = loc;

	if(p==root) root=loc;
	return;
}

// Function performing left rotation
// of the passed node
void RedBlackTree::leftrotate(ptr loc)
{
	if(loc==nullptr) return;

	ptr p = loc->parent;
	if(p == nullptr) return;

	p->right = loc->left;
	if(loc->left) (loc->left)->parent = p;

	loc->left = p;
	loc->parent = p->parent;
	if(p->parent) {
        if(p == p->parent->left)
            p->parent->left = loc;
        else
            p->parent->right = loc;
    }
	p->parent = loc;

	if(p==root) root=loc;
	return;
}

// This function fixes violations
// caused by RBT insertion
void RedBlackTree::fixup(ptr loc)
{
	if(loc==nullptr) return;
	ptr p = loc->parent;
	if(p==nullptr) {
		loc->color = 0;
		return;
	}
	if(loc->color==0 || p->color==0) return;
	ptr gp = p->parent;
	if(gp==nullptr) {
		p->color = 1;
		return;
	}
	if(gp->left == p) {
		ptr u = gp->right;
		if(u==nullptr || u->color==0) {
			if(p->right==loc) {
				leftrotate(loc);
				loc = p;
                p = loc->parent;
			}
			p->color = 0;
			gp->color = 1;
			rightrotate(p);
			return;
		}
		else {
			u->color = 0;
			p->color = 0;
			gp->color = 1;
			fixup(gp);
			return;
		}	
	}
	else {
		ptr u = gp->left;
		if(u==nullptr || u->color==0) {
			if(p->left==loc) {
				rightrotate(loc);
				loc = p;
                p = loc->parent;
			}
			p->color = 0;
			gp->color = 1;
			leftrotate(p);
			return;
		}
		else {
			u->color = 0;
			p->color = 0;
			gp->color = 1;
			fixup(gp);
			return;
		}	
	}
}

// Function to print inorder traversal
// of the fixated tree
void RedBlackTree::inorder(ptr start) const
{
	if (!start)
		return;
	
	inorder(start->left);
	std::cout << start->data << " ";
	inorder(start->right);
}


