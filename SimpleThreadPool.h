/*
 * SimpleThreadPool.h
 *
 *  Created on: 2014年11月18日
 *      Author: keyming
 */

#ifndef SIMPLETHREADPOOL_H_
#define SIMPLETHREADPOOL_H_

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>


class SimpleThreadPool{
public:
	typedef void (*taskFunction)();
	enum {DEFAULTPOOLSIZE = 6};
	SimpleThreadPool(int poolSize = DEFAULTPOOLSIZE);
	~SimpleThreadPool();
	void addTask(taskFunction theTask);

private:
	std::mutex queueMutex;
	std::condition_variable condition;
	int threadNum;
	bool exitFlag;
	std::vector<std::thread> workThreadList;
	std::queue<taskFunction> taskQueue;

private:
	void executeTheTask(taskFunction theTask);
	void initThread();
};



#endif /* SIMPLETHREADPOOL_H_ */
