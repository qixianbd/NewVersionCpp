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
#include <chrono>

using namespace std;


static timed_mutex  init_lock;
static mutex io_lock;

static bool initable = false;

void init(int id){
	io_lock.lock();
	std::cout << "Init only once. Thread Id = " << id << std::endl;
	io_lock.unlock();
	initable = true;
}

void initOnlyOnce(int threadId){
	if(initable == false){
		bool ret = init_lock.try_lock_for(chrono::milliseconds(20));
		if(ret == true)
//		init_lock.lock();
		{
			if(initable == false){
				this_thread::sleep_for(chrono::milliseconds(50));
				init(threadId);
				init_lock.unlock();
			}
		}
		else{
			io_lock.lock();
			std::cout << "This thread (id =  " << threadId << ") Could not hold the init lock" << std::endl;
			io_lock.unlock();
		}

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
	std::cout << "The end." << std::endl;
}







