// medium list interface test for CISC220 lab3/4.

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

#include "ArrayDeque.h"
#include "DLList.h"
// including _my copy_ of SLList
#include "./SLList.h"
using namespace ods;

template <class FloatList>
bool listTest(){
	FloatList L;
	L.add(0, 3.14);
	L.remove(0);
    L.add(0, 1.62);
	L.add(1, 2.23);
	L.set(1, 2.72);
	bool pass =  (2.72f == L.get(1));
	L.remove(0);
	L.remove(0);
	pass = pass and 0 == L.size();
	return pass;
}

template <class FloatList>
void timedListTest(int n = 10000){
	FloatList L;
	// build up a base.
	for (int i = 0; i < n; ++i) 
		L.add(0, i);
    // measure ops on top of that.
    int start = clock();
	for (int i = 0; i < n; ++i) {
		L.add(0, i);
		L.remove(0);
	}
	int elapsed = clock() - start;
	cout << n << " add/remove at beginning of list of length " << n << " in time " << elapsed << endl;
}

int main() {
	// ArrayDeque
	cout << "ArrayDeque test: " << endl;
	timedListTest<ArrayDeque<float> >();
	if ( listTest<ArrayDeque<float> >() )
		cout << "ArrayDeque passes list interface test" << endl;
	else 
		cout << "ArrayDeque FAILS list interface test" << endl;

	// DLList
	cout << endl << "DLList test: " << endl;
	timedListTest<DLList<float> >();
	if ( listTest<DLList<float> >() )
		cout << "DLList passes list interface test" << endl;
	else 
		cout << "DLList FAILS list interface test" << endl;

	// SLList
	cout << endl << "SLList test: " << endl;
	timedListTest<SLList<float> >();
	if ( listTest<SLList<float> >() )
		cout << "SLList passes list interface test" << endl;
	else 
		cout << "SLList FAILS list interface test" << endl;
}
