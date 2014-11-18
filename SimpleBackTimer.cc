/*
 * BackTimer.cc
 *
 *  Created on: 2014年11月17日
 *      Author: keyming
 */
#include "SimpleBackTimer.h"
#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

BackTimer::BackTimer(std::chrono::milliseconds ms, callFunc func):msec(ms), theTimerFunc(func),
		backThread(&BackTimer::timerThread, this){

}

void BackTimer:: timerThread(){
	this_thread::sleep_for(chrono::milliseconds(msec));
	theTimerFunc();
}

BackTimer::~BackTimer(){
	backThread.join();
}

#define SIMPLEBACKTIMER_CC
#ifdef SIMPLEBACKTIMER_CC

void print(){
	cerr << "Hello world." << endl;
}
int main()
{
	BackTimer(chrono::milliseconds(2000), print);
	return 0;
}
#endif

