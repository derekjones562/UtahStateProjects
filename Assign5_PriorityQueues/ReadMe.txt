used visual studio 2012 to create and compile. 


a. onAverage insert:

	d-Ary heap: number of compares = 1 while loop that ends after propigating
		to the correct spot(possible of n/KIDS or n) = n;
	Leftist: number of compares = 2 in mergefunction call = 2logn = logn;
	Skew: number of compares = 1 in mergefunction call = logn;

b. onAverage merge:

	d-Ary heap: number of compares = 1 in for loop that ends at the size = n;
	Leftist: number of compares = 1 in recursive function then calls 1 in 
	 	updateNPL = 2logn or just logn;
	Skew: number of compares =1 in recursive function
	 	(doesnt compare in updateNPL because it switches everytime) = logn;

c  onAverage deleteMax:

	d-Ary heap: number of compares = 1 in for loop that ends at number of kids. 
		this for loop is inside a while loop that ends when the right spot is 
		is found(posible of n/Kids or n) = KIDS n/KIDS = n;
	Leftist: number of compares = 2 in mergefunction call = 2logn = logn;
	Skew: number of compares = 1 in mergefunction call = logn;