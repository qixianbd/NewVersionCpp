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

#ifdef TEST_TIME_MUTEX_CC
static timed_mutex  init_lock;
static mutex io_lock;

static bool initable = false;

void init(int id){
	io_lock.lock();
	std::cout << "Init only once. Thread Id = " << id << std::endl;
	io_lock.unlock();
	initable = true;
}
/**
 *
 * @param threadId
 */
void initOnlyOnce(int threadId){
	if(initable == false){									// The first test
			init_lock.lock();
			if(initable == false){							// The second test.
				this_thread::sleep_for(chrono::milliseconds(50));
				init(threadId);
				init_lock.unlock();
			}
			else{
				/*
				 * This branch denote the need for the second checks.
				* If the init thread(which really do the init) hold a lock for a long time, and the other threads have already past the fist test(initable == false) at the time
				* the init thread sleep, then we will need for the second check of variable initable.
				 */
				init_lock.unlock();
				io_lock.lock();
				std::cout << "This thread (id =  " << threadId << ") get the init lock, but other threads do the init." << std::endl;
				io_lock.unlock();
			}
	}
	else{
		io_lock.lock();
		std::cout << "For the thread (id =  " << threadId << "), the initable bool value have already be true." << std::endl;
		io_lock.unlock();
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
#endif






