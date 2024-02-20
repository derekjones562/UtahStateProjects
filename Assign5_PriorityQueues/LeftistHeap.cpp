#include "LeftistHeap.h"

LeftistHeap::LeftistHeap(string name)
{
	this->name = name;
	size=0;
	heap = NULL;
}

void LeftistHeap::insert(ItemType &newVal)
{
	
	if(leftistisEmpty())
	{
		PQheap = new Node(newVal);
	}
	else
	{
		LeftistHeap secondLeftist("temp");
		secondLeftist.PQheap = new Node(newVal);
		this->merge(&secondLeftist);
	}
	this->size++;
}

Node LeftistHeap::deleteMax( )
{
	if(leftistisEmpty())
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

void LeftistHeap::merge(PQ* second)
{	
	if (second->PQheap==NULL)
		return;
	PQheap=merge(this->PQheap, second->PQheap);
}

Node* LeftistHeap::merge(Node *first, Node *second)
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
	
	/*propigating back up update null pathlengths and switch to keep
	leftist properties
	*/
	
}
void LeftistHeap::updateNPL(Node * &head)
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
	if(head->left->npl < head->right->npl) //switch if left null path length is less than right
	{
		Node *ptr = head->left;
		head->left = head->right;
		head->right = ptr;
	}
	head->npl = head->right->npl + 1;
}

string LeftistHeap::toString(Node * ptr, string indent, int &size) const
{
	stringstream ss;
	ss<<"";
	if(ptr == NULL)
		return ss.str();
	indent +="     ";
	
	ss << toString(ptr->right, indent, --size);
	ss << ptr->toString();
	ss << toString(ptr->left, indent, --size);
	return ss.str();
} 

string LeftistHeap::toString(int size) const
{
	stringstream ss;
	ss << toString(PQheap, "", size);
	return ss.str();
}

bool LeftistHeap::leftistisEmpty()
{
	if(PQheap == NULL)
	{
		this->size = 0;
		return true;
	}
	return false;
}


