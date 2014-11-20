/*
 * DeadLockExample.cc
 *
 *  Created on: 2014年11月20日
 *      Author: keyming
 */

//#define DEADLOCKEXAMPLE_CC
#ifdef DEADLOCKEXAMPLE_CC

#include <unistd.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include "Random.h"

using namespace std;

mutex mutex1;
mutex mutex2;
void consume(){
	mutex1.lock();
	//sleep(1);
	mutex2.lock();

	std::cerr << "Used to test Helgrind. " << std::endl;

	mutex2.unlock();
	mutex1.unlock();
	return ;
}
void product(){
	mutex2.lock();
	//sleep(1);
	mutex1.lock();

	std::cerr << "Use Helgrind to test dead lock." << std::endl;
	mutex1.unlock();
	mutex2.unlock();
	return ;
}

int main()
{
	thread t1(product);
	thread t2(consume);
	sleep(1);
	t1.join();
	t2.join();
	return 0;
}
#endif

