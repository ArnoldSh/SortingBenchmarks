// sorting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ARRAY_SIZE		10 * 1000
#define E				2.718282
#define Y				0.577216
using namespace std;

const int N = (ARRAY_SIZE);				// size of array
const int L = 50;						// length of random string
int n = N - 1;

const int h[4]		= {9, 5, 3, 1};

int C[8] = {0, 0, 0, 0, 0, 0, 0, 0};	// number of comparisons
int M[8] = {0, 0, 0, 0, 0, 0, 0, 0};	// number of assignments

int C_min[8];	int M_min[8];
int C_avg[8];	int M_avg[8];
int C_max[8];	int M_max[8];

/*
	0 - sortInsert
	1 - sortInsertBin
	2 - sortSelection
	3 - sortBubble
	4 - sortShaker
	5 - sortShall
	6 - sortHeap
	7 - sortQuick
*/

int C_min_theor[8] = {n - 1,				n*(log(n)/log(2) - log(E)/log(2) + 0.5),		(n*n - n)/2,			(n*n - n)/2,	n - 1 };
int C_avg_theor[8] = {(n*n + n - 2)/4,		n*(log(n)/log(2) - log(E)/log(2) + 0.5),		(n*n - n)/2,			(n*n - n)/2,	(n*n - n*(Y + log(n)))/2 };
int C_max_theor[8] = {(n*n + n)/2 - 1,		n*(log(n)/log(2) - log(E)/log(2) + 0.5),		(n*n - n)/2,			(n*n - n)/2,	(n*n - n)/2 };
int M_min_theor[8] = {3*(n - 1),			3*(n - 1),										3*(n - 1),				0,				0 };
int M_avg_theor[8] = {(n*n +9*n - 10)/4,	(n*n +9*n - 10)/4,								n*(log(n) + Y),			(n*n - n)*3/4,	(n*n - n)*3/4 };
int M_max_theor[8] = {(n*n + 3*n - 4)/2,	(n*n + 3*n - 4)/2,								(n*n)/4 + 3*(n - 1),	(n*n - n)*3/2,	(n*n - n)*3/2 };

struct Item {
	int		id;
	char	str[L];
};

Item* sortedArray;
Item* randomArray;
Item* invertArray;

void fillArrays();
void generateItem(Item* );
void sortInsert(Item* );
void sortInsertBin(Item* );
void sortSelect(Item* );
void sortBubble(Item* );
void sortShaker(Item* );
void sortShell(Item* );

void sortInsert(Item* , bool);
void sortInsertBin(Item*, bool);
void sortSelect(Item*, bool);
void sortBubble(Item*, bool);
void sortShaker(Item*, bool);
void sortShell(Item*, bool);

namespace sortheap {
	void sortHeap(Item* );
	void silf(int, int, Item*);
	void sortHeap(Item* , bool);
	void silf(int, int, Item*, bool);
}

namespace sortquick {
	void sortQuick(Item* );
	void sort(int, int, Item*);
	void sortQuick(Item* , bool);
	void sort(int, int, Item*, bool);
}

int _tmain(int argc, _TCHAR* argv[]) {
	sortedArray	= (Item*)calloc(N, sizeof(Item));
	randomArray	= (Item*)calloc(N, sizeof(Item));
	invertArray	= (Item*)calloc(N, sizeof(Item));

	srand((unsigned int)time(0));
	double start, end;
	// ------------------------- WITHOUT TIMING ----------------------------
	
	cout << "-------------- Insertion sort (sorted) ---------------" << endl;
	fillArrays();
	
	sortInsert(sortedArray);
	
	cout << "C_min_theor = " << C_min_theor[0] << " C_min = " << C[0] << endl;
	cout << "M_min_theor = " << M_min_theor[0] << " M_min = " << M[0] << endl;
	
	cout << "-------------- Insertion sort (inverted) ---------------" << endl;
	fillArrays();
	
	sortInsert(invertArray);
	
	cout << "C_max_theor = " << C_max_theor[0] << " C_max = " << C[0] << endl;
	cout << "M_max_theor = " << M_max_theor[0] << " M_max = " << M[0] << endl;
	
	cout << "-------------- Insertion sort (random) ---------------" << endl;
	fillArrays();
	
	sortInsert(randomArray);
	
	cout << "C_avg_theor = " << C_max_theor[0] << " C_avg = " << C[0] << endl;
	cout << "M_avg_theor = " << M_max_theor[0] << " M_avg = " << M[0] << endl;
	
	cout << "-------------- Insertion sort binary (sorted) ---------------" << endl;
	fillArrays();
	
	sortInsertBin(sortedArray);
	
	cout << "C_min_theor = " << C_min_theor[1] << " C_min = " << C[1] << endl;
	cout << "M_min_theor = " << M_min_theor[1] << " M_min = " << M[1] << endl;
	
	cout << "-------------- Insertion sort binary (inverted) ---------------" << endl;
	fillArrays();
	
	sortInsertBin(invertArray);
	
	
	cout << "C_max_theor = " << C_max_theor[1] << " C_max = " << C[1] << endl;
	cout << "M_max_theor = " << M_max_theor[1] << " M_max = " << M[1] << endl;
	
	cout << "-------------- Insertion sort binary (random) ---------------" << endl;
	fillArrays();
	
	sortInsertBin(randomArray);
	
	cout << "C_avg_theor = " << C_max_theor[1] << " C_avg = " << C[1] << endl;
	cout << "M_avg_theor = " << M_max_theor[1] << " M_avg = " << M[1] << endl;
	
	cout << "-------------- Selection sort (sorted) ---------------" << endl;
	fillArrays();
	
	sortSelect(sortedArray);
	
	cout << "C_min_theor = " << C_min_theor[2] << " C_min = " << C[2] << endl;
	cout << "M_min_theor = " << M_min_theor[2] << " M_min = " << M[2] << endl;
	
	cout << "-------------- Selection sort (inverted) ---------------" << endl;
	fillArrays();
	
	sortSelect(invertArray);
	
	cout << "C_max_theor = " << C_max_theor[2] << " C_max = " << C[2] << endl;
	cout << "M_max_theor = " << M_max_theor[2] << " M_max = " << M[2] << endl;
	
	cout << "-------------- Selection sort (random) ---------------" << endl;
	fillArrays();
	
	sortSelect(randomArray);
	
	cout << "C_avg_theor = " << C_max_theor[2] << " C_avg = " << C[2] << endl;
	cout << "M_avg_theor = " << M_max_theor[2] << " M_avg = " << M[2] << endl;
	
	cout << "-------------- Bubble sort (sorted) ---------------" << endl;
	fillArrays();
	
	sortBubble(sortedArray);
	
	cout << "C_min_theor = " << C_min_theor[3] << " C_min = " << C[3] << endl;
	cout << "M_min_theor = " << M_min_theor[3] << " M_min = " << M[3] << endl;
	
	cout << "-------------- Bubble sort (inverted) ---------------" << endl;
	fillArrays();
	
	sortBubble(invertArray);
	
	cout << "C_max_theor = " << C_max_theor[3] << " C_max = " << C[3] << endl;
	cout << "M_max_theor = " << M_max_theor[3] << " M_max = " << M[3] << endl;
	
	cout << "-------------- Bubble sort (random) ---------------" << endl;
	fillArrays();
	
	sortBubble(randomArray);
	
	cout << "C_avg_theor = " << C_max_theor[3] << " C_avg = " << C[3] << endl;
	cout << "M_avg_theor = " << M_max_theor[3] << " M_avg = " << M[3] << endl;
	
	cout << "-------------- Shaker sort (sorted) ---------------" << endl;
	fillArrays();
	
	sortShaker(sortedArray);
	
	cout << "C_min_theor = " << C_min_theor[4] << " C_min = " << C[4] << endl;
	cout << "M_min_theor = " << M_min_theor[4] << " M_min = " << M[4] << endl;
	
	cout << "-------------- Shaker sort (inverted) ---------------" << endl;
	fillArrays();
	
	sortShaker(invertArray);
	
	cout << "C_max_theor = " << C_max_theor[4] << " C_max = " << C[4] << endl;
	cout << "M_max_theor = " << M_max_theor[4] << " M_max = " << M[4] << endl;
	
	cout << "-------------- Shaker sort (random) ---------------" << endl;
	fillArrays();
	
	sortShaker(randomArray);
	
	cout << "C_avg_theor = " << C_max_theor[4] << " C_avg = " << C[4] << endl;
	cout << "M_avg_theor = " << M_max_theor[4] << " M_avg = " << M[4] << endl;
	
	cout << "-------------- Shell sort (sorted) ---------------" << endl;
	fillArrays();
	
	sortShell(sortedArray);
	
	cout << "C_min_theor = " << C_min_theor[5] << " C_min = " << C[5] << endl;
	cout << "M_min_theor = " << M_min_theor[5] << " M_min = " << M[5] << endl;
	
	cout << "-------------- Shell sort (inverted) ---------------" << endl;
	fillArrays();
	
	sortShell(invertArray);
	
	cout << "C_max_theor = " << C_max_theor[5] << " C_max = " << C[5] << endl;
	cout << "M_max_theor = " << M_max_theor[5] << " M_max = " << M[5] << endl;
	
	cout << "-------------- Shell sort (random) ---------------" << endl;
	fillArrays();
	
	sortShell(randomArray);
	
	cout << "C_avg_theor = " << C_max_theor[5] << " C_avg = " << C[5] << endl;
	cout << "M_avg_theor = " << M_max_theor[5] << " M_avg = " << M[5] << endl;
	
	cout << "-------------- Heap sort (sorted) ---------------" << endl;
	fillArrays();
	
	sortheap::sortHeap(sortedArray);
	
	cout << "C_min_theor = " << C_min_theor[6] << " C_min = " << C[6] << endl;
	cout << "M_min_theor = " << M_min_theor[6] << " M_min = " << M[6] << endl;
	
	cout << "-------------- Heap sort (inverted) ---------------" << endl;
	fillArrays();
	
	sortheap::sortHeap(invertArray);
	
	cout << "C_min_theor = " << C_min_theor[6] << " C_min = " << C[6] << endl;
	cout << "M_min_theor = " << M_min_theor[6] << " M_min = " << M[6] << endl;
	
	cout << "-------------- Heap sort (random) ---------------" << endl;
	fillArrays();
	
	sortheap::sortHeap(randomArray);
	
	cout << "C_min_theor = " << C_min_theor[6] << " C_min = " << C[6] << endl;
	cout << "M_min_theor = " << M_min_theor[6] << " M_min = " << M[6] << endl;
	
	cout << "-------------- Quick sort (sorted) ---------------" << endl;
	fillArrays();
	
	sortquick::sortQuick(sortedArray);
	
	cout << "C_min_theor = " << C_min_theor[7] << " C_min = " << C[7] << endl;
	cout << "M_min_theor = " << M_min_theor[7] << " M_min = " << M[7] << endl;
	
	cout << "-------------- Quick sort (inverted) ---------------" << endl;
	fillArrays();
	
	sortquick::sortQuick(invertArray);
	
	cout << "C_min_theor = " << C_min_theor[7] << " C_min = " << C[7] << endl;
	cout << "M_min_theor = " << M_min_theor[7] << " M_min = " << M[7] << endl;
	
	cout << "-------------- Quick sort (random) ---------------" << endl;
	fillArrays();
	
	sortquick::sortQuick(randomArray);
	
	cout << "C_min_theor = " << C_min_theor[7] << " C_min = " << C[7] << endl;
	cout << "M_min_theor = " << M_min_theor[7] << " M_min = " << M[7] << endl;
	
	// ------------------------- WITH TIMING --------------------------------
	cout << "-------------- Insertion sort (sorted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortInsert(sortedArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Insertion sort (inverted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortInsert(invertArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Insertion sort (random) ---------------" << endl;
	fillArrays();
	start = clock();
	sortInsert(randomArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Insertion sort binary (sorted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortInsertBin(sortedArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Insertion sort binary (inverted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortInsertBin(invertArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	start = clock();end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Insertion sort binary (random) ---------------" << endl;
	fillArrays();
	start = clock();
	sortInsertBin(randomArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Selection sort (sorted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortSelect(sortedArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Selection sort (inverted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortSelect(invertArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Selection sort (random) ---------------" << endl;
	fillArrays();
	start = clock();
	sortSelect(randomArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Bubble sort (sorted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortBubble(sortedArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Bubble sort (inverted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortBubble(invertArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Bubble sort (random) ---------------" << endl;
	fillArrays();
	start = clock();
	sortBubble(randomArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Shaker sort (sorted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortShaker(sortedArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Shaker sort (inverted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortShaker(invertArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Shaker sort (random) ---------------" << endl;
	fillArrays();
	start = clock();
	sortShaker(randomArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Shell sort (sorted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortShell(sortedArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	//for(int i = 0; i < N; i++)
		//cout << sortedArray[i].id << endl;
	cout << "-------------- Shell sort (inverted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortShell(invertArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	//for(int i = 0; i < N; i++)
		//cout << sortedArray[i].id << endl;
	cout << "-------------- Shell sort (random) ---------------" << endl;
	fillArrays();
	start = clock();
	sortShell(randomArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	//for(int i = 0; i < N; i++) 
		//cout << sortedArray[i].id << endl;
	
	cout << "-------------- Heap sort (sorted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortheap::sortHeap(sortedArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Heap sort (inverted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortheap::sortHeap(invertArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Heap sort (random) ---------------" << endl;
	fillArrays();
	start = clock();
	sortheap::sortHeap(randomArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Quick sort (sorted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortquick::sortQuick(sortedArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Quick sort (inverted) ---------------" << endl;
	fillArrays();
	start = clock();
	sortquick::sortQuick(invertArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;
	cout << "-------------- Quick sort (random) ---------------" << endl;
	fillArrays();
	start = clock();
	sortquick::sortQuick(randomArray, true);
	end = (clock() - start)/(double)CLOCKS_PER_SEC;
	cout << "Time: " << end << endl;

	delete sortedArray;
	delete invertArray;
	delete randomArray;
	return 0;
}

void generateItem(Item* _item) {
	_item->id = rand();
	for(int i = 0; i < L; i++)
		_item->str[i] = (char)rand()%255; 
}

void fillArrays() {
	Item buffer;
	for(int i = 1; i < N; i++) {
		generateItem(&buffer);
		randomArray[i] = buffer;
		buffer.id = i;
		sortedArray[i] = buffer;
		invertArray[N-i] = buffer;
	}
}

void sortInsert(Item* _array) {
	C[0] = M[0] = 0;
	Item buffer;
	int i,j;
	for(i = 2; i < N; i++) {
		buffer = _array[i];
		_array[0] = buffer;
		j = i - 1;
		M[0] += 1;
		while(buffer.id < _array[j].id) {
			_array[j+1] = _array[j];
			j--;
			C[0]++;		M[0]++;
		}
		C[0]++;	
		_array[j+1] = buffer;
		M[0]++;
	}
}

void sortInsertBin(Item* _array) {
	C[1] = M[1] = 0;
	Item buffer;
	int i,j,l,r,m;
	for(i = 1; i < N; i++) {
		buffer = _array[i];
		M[1]++;
		l = 0;
		r = i - 1;
		while(l <= r) {
			m = (l+r)/2;
			if(buffer.id < _array[m].id) {
				r = m - 1;
			}
			else {
				l = m + 1;
			}
			C[1]++;
		}
		for(j = i - 1; j >= l; j--) {
			_array[j+1] = _array[j];
			M[1]++;
		}
		_array[l] = buffer;
		M[1]++;
	}
}

void sortSelect(Item* _array) {
	C[2] = M[2] = 0;
	Item buffer;
	int i,j,k;
	for(i = 1; i < n; i++) {
		k = i;		buffer = _array[i];
		M[2]++;
		for(j = i + 1; j < N; j++) {
			if(_array[j].id < buffer.id) {
				k = j;		buffer = _array[j];
				M[2]++;
			}
			C[2]++;
		}
		_array[k] = _array[i];		_array[i] = buffer;
		M[2] += 2;
	}
}

void sortBubble(Item* _array) {
	C[3] = M[3] = 0;
	Item buffer;
	int i,j;

	for(i = 1; i < n; i++) {
		for(j = n; j > i; j--) {
			if(_array[j-1].id > _array[j].id) {
				buffer		= _array[j-1];
				_array[j-1] = _array[j];
				_array[j]	= buffer;
				M[3] += 3;	
			}
			C[3]++;
		}
	}
}

void sortShaker(Item* _array) {
	C[4] = M[4] = 0;
	Item buffer;
	int j, k, l, r;
	l = 2; r = n; k = n;
	do {
		for(j = r; j >= l; j--) {
			if(_array[j-1].id > _array[j].id) {
				buffer = _array[j-1];	_array[j-1] = _array[j];
				_array[j] = buffer;		k = j;
				M[4] += 3;
			}
			C[4]++;
		}
		l = k + 1;
		for(j = l; j <= r; j++) {
			if(_array[j-1].id > _array[j].id) {
				buffer = _array[j-1];	_array[j-1] = _array[j];
				_array[j] = buffer;		k = j;
				M[4] += 3;
			}
			C[4]++;
		}
		r = k - 1;
	} while (l <= r);
}

void sortShell(Item* a) {
	C[5] = M[5] = 0;
	Item x;
	Item* b = new Item[h[0] + N];
	int i = 0, j = 0, k = 0, s = 0, m = 0;

	for (i = 0; i < N; i++) {
	 b[i+h[0]] = a[i];
	}
	for (m = 0; m <= 3; m++) {
		k = h[m];
		s = -k - 1;
		for (i = k; i < N; i++) {
			x = b[i + h[0]];
			M[5]++;
			j = i - k;
			if (s == -1) {
				s = -k - 1;
			}
			s++;
			b[s + h[0]] = x;
			M[5]++;
			while (x.id < b[j+h[0]].id) {  
			  b[j + k + h[0]] = b[j + h[0]];
			  M[5]++;
			  j--;
			}
			C[5]++;
			b[j + k + h[0]] = x;
			M[5]++;
		}
	}
	for (i = 0; i < N; i++) {				// copy out
		 a[i] = b[i + h[0]];
	}
	delete [] b;
}

void sortheap::silf(int l, int r, Item* a) {
	int i = 0, j = 0;
	Item x;
	i = l;		
	j = 2*i;
	x = a[i];
	M[6]++;
	while(j <= 2) {
		if(j != r) {
			if(a[j].id < a[j+1].id) { 
				j++;
			}
			C[6]++;
		}
		if(x.id <= a[j].id) {
			break;
		}
		C[6]++;
		a[i] = a[j];
		M[6]++;
		i = j;
		j = 2*i;
	}
	a[i] = x;
	M[6]++;
}

void sortheap::sortHeap(Item* a) {
	M[6] = C[6] = 0;
	Item x;
	int l = N / 2 - 1;
	int r = N - 1;
	while(l > 1) {
		l--;
		silf(l, r, a);
	}
	while (r > 1) {
		x		= a[0]; 
		a[0]	= a[r];
		a[r]	= x;
		M[6] += 3;
		r--;
		silf(l, r, a);
	}
}

void sortquick::sort(int l, int r, Item* a) {
	int i = 0, j = 0;
	Item x, w;

	i = l;
	j = r;
	x = a[(l + r) / 2];
	M[7]++;
	do {
		while(a[i].id < x.id) {
			i++;
			C[7]++;
		}
		C[7]++;
		while(x.id < a[j].id)	{
			j--;
			C[7]++;
		}
		C[7]++;
		if(i <= j) {
			w = a[i];
			a[i] = a[j];
			a[j] = w;
			M[7] += 3;
			i++;
			j--;
		}
	} while(i < j);
	if(l < j)	sortquick::sort(l, j, a);
	if(i < r)	sortquick::sort(i, r, a);
}

void sortquick::sortQuick(Item* a) {
	M[7] = C[7] = 0;
	sortquick::sort(0, N-1, a);
}

// ALGORHITMS WITH TIMING

void sortInsert(Item* _array, bool) {
	Item buffer;
	int i,j;
	for(i = 2; i < N; i++) {
		buffer = _array[i];
		_array[0] = buffer;
		j = i - 1;
		while(buffer.id < _array[j].id) {
			_array[j+1] = _array[j];
			j--;
		}
		_array[j+1] = buffer;
	}
}

void sortInsertBin(Item* _array, bool) {
	Item buffer;
	int i,j,l,r,m;
	for(i = 1; i < N; i++) {
		buffer = _array[i];
		l = 0;
		r = i - 1;
		while(l <= r) {
			m = (l+r)/2;
			if(buffer.id < _array[m].id) {
				r = m - 1;
			}
			else {
				l = m + 1;
			}
		}
		for(j = i - 1; j >= l; j--) {
			_array[j+1] = _array[j];
		}
		_array[l] = buffer;
	}
}

void sortSelect(Item* _array, bool) {
	Item buffer;
	int i,j,k;
	for(i = 1; i < n; i++) {
		k = i;		buffer = _array[i];
		for(j = i + 1; j < N; j++) {
			if(_array[j].id < buffer.id) {
				k = j;		buffer = _array[j];
			}
		}
		_array[k] = _array[i];		_array[i] = buffer;
	}
}

void sortBubble(Item* _array, bool) {
	Item buffer;
	int i,j;

	for(i = 1; i < n; i++) {
		for(j = n; j > i; j--) {
			if(_array[j-1].id > _array[j].id) {
				buffer		= _array[j-1];
				_array[j-1] = _array[j];
				_array[j]	= buffer;
			}
		}
	}
}

void sortShaker(Item* _array, bool) { 
	Item buffer;
	int j, k, l, r;
	l = 2; r = n; k = n;
	do {
		for(j = r; j >= l; j--) {
			if(_array[j-1].id > _array[j].id) {
				buffer = _array[j-1];	_array[j-1] = _array[j];
				_array[j] = buffer;		k = j;
			}
		}
		l = k + 1;
		for(j = l; j <= r; j++) {
			if(_array[j-1].id > _array[j].id) {
				buffer = _array[j-1];	_array[j-1] = _array[j];
				_array[j] = buffer;		k = j;
			}
		}
		r = k - 1;
	} while (l <= r);
}

void sortShell(Item* a, bool) {
	Item x;
	Item* b = new Item[h[0] + N];
	int i = 0, j = 0, k = 0, s = 0, m = 0;

	for (i = 0; i < N; i++) {
	 b[i+h[0]] = a[i];
	}
	for (m = 0; m <= 3; m++) {
		k = h[m];
		s = -k - 1;
		for (i = k; i < N; i++) {
			x = b[i + h[0]];
			j = i - k;
			if (s == -1) {
				s = -k - 1;
			}
			s++;
			b[s + h[0]] = x;
			while (x.id < b[j+h[0]].id) {  
			  b[j + k + h[0]] = b[j + h[0]];
			  j--;
			}
			b[j + k + h[0]] = x;
		}
	}
	for (i = 0; i < N; i++) {				// copy out
		 a[i] = b[i + h[0]];
	}
	delete [] b;
}

void sortheap::silf(int l, int r, Item* a, bool) {
	int i = 0, j = 0;
	Item x;
	i = l;		
	j = 2*i;
	x = a[i];
	while(j <= 2) {
		if(j != r) {
			if(a[j].id < a[j+1].id) { 
				j++;
			}
		}
		if(x.id >= a[j].id) {
			break;
		}
		a[i] = a[j];
		i = j;
		j = 2*i;
	}
	a[i] = x;
}

void sortheap::sortHeap(Item* a, bool) {
	Item x;
	int l = N / 2 - 1;
	int r = N - 1;
	while(l > 1) {
		l--;
		silf(l, r, a);
	}
	while (r > 1) {
		x		= a[0]; 
		a[0]	= a[r];
		a[r]	= x;
		r--;
		silf(l, r, a, true);
	}
}

void sortquick::sort(int l, int r, Item* a, bool) {
	int i = 0, j = 0;
	Item x, w;

	i = l;
	j = r;
	x = a[(l + r) / 2];
	do {
		while(a[i].id < x.id) {
			i++;
		}
		while(x.id < a[j].id)	{
			j--;
		}
		if(i <= j) {
			w = a[i];
			a[i] = a[j];
			a[j] = w;
			i++;
			j--;
		}
	} while(i < j);
	if(l < j)	sortquick::sort(l, j, a, true);
	if(i < r)	sortquick::sort(i, r, a, true);
}

void sortquick::sortQuick(Item* a, bool) {;
	sortquick::sort(0, N-1, a, true);
}