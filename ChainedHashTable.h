/*
 * ChainedHashTable.h
 *
 *  Created on: 2011-11-30
 *      Author: morin
 *  extensive mods 2014Mar, bds
 */

#ifndef CHAINEDHASHTABLE_H_
#define CHAINEDHASHTABLE_H_
#include <cstdlib>
#include "ArrayUSet.h"

namespace ods {

template<class T>
// T must be a class on which operator== and function hashCode are defined.
class ChainedHashTable {
protected:
    typedef ArrayUSet<T> Chain;
    Chain *t;
    int n; // number of elts
    int d; // t has length 2^d. 
    int z;
    static const int w = 32; //sizeof(int)*8;
    T null;

public:
    ChainedHashTable(T nullItem = T());
    ~ChainedHashTable();
    bool add(T x);
    T remove(T x);
    T find(T x) { return t == 0 ? null : t[hash(x)].find(x); };
    int size() { return n; }
    void clear();
    T random();

protected:
    void resize();
    int hash(T x) { return hashFromInt( hashCode( x ) ); }

    int hashFromInt(int k) { return ((unsigned)(z * k)) >> (w-d); }
};

template<class T>
ChainedHashTable<T>::ChainedHashTable(T nullItem) {
    t = 0; //NULL
    n = 0;
    d = 0;
    null = nullItem;
    z = rand() | 1;     // is a random odd integer
}

template<class T>
ChainedHashTable<T>::~ChainedHashTable() {
}


template<class T>
bool ChainedHashTable<T>::add(T x) {
    if (t == 0 or find(x) == null) {
        int length = (t == 0 ? 0 : 1 << d); // length of current table t
        if (++n > length) resize();
    bool k =        t[hash(x)].add(x);
        return true;
    } else
        return false;
}


template<class T>
T ChainedHashTable<T>::remove(T x) {
    if (t == 0) return null;
    T y = t[hash(x)].remove(x);
    if (y != null and --n <= (1<<d)/4)
        resize();
    return y;
}

template<class T>
void ChainedHashTable<T>::clear() {
    if (t != 0) delete[] t;
    t = 0;
    n = 0;
    d = 0;
}

template<class T>
T  ChainedHashTable<T>::random() { // must be a nonempty table.
    int length = 1<<d;
    int i = rand()%length;
    while (t[i].size() == 0) i = (i+1)%length; // expected # of tries <= 4.
    return t[i].random();
}

template<class T>
void ChainedHashTable<T>::resize() {
    int oldlength = (t == 0 ? 0 : 1 << d); // length of current table t
    d = 0;
    while (1<<d <= n) d++;
    //int newlength = (n == 0) ? 0 : 1 << d; // next length
    Chain * newTable = ((n == 0) ? 0 : new Chain[ 1<<d ]); // table size will be 2^d.
    for (int i = 0; i < oldlength; i++) {
        for (int j = 0; j < t[i].size(); j++) {
            T x = t[i].get(j);
            newTable[hash(x)].add(x);
        }
    }
    if (t != 0) delete[] t;
    t = newTable;
}

} /* namespace ods */
#endif /* CHAINEDHASHTABLE_H_ */
