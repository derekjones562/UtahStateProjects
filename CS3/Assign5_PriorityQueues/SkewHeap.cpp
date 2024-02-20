#include "SkewHeap.h"

#include "LeftistHeap.h"

SkewHeap::SkewHeap(string name)
{
	this->name = name;
	size=0;
	heap = NULL;
}

void SkewHeap::insert(ItemType &newVal)
{
	
	if(SkewisEmpty())
	{
		PQheap = new Node(newVal);
	}
	else
	{
		SkewHeap secondSkew("temp");
		secondSkew.PQheap = new Node(newVal);
		this->merge(&secondSkew);
	}
	this->size++;
	
}

Node SkewHeap::deleteMax( )
{
	if(SkewisEmpty())
	{
		assert(PQheap);
	}

	Node * ptr = PQheap;
	PQheap = merge(PQheap->left,PQheap->right);
	Node temp= *ptr;
	delete ptr;
	this->size--;
	return temp;
}

void SkewHeap::merge(PQ* second)
{	
	if (second->PQheap==NULL)
		return;
	PQheap=merge(this->PQheap, second->PQheap);
}

Node* SkewHeap::merge(Node *first, Node *second)
{
	if(first == NULL) 
		return second;
	if(second == NULL)
		return first;
	/*is first bigger than second?
	if yes
	firsts right point to the merge of the right and second
	*/
	if(first->element.priority > second->element.priority)
	{
		first->right=merge(first->right, second);
		updateNPL(first);
		return first;
	}
	else
	{
		second->right = merge(second->right, first);
		updateNPL(second);
		return second;
	}
	
	/*propigating back up update null pathlengths and switch everytime to keep
	skew properties
	*/
	
}
void SkewHeap::updateNPL(Node * &head)
{
	if(head->left == NULL)
	{
		head->npl=0;
		if(head->right != NULL)
		{
			head->left= head->right;
			head->right = NULL;
		}
		return;
	}
	if(head->right == NULL)
	{
		head->npl= 0;
		return;
	}
	 //switch every time on the way back up
	
	Node *ptr = head->left;
	head->left = head->right;
	head->right = ptr;
	
	if(head->left->npl > head->right->npl)
		head->npl = head->right->npl + 1;
	else
		head->npl = head->left->npl +1;
}

string SkewHeap::toString(Node * ptr, string indent, int &size) const
{
	
	stringstream ss;
	ss<<"";
	if(size < 0)
		return ss.str();
	if(ptr == NULL)
		return ss.str();
	indent +="   ";
	/*print out top 3 priorities*/
	ss << indent << toString(ptr->right, indent, --size)<<endl;
	ss << indent <<ptr->toString()<<endl;
	ss << indent <<toString(ptr->left, indent, --size)<<endl;
	return ss.str();
} 

string SkewHeap::toString(int size) const
{
	stringstream ss;
	ss << toString(PQheap, "", size);
	return ss.str();
}

bool SkewHeap::SkewisEmpty()
{
	if(PQheap == NULL)
	{
		this->size = 0;
		return true;
	}
	return false;
}


