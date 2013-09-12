/*
 * SLList.h
 *
 *  Created on: 2011-11-25
 *      Author: morin
 *      FIXME: This code is completely untested (but was ported from tested Java code)
 *      WORKINGONIT.  null removed, test being developed -bds 2013Sept.
 */

#ifndef SLLIST_H_
#define SLLIST_H_
#include <stdlib.h>

namespace ods {

template<class T>
class SLList {
protected:
	class Node {
	public:
		T x;
		Node *next;
		Node(T x0, Node *np = NULL) {
			x = x0;
			next = np;
		}
	};
	Node *head;
	Node *tail;
	int n;

public:

	SLList() {
		n = 0;
		head = tail = NULL;
	}

	virtual ~SLList() {
		Node *u = head;
		while (u != NULL) {
			Node *w = u;
			u = u->next;
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

} /* namespace ods */
#endif /* SLLIST_H_ */
