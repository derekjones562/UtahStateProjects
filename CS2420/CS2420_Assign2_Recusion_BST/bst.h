#include <iostream> 
#include <iomanip> 
#include <string> 
#include <vector> 
#include <algorithm> 
#include <sstream> 
#include <assert.h> 

using namespace std; 



template <class Etype> class TreeNode 
{ 
public: 
	Etype element; 
	TreeNode *left; 
	TreeNode *right; 
	TreeNode *parent; 
	TreeNode(Etype e = 0, TreeNode *l = NULL, TreeNode *r = NULL, TreeNode *p = NULL) : 
		element(e), left(l), right(r), parent(p) { } 
}; 


template <class Etype> class BinarySearchTree 
{ 
protected:
		TreeNode<Etype> *root; 
		bool insert(Etype & x, TreeNode<Etype> * & t, TreeNode<Etype>* p); 
		string toString(TreeNode<Etype> * t, string indent) const; 
		string traverse(TreeNode<Etype> * t) const; 
		TreeNode<Etype> * minimumEle(TreeNode<Etype> * & t); 
		TreeNode<Etype> * maximumEle(TreeNode<Etype> * & t); 
		TreeNode<Etype> * predecessor(TreeNode<Etype> * & t); 
		int nodesInLevel(TreeNode<Etype> * & t, int level); 
		TreeNode<Etype> * findKthInOrder(TreeNode<Etype> * t, int &k); 
		int count(TreeNode<Etype> *t); 
		int width(TreeNode<Etype> * t, int &height); 
		bool isIsomorphic(TreeNode<Etype> *t1, TreeNode<Etype> *t2); 
		bool isQuasiIsomorphic(TreeNode<Etype> *t1, TreeNode<Etype> *t2); 
		TreeNode<Etype> * find(TreeNode<Etype> * curr, Etype value); 
		void makeEmpty(TreeNode<Etype> *&t); 
		int countFringe(TreeNode<Etype> *t) const; 
		TreeNode<Etype>* leastCommonAncestor(TreeNode <Etype>* r, Etype a, Etype b); 
public: 
		TreeNode<Etype>* leastCommonAncestor(Etype a, Etype b)  
		{ 
			//bool b1 = isInTree(root, a);
			//bool b2 = isInTree(root, b);
			//if(b1 == true && b2 == true){
				if (a < b) // order the elements so we know which is smaller
					return leastCommonAncestor(root, a, b); 
				return leastCommonAncestor(root, b, a);
			//}
			//else{
			//	cout<<"one or more elements arent in the tree\n";
			//}
		} 
		void makeTree(vector<Etype> all); 
		Etype predecessor(Etype value) 
		{ 
			TreeNode<Etype> *curr = find(root, value); 
			TreeNode<Etype> * p = predecessor(curr); if (p != NULL) return p->element; else return 0; } BinarySearchTree() : root(NULL) { } TreeNode<Etype> * minimumEle(){ return minimumEle(root); 
		} 
		TreeNode<Etype> * maximumEle(){ return maximumEle(root); } 
		TreeNode<Etype> * successor(){ return minimumEle(); } 
		string toString(string msg = "") const { return msg + "\n" + toString(root, " "); } 
		virtual int insert(Etype & x) { return insert(x, root, NULL); } 
		string traverse(string msg) const { return msg + "\n" + traverse(root); } 
		int nodesInLevel(int level) { return nodesInLevel(root, level); } 
		int findKthInOrder(int k) 
		{ 
			TreeNode<Etype>* t = findKthInOrder(root, k); 
			if (t == NULL) return -999; 
				return t->element; 
		} 
		int count() { return count(root); } 
		int width() { int height=0; return width(root, height); } 
		bool isIsomorphic(BinarySearchTree<Etype> t) { return isIsomorphic(root, t.root); }
		bool isQuasiIsomorphic(BinarySearchTree<Etype> t) { return isQuasiIsomorphic(root, t.root); } 
		TreeNode<Etype> * clone(TreeNode<Etype> *t, TreeNode<Etype> *p) const; 
		void makeEmpty() { makeEmpty(root); } 
		int countFringe() { return countFringe(root); } 
}; 

//Big O for LeastCommonAncestor function
//a=1 b=2 k=0
//a=b^k =  O(n^k log n)
//O(log n)
template <class Etype> 
TreeNode<Etype>* BinarySearchTree<Etype>::leastCommonAncestor(TreeNode < Etype>* r, Etype a, Etype b)
{ 
	if(r==NULL) 
		return NULL; 
	if(a < r->element)
	{
		if(b < r->element)
			return leastCommonAncestor(r->left, a, b);
		else //in the case of b>=r->element
			return r;  
	}
	return leastCommonAncestor(r->right, a, b);
} 

//Big O for isIsomorphic function
//a=2 b=2 k=0
//a>b^k =  O(n^log(base b) a)
//O(n)
template <class Etype> 
bool BinarySearchTree<Etype>::isIsomorphic(TreeNode<Etype>*t1, TreeNode<Etype>*t2) 
{ 
	if(t1 == NULL)
	{
		if(t2== NULL)
			return true;
		else
			return false;
	}
	if(t2 == NULL)
		return false;
	else 
		return (isIsomorphic(t1->left, t2->left) && isIsomorphic(t1->right, t2->right)); 
} 

//Big O for isQuasiIsomorphic function
//a=4 b=2 k=0
//a>b^k =  O(n^log(base b) a)
//O(n^2)
template <class Etype> 
bool BinarySearchTree<Etype>::isQuasiIsomorphic(TreeNode<Etype>*t1, TreeNode<Etype>*t2) 
{ 
	if(t1 == NULL)
	{
		if(t2 == NULL)
			return true;
		else
			return false;
	}
	if(t2 == NULL)
		return false;
	int n1, n2; 
	n1 = numberOfKids(t1);
	n2 = numberOfKids(t2);
	if(n1 != n2)
		return false;
	else
		return ((isQuasiIsomorphic(t1->left, t2->left) && isQuasiIsomorphic(t1->right, t2->right)) || 
				(isQuasiIsomorphic(t1->left, t2->right) && isQuasiIsomorphic(t1->right, t2->left)));
}
/*//Big O for width function
//a=2 b=2 k=0
//a>b^k =  O(n^log(base b) a)
//O(n)*/
//big 0 comment section not accurate due to unfinished function
template <class Etype> 
int BinarySearchTree<Etype>::width(TreeNode<Etype> *t, int &height) //didnt quite get this function to work properly
	//currently spits out garabage
{  
	if(t == NULL)
	{
		height++;
		return 0;
	}
	if(height>0)
	height--;
	int leftW = width(t->left, height);
	int rootW = height;
	if(height>0)
	height--;
	int rightW = width(t->right, height);

	rootW= rootW +  height;
	if(t->parent!=NULL)
	{
		height++;
		rootW++;
	}
	return max(rootW, max(leftW, rightW)); 
} 

//Big O for count function
//a=2 b=2 k=0
//a>b^k =  O(n^log(base b) a)
//O(n)
template <class Etype> 
int BinarySearchTree<Etype>::count(TreeNode<Etype>*t) 
{ 
	if(t==NULL) 
		return 0; 
	return count(t->left)+count(t->right)+1; 
} 

//Big O for findKthInOrder function
//a=2 b=2 k=0
//a>b^k =  O(n^log(base b) a)
//O(n)
template <class Etype> 
TreeNode<Etype> * BinarySearchTree<Etype>::findKthInOrder(TreeNode<Etype>*t, int &k) 
{
	if(t==NULL) 
		return NULL; 
	
	if(t->left!=NULL) 
	{ 
		TreeNode<Etype>* ptr= findKthInOrder(t->left, k); 
		if(ptr==NULL)
		{
			if(--k==0) 
				return t; 
			return findKthInOrder(t->right, k); 
		}
		else 
			return ptr; 
	} 
	else
	{
		k--;
		return findKthInOrder(t->right, k);
	}
} 

//Big O for nodesInLevel function
//a=2 b=2 k=0
//a>b^k =  O(n^log(base b) a)
//O(n)
template <class Etype> 
int BinarySearchTree<Etype>::nodesInLevel(TreeNode<Etype>*&t, int level) 
{ 
	if(t==NULL) 
		return 0; 
	if(level==0) 
		return 1; 
	else 
		return nodesInLevel(t->left, level-1) + nodesInLevel(t->right, level-1);
} 

//Big O for minimumEle function
//a=1 b=2 k=0
//a=b^k =  O(n^k log n)
//O(log n)
template <class Etype> 
TreeNode<Etype> * BinarySearchTree<Etype>::minimumEle(TreeNode<Etype> * & t) 
{ 
	if(t==NULL)
		return NULL;
	if (t->left != NULL) 
		return minimumEle(t->left); 
	return t; 
} 

//Big O for traverse function
//a=2 b=2 k=0
//a>b^k =  O(n^log(base b) a)
//O(n)
template <class Etype> 
string BinarySearchTree<Etype>::traverse(TreeNode<Etype> *t) const 
{ 
	stringstream ss; 
	if (t == NULL) 
		return ""; 
	ss << traverse(t->left); 
	ss << t->element << " "; 
	ss << traverse(t->right);
	return ss.str(); 
} 

//Big O for maximumEle function
//a=1 b=2 k=0
//a=b^k =  O(n^k log n)
//O(log n)
template <class Etype> 
TreeNode<Etype> * BinarySearchTree<Etype>::maximumEle(TreeNode<Etype> * & t) 
{ 
	if(t==NULL)
		return NULL;
	if (t->right != NULL) 
		return maximumEle(t->right); 
	return t; 
} 

//Big O for predecessor function
//depth of tree = Log n for n nodes
//O(log n)
template <class Etype> 
TreeNode<Etype> * BinarySearchTree<Etype>::predecessor(TreeNode<Etype> * & t) 
{ 
	if(t == NULL)
		return NULL;
	if(t->left!=NULL)
		return findMax(t->left);

	TreeNode<Etype> * p = t->parent;
	while(p!=NULL && p->element>t->element)
	{
		p = p->parent;
	}
	return p; 
} 

//Big O for toString function
//a=2 b=2 k=0
//a>b^k =  O(n^log(base b) a)
//O(n)
template <class Etype> 
string BinarySearchTree<Etype>::toString(TreeNode<Etype> *t, string indent) const 
{ 
	if(t == NULL)
		return "";
	indent+="    ";
	string temp = toString(t->right, indent);
	temp+= indent + to_string(t->element)+"("+getParentElementAsString(t->parent)+")\n";
	temp+= toString(t->left, indent);
	return temp; 
} 

// Return true if insertion is successful 
// no Big O (didnt write this function)
template <class Etype> 
bool BinarySearchTree<Etype>::insert(Etype & x, TreeNode<Etype> * & t, TreeNode<Etype> * p) 
{ 
	if (t == NULL) 
	{ 
		// cout << "inserting " << x << endl; 
		t = new TreeNode<Etype>(x, NULL, NULL, p); 
		if (t == NULL) 
			return false; 
		return true; 
	} 
	if (x < t->element) 
		return insert(x, t->left, t);
	if (x > t->element) 
		return insert(x, t->right, t); 
	// cout << "Warning, duplicate ignored " << x << endl; 
	return false; // does not allow duplicate insertions 
} 

// no Big O (didnt write this function)
template <class Etype> 
TreeNode<Etype> * BinarySearchTree<Etype>::find(TreeNode<Etype> * curr, Etype value) 
{ 
	if (curr == NULL) 
		return NULL; 
	if (curr->element == value) 
		return curr; 
	if (value < curr->element) 
		return find(curr->left, value); 
	return find(curr->right, value); 
} 

// no Big O (didnt write this function)
template <class Etype> 
void BinarySearchTree<Etype>::makeTree(vector<Etype> all) 
{ 
	makeEmpty(root); 
	for (unsigned i = 0; i < all.size(); i++) 
		insert(all[i]); 
} 

//Big O for makeEmpty function
//a=2 b=2 k=0
//a>b^k =  O(n^log(base b) a)
//O(n)
template <class Etype> 
void BinarySearchTree<Etype>::makeEmpty(TreeNode<Etype> *&t) 
{ 
	if(t!=NULL) 
	{
		makeEmpty(t->left); 
		makeEmpty(t->right); 
		delete t; 
		t=NULL;
	} 
} 

//no Big O (didnt write this function)
template <class Etype> 
TreeNode<Etype> * BinarySearchTree<Etype>::clone(TreeNode<Etype> *t, TreeNode<Etype> *parent) const 
{ 
	if (t == NULL) 
		return NULL; 
	TreeNode<Etype>* newNode = new TreeNode < Etype > { t->element, NULL, NULL, parent }; 
	newNode->left = clone(t->left, newNode); 
	newNode->right = clone(t->right, newNode); 
	return newNode; 
} 

//Big O for countFringe function
//a=2 b=2 k=0
//a>b^k =  O(n^log(base b) a)
//O(n)
template <class Etype> 
int BinarySearchTree<Etype>::countFringe(TreeNode<Etype> *t) const 
{ 
	if(t==NULL)
		return -999;
	if(t->left == NULL) 
	{ 
		if(t->right==NULL) 
			return 1; 
		else 
			return countFringe(t->right); 
	} 
	else 
	{ 
		if(t->right==NULL) 
			return countFringe(t->left); 
		else 
			return countFringe(t->left) + countFringe(t->right); 
	} 
}

//Big O for numberOfKids function
//O(1) no recursive calls or loops
template <class Etype> 
int numberOfKids(TreeNode<Etype> * t)
{
	if(t==NULL)
		return 0;
	if(t->left==NULL)
	{
		if(t->right == NULL)
			return 0;
		else
			return 1;
	}
	if(t->right == NULL)
		return 1;
	else
		return 2;
}

//Big O for findMax function
//a=1 b=2 k=0
//a=b^k =  O(n^k log n)
//O(log n)
template <class Etype>
TreeNode<Etype> * findMax(TreeNode<Etype>* t)//used to help find the inorder predessor
{
	if(t->right ==NULL)
		return t;
	else
		return findMax(t->right);

}

//Big O for getParentElementAsString function
//O(1) no recursive calls or loops
template <class Etype>
string getParentElementAsString(TreeNode<Etype> * parent)//used in print function
{
	if(parent == NULL)
		return "No Parent";
	return to_string(parent->element);
}

//Big O for isInTree function
//a=2 b=2 k=0
//a>b^k =  O(n^log(base b) a)
//O(n)
template <class Etype>
bool isInTree( TreeNode<Etype> * t, Etype b)
{
	if(t==NULL)
		return false;
	if(t->element == b)
		return true;
	return (isInTree( t->left, b) || isInTree(t->right, b));
}

