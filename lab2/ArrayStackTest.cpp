/* ArrayStack resize study 
 *      by bds, 2013Sept
 */
#include <iostream>
using namespace std;

#include "ArrayStack.h"
#include "HangerStack.h"
using namespace ods;

template<class Stack>
void testStack(Stack S, string title){

	for (int i = 0; i < 100; ++i) // build to 100
		S.push(i+1);
	for (int i = 0; i < 99; ++i) // raze to 1
		S.pop();
	for (int i = 0; i < 128; ++i) // build to 129
		S.push(2*i+1);
	for (int i = 0; i < 129; ++i) // raze to 0
		S.pop();
	if (S.isEmpty())
		cout << "done using " << title << " -- stack is empty (after two build up and take down cycles)" << endl;
	else
		cout << "problem using " << title << " -- stack not empty at end" << endl;
}

int main() {
	ArrayStack<float> S1;
	testStack(S1, "ArrayStack");
	HangerStack<float> S2;
	testStack(S2, "HangerStack");
}


