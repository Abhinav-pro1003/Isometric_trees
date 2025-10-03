#include "two_three_four.h"
// Fill in the missing functions

// -----------------------------
// BigNode constructor
// -----------------------------
BigNode::BigNode()
{
    A = -1;
    B = -1;
    C = -1;
    L = M1 = M2 = R = nullptr;
}
RedBlackTree::RedBlackTree()
{
    root = nullptr;
}

struct node *RedBlackTree::getRoot()
{
    return root;
};

void RedBlackTree::setRoot(node *newroot)
{
    root = newroot;
}

// function to perform RBT insertion of a node
node *RedBlackTree::insert(node *trav,
                           node *temp)
{
    // If the tree is empty,
    // return a new node
    if(trav==nullptr) {
        setRoot(temp);
        return temp;
    }
    // Otherwise recur down the tree
    node* y=trav;
	node* par = nullptr;
	while(y!=nullptr) {
		par = y;
		if(y->d >= temp->d) y = y->l;
		else y = y->r;
	}

	if(par->d >= temp->d) par->l = temp;
	else par->r = temp;
	temp->p = par;
    // Return the (unchanged) node pointer
    return temp;
}

// Helper for pretty printing (internal; not in header)
// Credits to Adrian Schneider
static void printRBTHelper(node *n, const std::string &prefix, bool isLeft)
{
    if (!n)
        return;
    std::cout << prefix;
    std::cout << (isLeft ? "|--" : "|__");
    std::cout << n->d << "(" << (n->c == 0 ? "B" : "R") << ")" << std::endl;
    printRBTHelper(n->l, prefix + (isLeft ? "│   " : "    "), true);
    printRBTHelper(n->r, prefix + (isLeft ? "│   " : "    "), false);
}

void RedBlackTree::printRBT(const std::string &prefix, bool isLeft)
{
    // public wrapper prints from root; ignore args and use root for consistency
    (void)prefix;
    (void)isLeft;
    printRBTHelper(root, "", true);
}

void RedBlackTree::rightrotate(node *temp)
{ // Function performing right rotation of the passed node
    if(temp==nullptr) return;

	node* par = temp->p;
	if(par == nullptr) return;

	par->l = temp->r;
	if(temp->r) (temp->r)->p = par;

	temp->r = par;
	temp->p = par->p;
	if(par->p) {
        if(par == par->p->l)
            par->p->l = temp;
        else
            par->p->r = temp;
    }
	par->p = temp;

	if(par==root) setRoot(temp);
	return;
}

void RedBlackTree::leftrotate(node *temp)
{
    // Function performing left rotation of the passed node
    if(temp==nullptr) return;

	node* par = temp->p;
	if(par == nullptr) return;

	par->r = temp->l;
	if(temp->l) (temp->l)->p = par;

	temp->l = par;
	temp->p = par->p;
	if(par->p) {
        if(par == par->p->l)
            par->p->l = temp;
        else
            par->p->r = temp;
    }
	par->p = temp;

	if(par==root) setRoot(temp);
	return;
}

void RedBlackTree::fixup(node *pt)
{
    // This function fixes violations
    // caused by RBT insertion
    if(pt==nullptr) return;
	node* par = pt->p;
	if(par==nullptr) {
		pt->c = 0;
		return;
	}
	if(pt->c==0 || par->c==0) return;
	node* gp = par->p;
	if(gp==nullptr) {
		par->c = 0;
		return;
	}
	if(gp->l == par) {
		node* u = gp->r;
		if(u==nullptr || u->c==0) {
			if(par->r==pt) {
				leftrotate(pt);
                pt = par;
                par = pt->p;
			}
			par->c = 0;
			gp->c = 1;
			rightrotate(par);
			return;
		}
		else {
			u->c = 0;
			par->c = 0;
			gp->c = 1;
			fixup(gp);
			return;
		}	
	}
	else {
		node* u = gp->l;
		if(u==nullptr || u->c==0) {
			if(par->l==pt) {
				rightrotate(pt);
                pt = par;
                par = pt->p;
			}
			par->c = 0;
			gp->c = 1;
			leftrotate(par);
			return;
		}
		else {
			u->c = 0;
			par->c = 0;
			gp->c = 1;
			fixup(gp);
			return;
		}	
	}
}

void RedBlackTree::inorder(node *trav)
{ // Function to print inorder traversal of the fixated tree, no changes needed here keep it as it is
    if (!trav)
        return;
    inorder(trav->l);
    std::cout << trav->d << " ";
    inorder(trav->r);
}

TwoThreeFourTree::TwoThreeFourTree()
{ // no change needed here
    tree = new RedBlackTree();
}

void TwoThreeFourTree::insert(int key)
{
    // create new node here then insert and then fix
    node* temp = new node;
    temp->d = key;
    temp->c = 1;
    node* t = tree->insert(tree->getRoot(), temp);
    tree->fixup(t);
    return;
}

// just a forward declaration
static BigNode *Convert(node *root);

BigNode *TwoThreeFourTree::convert()
{
    // tree->printRBT("",true);
    // return nullptr;
    return Convert(tree->getRoot());
}

static BigNode *Convert(node *root)
{ // Convert RB to 2-3-4 BigNode structure
    BigNode* ans = new BigNode;
    ans->A = -1;
    ans->B = -1;
    ans->C = -1;

    if(root==nullptr) return ans;
    ans->B = root->d;
    if(root->l) {
        ans->A  = root->l->d;
        ans->L = Convert((root->l)->l);
        ans->M1 = Convert((root->l)->r);
    }
    if(root->r) {
        ans->C  = root->r->d;
        ans->M2 = Convert((root->r)->l);
        ans->R = Convert((root->r)->r);
    }
    return ans;
}

void TTF(BigNode *root)
{
    if (!root)
        return;
    if (root->L)
        TTF(root->L);
    if (root->A != -1)
        std::cout << root->A << " ";
    if (root->M1)
        TTF(root->M1);
    if (root->B != -1)
        std::cout << root->B << " ";
    if (root->M2)
        TTF(root->M2);
    if (root->C != -1)
        std::cout << root->C << " ";
    if (root->R)
        TTF(root->R);

}
