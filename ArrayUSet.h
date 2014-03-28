/*
 * ArrayUSet.h
 *
 * Evolved from ArrayStack.h * 2014Mar by Saunders
 * Dynamic array just like ArrayStack, but has the USet interface: 
 * find(x), add(x), remove(x).
 */

#ifndef ARRAYUSET_H_
#define ARRAYUSET_H_
#include <cstdlib>
using namespace std;

namespace ods {

template<class T>
class ArrayUSet {
protected:
    T *a;
    int length; // capacity (size of allocated memory to which a points.)
    int n; // current stack size
    T null;
public:
    ArrayUSet(T nullItem = T()) { init(nullItem); }
    void init(T nullItem = T()) {
        a = 0;// NULL pointer initially
    //std::cout << "ArrayUSet init " << (long)a << " foob " << this << std::endl;
        length = n = 0;
        null = nullItem;
    }
    ~ArrayUSet() { clear(); }
    int size() { return n; }
    void clear() { //std::cout << "ArrayUSet clear " << (long)a << " foob" << std::endl; if (a != 0) 
        delete a; length = n = 0;
    }

    // USet interface
    bool add(T x); /* Add x.  
        Don't add it and return false if an item equal to x is already present. 
        */
    T remove(T x); /* Remove and return the item equal to x, 
        Return null if there is no equal item.
        */
    T find(T x); // Return the item equal to x or null if there is no such item.

    T random() { // Return (and don't remove) a random item from the set.
        return a[rand()%n];
    }

    // the part of the list interface we can do fast.
    T get(int i) { return a[i]; }
    void set(int i, T x) { a[i] = x; }

protected:
    void resize(int copynum);
    int findIndex(T x) {
        // Return index i in range 0..n-1 such that a[i] equals x.
        // But if no entry equals x, return n.
        int ans;
        for (ans = 0; ans < n and a[ans] != x; ++ans);
        return ans;
    }
}; // end of ArrayUSet class declaration


// Definitions of the ArrayUSet member functions that weren't already defined //

template<class T> inline
T ArrayUSet<T>::find(T x) {
    int i = findIndex(x);
    if (i == n) return null;
    else return a[i];
}

template<class T> inline
bool ArrayUSet<T>::add(T x) {
    int i = findIndex(x);
    if (i != n)
        return false;
    else {
        if (++n > length) resize(n-1);
        a[n-1] = x;
        return true;
    }
}

template<class T> inline
T ArrayUSet<T>::remove(T x) {
    int i = findIndex(x);
    if (i == n) return null;
    else {
        T y = a[i];
        a[i] = a[n-1];
        if (--n < length/3) resize(n);
        return y; }
}

template<class T>
void ArrayUSet<T>::resize(int copynum) {
//std::cout << "ArrayUSet resizing from " << length << " to " << 2*n << std::endl;
    length = 2*n;
    T * b = new T[length];
    for (int i = 0; i < copynum; i++)
        b[i] = a[i];
    if (a != 0) delete a;
    a = b;
}

} /* namespace ods */

#endif /* ARRAYUSET_H_ */
