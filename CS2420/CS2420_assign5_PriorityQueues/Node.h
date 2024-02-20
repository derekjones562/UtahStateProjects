
#ifndef NODE_H
#define NODE_H
class Node
{
  public:
    ItemType element;  // Data element
	int npl;           //  Null Path Length
	int treeSize;      // Number of nodes in tree
    Node *left;        // Left child
    Node *right;       // Right Child
    Node( ItemType e, Node *l = NULL, Node *r = NULL ) : 
        element( e ), left( l ), right( r ) {npl = 0; treeSize=0;}
	virtual string toString() { 
		stringstream out;
		out << element.toString();
		if (left!=NULL) out << "[l:" << left->element.priority<< "]";
		if (right!=NULL) out << "[r:" << right->element.priority<< "]";
		return out.str();
	 }
	virtual string toStringShort() { return element.word;}
};
#endif 