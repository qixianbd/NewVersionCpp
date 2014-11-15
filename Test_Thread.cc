/*
 * Test_Thread.cc
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

#ifdef TEST_THREAD_CC
using namespace std;

void func(int threadId, atomic<int> &counter){
	for(int i = 0; i < 10000; i++){
		++counter;
	}
	counter.fetch_add(1);
	std::cout << "thread id = " << threadId << ", counter = " << counter << endl;

}

int main()
{
	atomic<int> a;
	cout.sync_with_stdio(true); // Make sure cout is thread-safe

	a = 0;
	vector<thread> threads;
	for(int i = 0; i < 5; i++){
		threads.push_back(thread(func, i, ref(a)));
	}
	for(auto &t: threads){
		t.join();
	}
	std::cout << "At end, counter = " << a << endl;
}
#endif

