/*
 * ArrayStack.h
 *
 *  Created on: 2011-11-23
 *      Author: morin
 *  Modifications: 2014Feb by Saunders
 */

#ifndef ARRAYSTACK_H_
#define ARRAYSTACK_H_

namespace ods {

template<class T>
class ArrayStack {
protected:
	T *a;
	int length; // capacity (size of allocated memory to which a points.)
	int n; // current stack size
public:
	ArrayStack() { a = NULL; length = n = 0; }
	~ArrayStack() { delete a; }
	int size() { return n; }
	void clear() { delete a; a = NULL; length = n = 0; };

	// List interface
	T get(int i) { return a[i]; } 
	T set(int i, T x);
	virtual void add(int i, T x); 
	virtual T remove(int i); // return the removed item

	// standard Stack interface:
	void push(T x) { add(n, x); }
	void pop() { remove(n-1); } // Requires a nonempty Stack
	T top() { return a[n-1]; } // Requires a nonempty Stack
	bool isEmpty() { return n == 0; }
protected:
	virtual void resize();
}; // end of ArrayStack class declaration


// Definitions of the 4 ArrayStack member functions that weren't already defined //

template<class T> inline
T ArrayStack<T>::set(int i, T x) {
	//if (i < 0 or i >= n) throw ListAccessError(i, n);
	T y = a[i];
	a[i] = x;
	return y;
}

template<class T>
void ArrayStack<T>::add(int i, T x) {
	if (n == length) resize();
	for (int j = n; j > i; j--)
		a[j] = a[j - 1];
	a[i] = x;
	++n;
}

template<class T>
T ArrayStack<T>::remove(int i) {
    T x = a[i];
	if (length >= 3 * n) resize();
	n--;
	for (int j = i; j < n - 1; j++)
		a[j] = a[j + 1];
	return x;
}

template<class T>
void ArrayStack<T>::resize() {
	length = max(1, 2*n);
	T * b = new T[length];
	for (int i = 0; i < n; i++)
		b[i] = a[i];
	delete a;
	a = b;
}

} /* namespace ods */

#endif /* ARRAYSTACK_H_ */
