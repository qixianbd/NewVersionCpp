/*
 * ThreadPoolBackTimer.cc
 *
 *  Created on: 2014年11月18日
 *      Author: keyming
 */

#include "ThreadPoolBackTimer.h"
#include <vector>
#include <iostream>

using namespace std;

ThreadPoolBackTimer::ThreadPoolBackTimer() {
}

ThreadPoolBackTimer& ThreadPoolBackTimer::getInstance() {
	static ThreadPoolBackTimer instance;
	return instance;
}

ThreadPoolBackTimer::~ThreadPoolBackTimer() {
	lock_guard<mutex> lock(poolLock);
	for(auto& t : threadPool){
		t.join();
	}
}

void ThreadPoolBackTimer::executeTask(std::chrono::milliseconds ms,
		taskFunc func){
	this_thread::sleep_for(ms);
	func();
}
int ThreadPoolBackTimer::addTimerTask(std::chrono::milliseconds ms,
		taskFunc func) {
	lock_guard<mutex> lock(poolLock);
	threadPool.push_back( thread(&ThreadPoolBackTimer::executeTask, this, ms, func) );
	return threadPool.size() -1 ;
}

void ThreadPoolBackTimer::deleteTimerTask(int taskId) {
}

void ThreadPoolBackTimer::initThread(){
//	lock_guard<mutex> lock(poolLock);
//	cvy.wait(lock);

}

//#define ThreadPoolBackTimer_cc
#ifdef ThreadPoolBackTimer_cc
mutex io_lock;

void printHello(){
	lock_guard<mutex> lock(io_lock);
	cerr << "Hello, ";
}

void printWord(){
	lock_guard<mutex> lock(io_lock);
	cerr << " World! \n";
}

typedef chrono::milliseconds msec;

int main()
{
	ThreadPoolBackTimer &tp = ThreadPoolBackTimer::getInstance();
	msec m1(1000), m2(2000);
	tp.addTimerTask(m1, printHello);
	tp.addTimerTask(m2, printWord);
	for(int  i = 0; i < 10; i++){
		tp.addTimerTask(msec(i*1000), printHello);
		tp.addTimerTask(msec(i*1000+100), printWord);
	}
	return 0;
}
#endif

