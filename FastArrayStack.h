/*
 * FastArrayStack.h
 *
 *  Created on: 2011-11-23
 *      Author: morin
 *  Modifications: 2014Feb by Saunders
 */

#ifndef FASTARRAYSTACK_H_
#define FASTARRAYSTACK_H_
#include "ArrayStack.h"

namespace ods {

template<class T>
class FastArrayStack : public ArrayStack<T> {
protected:
	using ArrayStack<T>::a;
	using ArrayStack<T>::length;
	using ArrayStack<T>::n;
public:
	void add(int i, T x) {
		if (n == length) resize();
		if (i < n) 
			std::copy_backward(a+i, a+n, a+i+1);
		a[i] = x;
		++n;
	}
	T remove(int i) {
   	 T x = a[i];
		if (length >= 3 * n) resize();
		n--;
		if (i < n-1) 
			std::copy(a+i+1, a+n, a+i);
		return x;
	}
protected:
	void resize() {
		length = max(1, 2*n);
		T * b = new T[length];
		std::copy(a, a+n, b);
		delete a;
		a = b;
	}
};
#if 0
protected:
	T *a;
	int length; // capacity (size of allocated memory to which a points.)
	int n; // current stack size
public:
	FastArrayStack() { a = NULL; length = n = 0; }
	~FastArrayStack() { delete a; }
	int size() { return n; }
	void clear() { delete a; a = NULL; length = n = 0; };

	// List interface
	T get(int i) { return a[i]; } 
	T set(int i, T x);
	virtual void add(int i, T x); 
	virtual T remove(int i); // return the removed item

	// standard Stack interface:
	virtual void push(T x) { add(n, x); }
	virtual void pop() { remove(n-1); } // Requires a nonempty Stack
	T top() { return a[n-1]; } // Requires a nonempty Stack
	bool isEmpty() { return n == 0; }
protected:
	virtual void resize();
}; // end of FastArrayStack class declaration


// Definitions of the 4 FastArrayStack member functions that weren't already defined //

template<class T> inline
T FastArrayStack<T>::set(int i, T x) {
	//if (i < 0 or i >= n) throw ListAccessError(i, n);
	T y = a[i];
	a[i] = x;
	return y;
}

template<class T>
void FastArrayStack<T>::add(int i, T x) {
	if (n == length) resize();
	if (i < n) 
		std::copy_backward(a+i, a+n, a+i+1);
	a[i] = x;
	++n;
}

template<class T>
T FastArrayStack<T>::remove(int i) {
    T x = a[i];
	if (length >= 3 * n) resize();
	n--;
	if (i < n-1) 
		std::copy(a+i+1, a+n, a+i);
	//for (int j = i; j < n - 1; j++)
	//	a[j] = a[j + 1];
	return x;
}

template<class T>
void FastArrayStack<T>::resize() {
	length = max(1, 2*n);
	T * b = new T[length];
	std::copy(a, a+n, b);
	//for (int i = 0; i < n; i++)
	//	b[i] = a[i];
	delete a;
	a = b;
}
#endif


} /* namespace ods */

#endif /* FASTARRAYSTACK_H_ */
