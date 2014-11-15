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
#include <mutex>

using namespace std;

#ifdef DOUBLElOCK_CC
static mutex  init_lock;
static mutex io_lock;

static bool initable = false;

void init(int id){
	std::cout << "Init only once. Thread Id = " << id << std::endl;
	initable = true;
}

void initOnlyOnce(int threadId){
	if(initable == false){
		init_lock.lock();
		if(initable == false){
			init(threadId);
		}
		init_lock.unlock();
	}

	io_lock.lock();
	std::cout << "The thread id =  " << threadId << std::endl;
	io_lock.unlock();
	return ;
}

int main()
{
	cout.sync_with_stdio(true); // Make sure cout is thread-safe
	vector<thread> threads;
	for(int i = 0; i < 50; i++){
		threads.push_back(thread(initOnlyOnce, i));
	}
	for(auto &t: threads){
		t.join();
	}
}
#endif






