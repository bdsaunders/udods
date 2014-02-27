/*
 * SLList.h
 *
 *  Created on: 2011-11-25
 *      Author: morin
<<<<<<< HEAD
 *       FIXME: This code is completely untested (but was ported from tested Java code)
 *   2014Feb: fixes and mods by bds
=======
 *      FIXME: This code is completely untested (but was ported from tested Java code)
 *      WORKINGONIT.  null removed, test being developed -bds 2013Sept.
>>>>>>> 5d9a7da1e5952737457624387dc5fe0ddf74eb98
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
<<<<<<< HEAD
		Node(T x0) { x = x0; next = NULL; }
	}; // end Node

=======
		Node(T x0, Node *np = NULL) {
			x = x0;
			next = np;
		}
	};
>>>>>>> 5d9a7da1e5952737457624387dc5fe0ddf74eb98
	Node *head;
	Node *tail;
	int n;

public:
<<<<<<< HEAD
	SLList() { n = 0; head = tail = NULL; }
	~SLList() { clear(); }
	int size() { return n; }
	void clear() {
=======

	SLList() {
		n = 0;
		head = tail = NULL;
	}

	virtual ~SLList() {
>>>>>>> 5d9a7da1e5952737457624387dc5fe0ddf74eb98
		Node *u = head;
		for (int i = 0; i < n; ++i) {
			Node *v = u;
			u = u->next;
<<<<<<< HEAD
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
=======
			delete w;
		}
	}

	int size() {
		return n;
	}

	T peek() {
		return head->x;
	}

	void add(T x) { // queue name for "add at tail"
		Node *u = new Node(x);
		if (n == 0) {
			head = u;
		} else {
			tail->next = u;
		}
		tail = u;
		n++;
	}

	void push(T x) { // stack name for "add at head"
		head = new Node(x, head);
		n++;
		if (tail == NULL) tail = head;
	}

	void remove() { // queue name for "remove head".  List must be nonempty.
		if (n == 0)	throw 99;
		Node *u = head;
		head = head->next;
		delete u;
		n--;
		if (n == 0) tail = NULL;
	}

	void pop() { // stack name for "remove head".  List must be nonempty.
		remove(); 
	}

};
>>>>>>> 5d9a7da1e5952737457624387dc5fe0ddf74eb98

} /* namespace ods */
#endif /* SLLIST_H_ */
