// basic list interface test for CISC220 lab3.

#include <iostream>
#include <string>
using namespace std;

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
	float x = L.get(1);
	return ( 2.72 == L.get(1) and 2 == L.size() );
}

int main() {
	if ( listTest<SLList<float> >() )
		cout << "SLList passes basic list interface test" << endl;
	else 
		cout << "SLList FAILS basic list interface test" << endl;
}
