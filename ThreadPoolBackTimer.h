/*
 * ThreadPoolBackTimer.h
 *
 *  Created on: 2014年11月18日
 *      Author: keyming
 */

#ifndef THREADPOOLBACKTIMER_H_
#define THREADPOOLBACKTIMER_H_

#include <chrono>
#include <thread>
#include <vector>
#include <mutex>              // std::mutex
#include <condition_variable> // std::condition_variable_any
#include <chrono>

class ThreadPoolBackTimer final{

private:
	typedef void (*taskFunc)();
	enum {THREADNUM = 30};
	std::vector<std::thread> threadPool;
	ThreadPoolBackTimer();

public:
	static ThreadPoolBackTimer& getInstance();
	~ThreadPoolBackTimer();
	ThreadPoolBackTimer(const ThreadPoolBackTimer&) = delete;
	ThreadPoolBackTimer operator=(const ThreadPoolBackTimer&) = delete;


public:
	int addTimerTask(std::chrono::milliseconds ms, taskFunc func);
	void deleteTimerTask(int taskId);


private:
	std::mutex poolLock;
	std::condition_variable_any cvy;
	void initThread();
	void executeTask(std::chrono::milliseconds ms, taskFunc func);
};



#endif /* THREADPOOLBACKTIMER_H_ */
