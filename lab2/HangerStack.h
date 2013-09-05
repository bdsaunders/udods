/*
 * HangerStack.h  
 *  modified from ArrayStack.h by bds 2013Sept
 *
 *  This includes Cliff Hanger's accounting scheme.
 */

#ifndef HANGERSTACK_H_
#define HANGERSTACK_H_
#include <math.h>
#include <iostream>
using namespace std;

#include "array.h"
//#include "utils.h"

namespace ods {

template<class T>
class HangerStack {
protected:
	array<T> a;
	int n;
	virtual void resize();

////// additional member data to support the resize cost study.
   
    // these two variables affect the effect and frequency of resizing.
    static const float resizeFactor = 2; // ratio of length/n right after a resize()
    static const float resizeShrinkTrigger = 2; // ratio length/n that triggers a resize() when removing.
    // note: fullness  (length/n = 1) triggers resize() in adding operations.

    // these variables are used just verify or disprove that amortization goals are met.
    typedef int CopyCash;
    CopyCash ccs; // copy cash savings
    static const CopyCash ccfa = 2; // copy cash savings to be gained from each add()
    static const CopyCash ccfr = 2; // copy cash savings to be gained from each remove()
    /* Amortization idea:  At each moment when resizing causes copying, 
       the savings are sufficient to pay for it.
    */

public:
	HangerStack();
	virtual ~HangerStack();
	int size();
	T get(int i);
	T set(int i, T x);
	virtual void add(int i, T x);
	virtual void add(T x) { add(size(), x); }
	virtual T remove(int i);
	virtual void clear();
	// Stack interface
	void push(T x) { add(size(), x); }
	void pop() { remove(size()-1); }
	T top() { return a[size()-1]; }
	bool isEmpty() { return size() == 0; }
};

template<class T> inline
int HangerStack<T>::size() {
	return n;
}

template<class T> inline
T HangerStack<T>::get(int i) {
	return a[i];
}

template<class T> inline
T HangerStack<T>::set(int i, T x) {
	T y = a[i];
	a[i] = x;
	return y;
}

template<class T>
void HangerStack<T>::clear() {
	n = 0;
	array<T> b(1);
	a = b;
}

template <class T>
HangerStack<T>::HangerStack() : a(1), n(0), ccs(0) {}

template<class T>
HangerStack<T>::~HangerStack() {
}

template<class T>
void HangerStack<T>::resize() {
	int newLength = max(1, (int)ceil(resizeFactor*n));
	cout << "resizing HangerStack contents ";
	cout << "from " << n << " items in length " << a.length << " array ";
	cout << "to " << n << " items in length " << newLength << " array." << endl;
	if (ccs < n) {
		cout << "    " << ccs << " is NOT ENOUGH SAVINGS to pay for move of ";
		cout << n << " items in resize()!" << endl; 
	} else {
		cout << "    " << ccs << " savings pays for move of ";
		cout << n << " items in resize()!" << endl; 
	} 
	ccs = 0; // we use the savings.  ... could be ccs -= n.
	array<T> b(newLength);
	for (int k = 0; k < n; k++)
		b[k] = a[k];
	a = b;
}

template<class T>
void HangerStack<T>::add(int i, T x) {
	if (n == a.length) resize(); // no room, so double the underlying container
	for (int j = n; j > i; j--) // move stuff out of the way (doesn't happen when adding at the end).
		a[j] = a[j - 1];
	a[i] = x;
	n++;
	ccs += ccfa; // contribute to cost of a future resize()
}

template<class T>
T HangerStack<T>::remove(int i) { // equivalent to remove(n-1).  Function added by -bds 2012sept
    T x = a[i];
	for (int j = i; j < n - 1; j++)// move stuff down (doesn't happen if removing last item).
		a[j] = a[j + 1];
	n--;
	ccs += ccfr; // contribute to cost of a future resize()
    	if (resizeShrinkTrigger*n < a.length) resize();
	return x;
}

} /* namespace ods */

#endif /* HANGERSTACK_H_ */

