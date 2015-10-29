#include "PQHeap.h"
#include <time.h>
#include "SkewHeap.h"
#include "LeftistHeap.h"

//Insert limit elements of the file fin into heap.
void insertNext(PQ & pq,ifstream & fin,int limit=0) 
{	if (limit ==0) 
		limit = numeric_limits<int>::max();
	string word;
	int ct;
	while (!fin.eof() && pq.size < limit ){
		fin >> word >> ct;
		pq.insert(ItemType(word,ct));
	}
}

int main()
{   clock_t start = clock();
	int const DELETE_CT=4;
	int const PRINTSIZE=5;
	int const HOWMANY = 10;  // How many values to read from each file.  If HOWMANY = 0, read all values.
	// SkewHeap pq1("SkewHeap PQ1");
	// LeftistHeap pq1("Leftist PQ1");
	PQHeap pq1("Heap PQ1",6000);
	PQHeap pq2("Heap PQ2",6000);
	PQHeap pq3("Heap PQ3",6000);
	PQHeap pq4("Heap PQ4",6000);
	PQHeap pq5("Heap PQ5",6000);
	PQHeap pq6("Heap PQ6",6000);
/*	SkewHeap pq1("SkewHeap PQ1");
	SkewHeap pq2("SkewHeap PQ2");
	SkewHeap pq3("SkewHeap PQ3");
	SkewHeap pq4("SkewHeap PQ4");
	SkewHeap pq5("SkewHeap PQ5");
	SkewHeap pq6("SkewHeap PQ6");*/
/*	LeftistHeap pq1("LeftistHeap PQ1");
	LeftistHeap pq2("LeftistHeap PQ2");
	LeftistHeap pq3("LeftistHeap PQ3");
	LeftistHeap pq4("LeftistHeap PQ4");
	LeftistHeap pq5("LeftistHeapPQ5");
	LeftistHeap pq6("LeftistHeapPQ6");
*/	
	ifstream fin;
	fin.open("Prog5In.txt");
	assert(fin);

	insertNext(pq1,fin,HOWMANY);
	insertNext(pq2,fin,HOWMANY);
	insertNext(pq3,fin,HOWMANY);
	insertNext(pq4,fin,HOWMANY);
	insertNext(pq5,fin,HOWMANY);
	insertNext(pq6,fin);
/**/	
	cout << pq1.toString(PRINTSIZE);
	ofstream fout;
	fout.open("prog5out.txt");
	cout <<  pq1.toString(PRINTSIZE);

	for (int ct=0; ct < DELETE_CT && !pq1.isEmpty(); ct++){//when testing leftist heaps use function leftistisEmpty() instead of isEmpty()
		Node big = pq1.deleteMax();
		fout  << " ** DELETED " << big.toString() << endl;
		cout << " ** DELETED " <<big.toString() << endl;  
		cout << pq1.toString(PRINTSIZE);
	};
	for (int ct=0; ct < DELETE_CT && !pq2.isEmpty(); ct++) {//when testing leftist heaps use function leftistisEmpty() instead of isEmpty()
		Node big = pq2.deleteMax();
		fout  << " ** DELETED " <<big.toString() << endl;
		cout  << " ** DELETED " <<big.toString() << endl;
	};
	cout << "Before merge \n" << pq1.toString(PRINTSIZE) << endl;
	fout << "Before merge \n" <<pq1.toString(PRINTSIZE)<< endl;
	cout << "Before merge \n"<< pq2.toString(PRINTSIZE)<< endl;
	fout << "Before merge \n" <<pq2.toString(PRINTSIZE)<< endl;

	pq1.merge(&pq2);

	cout << "After merge \n" << pq1.toString(PRINTSIZE) << endl;
	fout << "After merge \n" <<pq1.toString(PRINTSIZE)<< endl;
	cout << "After merge \n"<< pq2.toString(PRINTSIZE)<< endl;
	fout << "After merge \n" <<pq2.toString(PRINTSIZE)<< endl;
	pq3.merge(&pq4);
	cout << "After merge 3 and 4 \n" <<pq3.toString(PRINTSIZE)<< endl;
	pq5.merge(&pq6);
	cout << "After merge 5 and 6 \n" <<pq5.toString(PRINTSIZE)<< endl;
	pq1.merge(&pq3);
	cout << "After merge 1 and 3\n" <<pq1.toString(PRINTSIZE)<< endl;
	pq1.merge(&pq5);
	cout << "After merge 1 and 5\n" <<pq1.toString(PRINTSIZE)<< endl;
/**/	clock_t time = clock()-start;
	cout << "Elapsed time = " << ((float) time)/CLOCKS_PER_SEC << endl;
	fout << "Elapsed time = " << ((float) time)/CLOCKS_PER_SEC << endl;
	fout.close();
}


