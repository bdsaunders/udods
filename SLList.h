/*
 * SLList.h
 *
 *  Created on: 2011-11-25
 *      Author: morin
 *       FIXME: This code is completely untested (but was ported from tested Java code)
 *   2014Feb: fixes and mods by bds
 */

#ifndef SLLIST_H_
#define SLLIST_H_

namespace ods {

template<class T>
class SLList {
protected:

	struct Node {
		T x;
		Node *next;
		Node(T x0) { x = x0; next = NULL; }
	}; // end Node

	Node *head;
	Node *tail;
	int n;

public:
	SLList() { n = 0; head = tail = NULL; }
	~SLList() { clear(); }
	int size() { return n; }
	void clear() {
		Node *u = head;
		for (int i = 0; i < n; ++i) {
			Node *v = u;
			u = u->next;
			delete v;
		}
		head = tail = NULL; n = 0;
	}

	// Stack interface //
	void push(T x0) { // Add at head.
		Node *u = new Node(x0);
		u->next = head;
		head = u;
		if (n == 0)
			tail = u;
		n++;
	}

	T pop() { // Remove at head. Requires n > 0.
		T x0 = head->x;
		Node *u = head;
		head = head->next;
		delete u;
		if (--n == 0) tail = NULL;
		return x0;
	}

	T top() { return head->x; } // requires n > 0.

	bool isEmpty() { return head == NULL; }

	// Queue interface //

	void enqueue(T x0) { // Add at tail
		if (n == 0) {
			head = tail = new Node(x0);
		} else {
			tail->next = new Node(x0);
			tail = tail->next;
		}
		n++;
	}

	T dequeue() { return pop(); } // Remove at head.  Requires n > 0.

	// Deque functions //
	void addFirst(T x) { push(x); }
	void addLast(T x) { enqueue(x); }
	T removeFirst() { return pop(); }
	T removeLast() ; // ugh

	// TODO: provide removeLast, USet interface, maybe List interface
	// (none of those will fast)

	// USet interface
	void add(T x);
	T remove(T x);
	T find(T x);

	// List interface
	void add(int i, T x) ;
	T remove(int i) ;

}; // end class SLList

/* 
Theorem:  The Stack and Queue functions of SLList run in O(1) time.
clear() runs in O(n) time.
*/

} /* namespace ods */
#endif /* SLLIST_H_ */
