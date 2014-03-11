/*
	GetSetTimes.cpp
	A program to measure get and set costs on ArrayDeque and SLList.
	bds 2014Mara 
*/
#include <ctime>
#include <iostream>
#include "ArrayDeque.h"
#include "SLList.h"

template<class FloatList> 
int test(FloatList & L, int n);

int main(){
	int n = 1000000;

	ods::ArrayDeque<float> AD;
	std::cout << "Starting ArrayDeque Get/set test " << std::endl;
	int ADtime = test(AD, n);
	std::cout << "ArrayDeque Get/set time is " << ADtime;
	std::cout << " for " << n << " trials." << std::endl << std::endl;

	ods::SLList<float> SL;
	std::cout << "Starting SLList Get/set test " << std::endl;
	int SLtime = test(SL, n);
	std::cout << "SLList Get/set time is " << SLtime;
	std::cout << " for " << n << " trials." << std::endl << std::endl;
}

template<class FloatList> 
int test(FloatList & L, int n){
	for (int i = 0; i < n; ++i)
		L.push(-i);
	int start = clock();
	for (int i = 0; i < n; ++i) {
		int x = L.get(i);
		L.set(i, x+1);
	}
	// sanity check
	int k = n/2;
	if (L.get(k) != -k + 1) std::cerr << "get/set error" << std::endl;
	return clock()-start;
}
