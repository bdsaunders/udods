#include <cmath>
#include <algorithm>
using namespace std;
#include "BinaryHeap.h"

namespace ods {

// functions and data defined in this file
template <typename T> int insert(T *a, int n); // used by insertionSort
template <typename T> void insertionSort(T *a, int n); 
template <typename T> int partition(T *a, int n); // used by all quickSorts
template <typename T> void quickSort1(T *a, int n); // pure quickSort
template <typename T> void quickSort2(T *a, int n); // use a swap
template <typename T> void quickSort_T(T *a, int n); // use insertionSort below Threshold
template <typename T> void heapSort(T *a, int n); // use ods's in BinaryHeap.h
template <typename T> void introspectiveSort(T *a, int n); // quick & ins & heap
template <typename T> void merge(T* a0, int n0, T* a1, int n1, T* a); 
template <typename T> void mergeSort1(T *a, int n); // pure quickSort

int Threshold = 17; // global var for insertionSort threshold ( a hack )

template <typename T>
void quickSort1(T *a, int n) { // sort a[0]..a[n-1] in increasing order.
  if (n <= 1) return;

  swap(a[0], a[rand()%n]); // place random entry in first position
  int i = partition(a, n); // partition based on that entry
  
  quickSort1(a, i); // sort the smaller elts.
  quickSort1(a+i, n-i); // sort the larger elts.
}

template <typename T>
void quickSort2(T *a, int n) { // sort a[0]..a[n-1] in increasing order.
  if (n <= 2) { if (n == 2 and a[1] < a[0]) swap(a[0],a[1]); return; }

  swap(a[0], a[rand()%n]); // place random entry in first position
  int i = partition(a, n); // partition based on that entry
  
  quickSort2(a, i); // sort the smaller elts.
  quickSort2(a+i, n-i); // sort the larger elts.
}

template <typename T>
void quickSort_T(T *a, int n) { // sort a[0]..a[n-1] in increasing order.
  if (n < Threshold) { insertionSort(a, n); return; }

  swap(a[0], a[rand()%n]); // place random entry in first position
  int i = partition(a, n); // partition based on that entry

  quickSort_T(a, i); // sort the smaller elts.
  quickSort_T(a+i, n-i); // sort the larger elts.
}

template <typename T>
int partition(T *a, int n){
  int i = 0, j = n-1;
  // pivot is a[i]
  while (i < j) {
    while (a[i] < a[j]) --j; 
	if (i == j) break;
    swap( a[i], a[j] ); // now pivot is a[j]
    ++i;
    while (a[i] < a[j]) ++i;
    swap( a[i], a[j] ); // now pivot back to a[i]
    --j;
  }
  return i; // location of pivot.
}

template< typename T >
void insertionSort(T *a, int n) { 
  // Sort the array a.  
  // Operator< must be defined for type T (i.e. "a < b" is valid for T a, b).

  for (int i = 1; i < n; ++i)
    insert(a, i);
}

template< typename T >
int insert(T *a, int i) { 
  // Assume a[0..i-1] is sorted. Insert a[i] so that a[0..i] is sorted.
  // Just in case it is of interest, return j such that a[i] ended up at a[j].

  int j = i;
    while(j > 0 and a[j] < a[j-1]) {
      swap(a[j], a[j-1]); 
	  j--;
	}
	return j;
}

template <typename T>
void heapSort(T *a, int n) { // Sort a[0]..a[n-1] in increasing order.
	//cout << "To my surprise, here we are in heap sort, " << n << endl;
	BinaryHeap<T> h;
	// a cluge to use ods heapsort.
	array<T> b(n);
	for (int i = 0; i < n; ++ i) b[i] = a[i];
	h.sort(b);
	for (int i = 0; i < n; ++ i) a[i] = b[i];
}

template <typename T>
void introSort(T *a, int n, int d); //used by introspectiveSort

template <typename T>
void introspectiveSort(T *a, int n){ // Sort a[0]..a[n-1] in increasing order.
	int depth = ceil(2*log2(n));
	introSort(a, n, depth);
}

template <typename T>
void introSort(T *a, int n, int d){ // Sort a[0]..a[n-1] in increasing order.
    if (n < Threshold) { insertionSort(a, n); return; }

	if (d < 1) {/*cout << "heapsort on " << n << endl; */heapSort(a, n); }// avoid deep recursive calls
	// from here it looks like quicksort.

	swap(a[0], a[rand()%n]); // Choose random pivot.
    int i = partition(a, n); // Partition based on that entry

    introSort(a, i, d-1); // sort the smaller elts.
    introSort(a+i, n-i, d-1); // sort the larger elts.
}

template <typename T>
void mergeSort1(T *a, int n) { // sort a[0]..a[n-1] in increasing order.
  if (n <= 1) return;

  T* b = new T[n];
  copy(a, a+n, b);
  int n0 = n/2;
	
  mergeSort1(b, n0); // sort the first half.
  mergeSort1(b+n0, n-n0); // sort the second half.
  merge(b, n0, b+n0, n-n0, a); // merge the results.
  delete b;
}

template<class T>
void merge(T* a0, int n0, T* a1, int n1, T* a){ 
    int i = 0, i0 = 0, i1 = 0;
l1: while (i0 < n0 and i1 < n1) 
        if (compare(a0[i0], a1[i1]) < 0)
            a[i++] = a0[i0++];
        else
            a[i++] = a1[i1++];
l2: if (i0 < n0) 
		copy(a0+i0, a0+n0, a+i);
    else if (i1 < n1) 
		copy(a1+i1, a1+n1, a+i);
}

/* I found no use for the fancier insertionSort's using memmove and binary search
   quickSort was fastest with the plain insertSort for the base case.
   bds 2012Nov
   */
/*
template< typename T >
void insertionSort2(T *a, int n) { 
  for (int i = 1; i < n; ++i)
    insert2(a, i);
}

template< typename T >
void insertionSort3(T *a, int n) { 
  for (int i = 1; i < n; ++i)
    insert3(a, i);
}

// alternate versions of insert //

template< typename T >
int insert2(T *a, int i) { 
  // Assume a[0..i-1] is sorted. Insert a[i] so that a[0..i] is sorted.
  // Just in case it is of interest, return j such that a[i] ended up at a[j].

  T x = a[i];
  int j = i-1;
  while(0 <= j and a[i] < a[j]) { j--; }
  if (0 < j or a[j] < a[i]) j++;
  if (j < i) {
    memmove(a+j+1, a+j, (i-j)*sizeof(T) ); // args are new start, old start, length in bytes.
    a[j] = x;
  }
  return j;
}

// FIXME:  idea is fine, but the binary search has not been verified in detail.
template< typename T >
int insert3(T *a, int i) { 
  // Assume a[0..i-1] is sorted. Insert a[i] so that a[0..i] is sorted.
  // Just in case it is of interest, return j such that a[i] ended up at a[j].

  T x = a[i];
  // binary search for first elt > a[i] in range [l..h].
  int l = 0, h = i; 
  while(h-l > 1) { 
    int k = (l+h)/2;
	if (a[k] < a[i]) l = k;
	else h = k; 
  } 
  int j = (a[l] < a[i] ? h : l);
  if (j < i) {
    memmove( a+j+1, a+j, (i-j)*sizeof(T) );
    a[j] = x;
  }
  return j;
}
*/

} // namespace ods
