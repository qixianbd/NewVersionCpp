/*
 * Test_Atomic.cc
 *
 *  Created on: 2014年11月15日
 *      Author: keyming
 */

#include <atomic>
#include <thread>
#include <vector>
#include <functional>
#include <iostream>
#include <unistd.h>

using namespace std;

#ifdef TEST_ATOMIC_CC
void func(int threadId, atomic<int> &counter){
	for(int i = 0; i < 10000; i++){
		++counter;
	}
	counter.fetch_add(1);
}

int main()
{
	atomic<int> a;
	a = 0;
	vector<thread> threads;
	for(int i = 0; i < 5; i++){
		threads.push_back(thread(func, i, ref(a)));
	}
	for(auto &t: threads){
		t.join();
	}
	sleep(1);
	std::cout << a << endl;
}
#endif

