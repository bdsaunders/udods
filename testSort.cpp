#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>
using namespace std;
#include "Sorters.h"
#include "array.h"
using namespace ods;

template <typename T> bool isSorted(T *a, int n){ // A sanity check.
	// Return (n < 2) ? true : ( a[n-2] <= a[n-1] and isSorted(a, n-1) );
	for (int i = 1; i < n; ++i)
		if (a[i-1] > a[i]) return false;
	return true;
}

class Test{
public:
	ods::array<int> A;
	ods::array<int> B;
	Test(int n = 1000000): A(n), B(n) {
		for (int i = 0; i < n; ++i) A[i] = rand();
	} 
	void operator() (string name, void (* sorter) (int*, int), int m) 
{
    // sort m items n/m times, where n = 10^6.  m should be a divisor of n.
		int n = A.length;
	    copy(&(A[0]), &(A[0])+n, &(B[0]));
	    int start, elapsed;

		cout << name << ", array size  " << m << ", done " << n/m << " times: ";
    	start = clock();
    	for (int k = 0; k < n; k += m)
			// sort the length m array starting at the k-th position.
    		(*sorter)(&B[0] + k, m); 
    	elapsed = clock() - start;
		cout << elapsed << " clock ticks" << endl;
		if (not isSorted(&B[0], m)) cout << "SORT FAILURE" << endl;
	}
};

void suiteQ1() {
	Test test;
	test("quickSort1", quickSort1<int>, 10);
	test("quickSort1", quickSort1<int>, 100);
	test("quickSort1", quickSort1<int>, 1000);
	test("quickSort1", quickSort1<int>, 10000);
	test("quickSort1", quickSort1<int>, 100000);
	test("quickSort1", quickSort1<int>, 1000000);
}

void suiteQ2() {
	Test test;
	test("quickSort2", quickSort2<int>, 10);
	test("quickSort2", quickSort2<int>, 100);
	test("quickSort2", quickSort2<int>, 1000);
	test("quickSort2", quickSort2<int>, 10000);
	test("quickSort2", quickSort2<int>, 100000);
	test("quickSort2", quickSort2<int>, 1000000);
}

void suite_ins() {
	Test test;
	test("insertionSort", insertionSort<int>, 10);
	test("insertionSort", insertionSort<int>, 100);
	test("insertionSort", insertionSort<int>, 1000);
	test("insertionSort", insertionSort<int>, 10000);
}

void suiteQT() {
	Test test;
	test("quickSort_T", quickSort_T<int>, 10);
	test("quickSort_T", quickSort_T<int>, 100);
	test("quickSort_T", quickSort_T<int>, 1000);
	test("quickSort_T", quickSort_T<int>, 10000);
	test("quickSort_T", quickSort_T<int>, 100000);
	test("quickSort_T", quickSort_T<int>, 1000000);
}

void suiteM1() {
	Test test;
	test("mergeSort1", mergeSort1<int>, 10);
	test("mergeSort1", mergeSort1<int>, 100);
	test("mergeSort1", mergeSort1<int>, 1000);
	test("mergeSort1", mergeSort1<int>, 10000);
	test("mergeSort1", mergeSort1<int>, 100000);
	test("mergeSort1", mergeSort1<int>, 1000000);
}

void suiteH() {
	Test test;
	test("heapSort", heapSort<int>, 10);
	test("heapSort", heapSort<int>, 100);
	test("heapSort", heapSort<int>, 1000);
	test("heapSort", heapSort<int>, 10000);
	test("heapSort", heapSort<int>, 100000);
	test("heapSort", heapSort<int>, 1000000);
}

void suiteI() {
	Test test;
	test("introspectiveSort", introspectiveSort<int>, 10);
	test("introspectiveSort", introspectiveSort<int>, 100);
	test("introspectiveSort", introspectiveSort<int>, 1000);
	test("introspectiveSort", introspectiveSort<int>, 10000);
	test("introspectiveSort", introspectiveSort<int>, 100000);
	test("introspectiveSort", introspectiveSort<int>, 1000000);
}

void suiteMQHi1(int n) {
	Test test;
	test("mergeSort1", mergeSort1<int>, n);
	test("quickSort1", quickSort1<int>, n);
	test("heapSort", heapSort<int>, n);
    if (n <= 10000)
	    test("insertionSort", insertionSort<int>, n);
}

void suiteQHi2(int n) {
	Test test;
	test("quickSort1", quickSort1<int>, n);
	test("quickSort2", quickSort2<int>, n);
	test("heapSort", heapSort<int>, n);
    if (n <= 10000)
	    test("insertionSort", insertionSort<int>, n);
}

void suiteQHI(int n) {
	Test test;
	test("quickSort_T", quickSort_T<int>, n);
	test("heapSort", heapSort<int>, n);
	test("introspectiveSort", introspectiveSort<int>, n);
}
int main(int ac, char* av[]) {
	srand(time(NULL)); // seed the random number generator.

  if (ac < 2 or av[1][0] == '0') { // run with and without -O3.
	suiteMQHi1(100); cout << endl;
	suiteMQHi1(10000); cout << endl;
	suiteMQHi1(1000000); cout << endl;
  }
  if (ac >= 2 and av[1][0] == '1') { // quick improvement
	suiteQ1(); cout << endl;
	suiteQ2(); cout << endl;
	suite_ins(); cout << endl;
  }
  if (ac >= 2 and av[1][0] == '2') { // more quick improvement
	suiteQ1(); cout << endl;
	suiteQ2(); cout << endl;
	suite_ins(); cout << endl;
	suiteQT(); cout << endl;
  }
  if (ac >= 2 and av[1][0] == '3') { // final
	suiteQT(); cout << endl;
	suiteH(); cout << endl;
	suiteI(); cout << endl;
	suiteQHI(1000000); cout << endl;
  }
}
