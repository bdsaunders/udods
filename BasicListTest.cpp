#include <iostream>
using namespace std;
#include "SLList.h"
using namespace ods;

bool testGetSet(SLList<char>& L) {
	int n = 5;
	L.clear();
	bool pass = true;

	// test get
	for (int i = 0; i < n; ++i)
		L.push('e' - i);	
	if (L.size() != n) pass = false;;

	for (int i = 0; i < n; ++i)
		if (L.get(i) != 'a'+i) 
			pass = false;
	if (L.size() != n) pass = false; // get should not change size!
	if (not pass) { 
		cout << "error in get" << endl; 
		return false; 
	}

	// test get after a change
	L.pop(); --n;
	for (int i = 0; i < n; ++i)
		if (L.get(i) != 'b'+i) 
			pass = false;
	if (L.size() != n) pass = false;;
	if (not pass) { 
		cout << "error in get after change" << endl; 
		return false; 
	}

	// test set
	for (int i = 0; i < n; ++i)
		L.set(i, '0'+i);
	if (L.size() != n) pass = false; // set should not change size!
	for (int i = 0; i < n; ++i)
		if (L.get(i) != '0'+i) 
			pass = false;
	if (not pass) 
		cout << "error in set" << endl;

	return pass;	
}

int main(){
	SLList<char> L;
	if (testGetSet(L)) 
		cout << "Passed test of get/set part of List interface" << endl;
	else
		cout << "FAILED test of get/set part of List interface" << endl;
}
