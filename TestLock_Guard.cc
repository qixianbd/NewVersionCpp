/*
 * TestLockWithSharedPtr.cc
 *
 *  Created on: 2014年11月17日
 *      Author: keyming
 */

#include <memory>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>
#include <vector>
#include <math.h>
#include "Random.h"

//#define TESTLOCK_GUARD_CC
#ifdef TESTLOCK_GUARD_CC

using namespace std;

mutex result_mutex;
int theNum = 0;

void consume(){
	while(true){
		{
		lock_guard<mutex> lock(result_mutex);
		int num = theNum;
		std::cerr << "pow " << num << " is " << pow(num, 2) << endl;
		}
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}

//切记不要在持有锁的时候睡眠.如要如下面代码所示：  如果consume 和 product 都是在持有锁的时候睡眠，
// 那非常有可能发生死锁，　因为我们不知道睡眠的机制会影响哪些东西。
/**
 * void consume(){
	while(true){
		lock_guard<mutex> lock(result_mutex);
		int num = theNum;
		std::cerr << "pow " << num << " is " << pow(num, 2) << endl;
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}
 */


void product(){
	Random r;
	while(true){
		{
		int num = r.nextInt(0, 1000);
		lock_guard<mutex> lock(result_mutex);
		theNum = num;
		}
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	return ;
}

int main()
{
	thread t1(product);
	thread t2(consume);
	sleep(500);
	cerr << "end" << endl;
	return 0;
}
#endif

