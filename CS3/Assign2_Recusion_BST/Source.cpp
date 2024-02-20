#include "bst.h"
#include <ctime>

using namespace std;

void vectorInitialize(vector<int> &v1, int n1, int n2, int n3, int n4, int n5, int n6, 
					  int n7, int n8, int n9, int n10, int n11, int n12, 
					  int n13, int n14, int n15, int n16, int n17);

int main()
{
	int val = 460;
	const int SIZE = 8;
	BinarySearchTree<int> tree0, tree1, tree2,tree3, tree4,tree5,tree6;
	vector<int> v0;
	vectorInitialize(v0, 25, 10, 60, 55, 45,30, 14, 10, 75, 80, 20, 10, 5, 3, 61,62,63);
	vector<int> v1;
	vectorInitialize(v1,25, 10, 60, 55, 58, 56, 14, 10, 75, 80, 20, 10, 5, 7, 61, 62, 63);
	vector<int> v2,v3,v4,v5,v6;
	srand((int) time(0));
	for (int i = 0; i < SIZE; i++)
	{
		int t = rand() % 100;
		v2.push_back(t);
		v3.push_back(t+rand() % 5);
		v4.push_back(t + 18);
		v5.push_back(100 - t);
	}
	for (int i = 0; i < SIZE*SIZE*SIZE; i++)
	{
		int t = rand() % 2000;
		v6.push_back(t);
	}
	v6.push_back(val);
	tree0.makeTree(v0);
	cout << tree0.toString("Tree 0");
	tree1.makeTree(v1);
	cout << tree1.toString("Tree 1");
	cout << tree1.traverse("Tree 1");
	cout << "Fringe count tree1:" << tree1.countFringe() << endl;
	if(tree1.minimumEle() != NULL)
	cout << "Minimum element of tree 1 is " <<tree1.minimumEle()->element<<endl;
	if(tree1.maximumEle() != NULL)
	cout << "Maximum element of tree 1 is " <<tree1.maximumEle()->element<<endl;
	cout << tree1.traverse("Traversal of tree 1");
	int myLevel = 3;
	cout << "Number nodes at level " << myLevel << " is " << tree1.nodesInLevel(myLevel) << endl;
	myLevel = 5; 
	cout << "Number nodes at level " << myLevel << " is " << tree1.nodesInLevel(myLevel) << endl;
	cout << "Count of tree nodes " << tree1.count() << endl;
	int k = 1; 
	cout << "The" << k <<"th smallest value is  "  << tree1.findKthInOrder(k) << endl;
	k = 7; 
	cout << "The" << k <<"th smallest value is  "  << tree1.findKthInOrder(k) << endl;
	k = 12;

	cout << "The" << k <<"th smallest value is  "  << tree1.findKthInOrder(k) << endl;

  
  cout << "The width of  tree1 is " << tree1.width() << endl;
  tree2.makeTree(v2);
  cout << "The width of  tree2 is " << tree2.width() << endl;
  if (tree1.leastCommonAncestor(7, 15) == NULL)
	  cout << "No Least Common Ancestor\n";
  else
	  cout << "Least Common Ancestor " << tree1.leastCommonAncestor(7, 15)->element << endl;

  tree3.makeTree(v3);
  tree4.makeTree(v4);
  tree5.makeTree(v5);
  tree6.makeTree(v6);
  cout << tree6.traverse("tree6");
  cout << "starting at " << val << endl;
  for (int i = 0; i < 5; i++)
  {
	  val = tree6.predecessor(val);
	  cout << "The next predecessor is " << val << endl;
  }

 cout << tree2.toString("tree2");
 cout << tree3.toString("tree3");
 cout << tree4.toString("tree4");
 cout << tree5.toString("tree5");
 if (tree2.isIsomorphic(tree3)) cout << "Trees 2 and 3 are Isomorphic" << endl;
 if (tree2.isIsomorphic(tree4)) cout << "Trees 2 and 4 are Isomorphic" << endl;
 if (tree3.isIsomorphic(tree4)) cout << "Trees 3 and 4 are Isomorphic" << endl;
 if (tree0.isIsomorphic(tree1)) cout << "Trees 0 and 1 Are Isomorphic" << endl;
 if (tree2.isQuasiIsomorphic(tree3)) cout << "Trees 2 and 3 Are Quasi-Isomorphic" << endl;
 if (tree2.isQuasiIsomorphic(tree5)) cout << "Trees 2 and 5 Are Quasi-Isomorphic" << endl;
 if (tree0.isQuasiIsomorphic(tree1)) cout << "Trees 0 and 1 Are Quasi-Isomorphic" << endl;
 if (tree0.isQuasiIsomorphic(tree5)) cout << "Trees 0 and 5 Are Quasi-Isomorphic" << endl;
 tree1.makeEmpty();
 cout << tree1.toString("Is this tree empty?") << endl;
 
 return 0;
}

//Big O for vectorInitialize function
//O(1) no recursive calls or loops
void vectorInitialize(vector<int> &v1, int n1, int n2, int n3, int n4, int n5, int n6, 
					  int n7, int n8, int n9, int n10, int n11, int n12, 
					  int n13, int n14, int n15, int n16, int n17)
{
	v1.push_back(n1);
	v1.push_back(n2);
	v1.push_back(n3);
	v1.push_back(n4);
	v1.push_back(n5);
	v1.push_back(n6);
	v1.push_back(n7);
	v1.push_back(n8);
	v1.push_back(n9);
	v1.push_back(n10);
	v1.push_back(n11);
	v1.push_back(n12);
	v1.push_back(n13);
	v1.push_back(n14);
	v1.push_back(n15);
	v1.push_back(n16);
	v1.push_back(n17);
};

