/*
 * ArrayDeque.h
 *
 *  Created on: 2011-11-23
 *      Author: morin
 *  Modifications: 2014Feb by Saunders
 */

#ifndef ARRAYDEQUE_H_
#define ARRAYDEQUE_H_

namespace ods {

template<class T>
class ArrayDeque {
protected:
	T *a;
	int length; // capacity (size of allocated memory to which a points.)
	int n; // current stack size
	int j; // current starting point
	/* The current i-th conceptual position (vis a vis the List interface) is 
	   actual location (j + i)%length in a.
    */
	int a_index(int i) { return (j+i)%length; } // clock arithmetic on indices.
public:
	ArrayDeque();
	~ArrayDeque();
	inline int size() { return n; }
	void clear();

	// List interface
	T get(int i); // return item in i-th conceptual position.
	T set(int i, T x); // put x in i-th position, return what was there.
	virtual void add(int i, T x); 
	virtual T remove(int i); // return the removed item

    // add and remove are fast at both ends, slow in the middle.

	// standard Stack interface:
	virtual void push(T x) { add(n, x); }
	virtual void pop() { remove(n-1); } // Requires a nonempty Stack
	T top() { return a[n-1]; } // Requires a nonempty Stack
	bool isEmpty() { return n == 0; }

	// standard Queue interface:
	virtual void enqueue(T x) { add(0, x); }
	virtual T dequeue() { return remove(n-1); }
	
	// Deque interface
	void addLast(T x) { add(n, x); }
	void addFirst(T x) { add(0, x); } 
	T removeLast() { return remove(n-1); } 
	T removeFirst() { return remove(0); }

protected:
	virtual void resize();
}; // end of ArrayDeque class declaration

// definitions of the member functions of ArrayDeque //

template <class T>
ArrayDeque<T>::ArrayDeque() {
	a = NULL;
	length = n = 0;
}

template<class T>
ArrayDeque<T>::~ArrayDeque() {
	delete a;
}

template<class T> inline
T ArrayDeque<T>::get(int i) {
	return a[a_index(i)];
}

template<class T> inline
T ArrayDeque<T>::set(int i, T x) {
	T y = a[a_index(i)];
	a[a_index(i)] = x;
	return y;
}

template<class T>
void ArrayDeque<T>::clear() {
	delete a;
	a = NULL;
	n = length = 0;
}

template<class T>
void ArrayDeque<T>::add(int i, T x) {
	if (n == length) resize();
	for (int k = n; k > i; k--)
		a[a_index(k)] = a[a_index(k - 1)];
	a[a_index(i)] = x;
	++n;
}

template<class T>
T ArrayDeque<T>::remove(int i) {
    T x = a[i];
	if (length >= 3 * n) resize();
	n--;
	for (int j = i; j < n - 1; j++)
		a[a_index(j)] = a[a_index(j + 1)];
	return x;
}

template<class T>
void ArrayDeque<T>::resize() {
	int new_length = ( n == 0 ? 1 : 2*n );
	T * b = new T[new_length];
	for (int i = 0; i < n; i++)
		b[i] = a[a_index(i)];
	delete a;
	a = b;
	length = new_length;
	j = 0;
}

} /* namespace ods */

#endif /* ARRAYDEQUE_H_ */
