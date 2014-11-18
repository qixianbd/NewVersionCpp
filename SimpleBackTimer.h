/*
 * BackTimer.h
 *
 *  Created on: 2014年11月17日
 *      Author: keyming
 */

#ifndef BACKTIMER_H_
#define BACKTIMER_H_

#include <thread>
#include <chrono>

class BackTimer final {
private:
	typedef void (*callFunc) ();

	std::chrono::milliseconds msec;
	callFunc theTimerFunc;
	std::thread backThread;
private:
	void timerThread();
public:
	BackTimer(std::chrono::milliseconds ms, callFunc func);
	BackTimer(const BackTimer&) = delete;
	BackTimer operator=(const BackTimer&) = delete;
	~BackTimer();
};




#endif /* BACKTIMER_H_ */
