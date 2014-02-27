/* ArrayStack resize study 
 *      by bds, 2013Sept
 */
#include <iostream>
#include <ctime>
using namespace std;

#include "ArrayStack.h"
#include "FastArrayStack.h"
#include "SLList.h"
using namespace ods;

// Declaration of the function called by main.  It is defined below main.
template<class Stack> void testStack(Stack& S, int n);

int main() {
	srand(time(NULL)); // seed the random number generator.
	int n = 100000; 

	ArrayStack<float> S1;
	cout << "Times for stack operations on ArrayStack" << endl;
	testStack(S1, n);
	cout << endl;

	FastArrayStack<float> S2;
	cout << "Times for stack operations on FastArrayStack" << endl;
	testStack(S2, n);
	cout << endl;

	SLList<float> S3;
	cout << "Times for stack operations on SLList" << endl;
	testStack(S3, n);
}

// Declaration of functions called by testStack. They are defined below testStack.
template<class Stack> int buildUp(Stack & S, int n);
template<class Stack> int takeDown(Stack & S);
template<class Stack> int bubbleAlong(Stack & S, int n);

// Definition of testStack.
template<class Stack>
void testStack(Stack & S, int n){
// Note: the Stack item type must be a numeric type
// because implicit casts from int are used.

	int t0 = bubbleAlong(S, n);
	cout << "time to bubble along near size " << 0 << " is " << t0 << endl;
	S.clear();
	int t1 = buildUp(S, n);
	cout << "time to build up to size " << n << " is " << t1 << endl;
	int t2 = bubbleAlong(S, n);
	cout << "time to bubble along near size " << n << " is " << t2 << endl;
	int m = S.size();
	int t3 = takeDown(S);
	cout << "time to take down from size " << m << " is " << t3 << endl;
}

// Definitions of testStack helper functions.

template<class Stack> int buildUp(Stack & S, int n) {
	int start = clock();
	for (int i = 0; i < n; ++i) 
		S.push(i);
	return clock()-start;
}
	
template<class Stack> int takeDown(Stack & S) {
	int start = clock();
	while (not S.isEmpty())
		S.pop();
	return clock()-start;
}

template<class Stack> int bubbleAlong(Stack & S, int n) {
	int start = clock();
	for (int i = 0; i < n; ++i) 
		if (rand()%2 == 0 and not S.isEmpty())
			S.pop();
		else 
			S.push(i);
	return clock()-start;
}
