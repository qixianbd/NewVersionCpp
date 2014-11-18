/*
 * SimpleThreadPool.cc
 *
 *  Created on: 2014年11月18日
 *      Author: keyming
 */

#include "SimpleThreadPool.h"

using namespace std;

	SimpleThreadPool::SimpleThreadPool(int poolSize):threadNum(poolSize), exitFlag(false){
		for(int i = 0; i < threadNum; i++){
			workThreadList.push_back(thread(&SimpleThreadPool::initThread, this));
		}
	}
	SimpleThreadPool::~SimpleThreadPool(){
		{
			unique_lock<mutex> queueLock(queueMutex);
			exitFlag = true;
			condition.notify_all();
		}
		for(int i = 0; i < threadNum; i++){
			workThreadList[i].join();
		}
	}
	void SimpleThreadPool::addTask(taskFunction theTask){
		queueMutex.lock();
		taskQueue.push(theTask);
		condition.notify_all();
		queueMutex.unlock();
	}

	void SimpleThreadPool::initThread(){
		taskFunction theTask;
		while(!exitFlag){
			unique_lock<mutex> queueLock(queueMutex);{
				while(taskQueue.empty() && exitFlag == false){
					condition.wait(queueLock);
				}
				if(true == exitFlag){
					continue;
				}
				theTask = taskQueue.front();
				taskQueue.pop();
			}
			theTask();
		}
		return ;
	}



#define SIMPLETHREADPOOL_CC
#ifdef SIMPLETHREADPOOL_CC
#include <unistd.h>
#include <iostream>
#include <atomic>
#include "Random.h"


std::queue<int> buffer;
mutex bufferMutex;
mutex ioMutex;

atomic<int> number(0);


void product(){
	for(int i = 0; i < 20; i++){
		number.fetch_add(1);
		Random r;
		int data = r.nextInt(0, 100);
		bufferMutex.lock();
		buffer.push(data);
		bufferMutex.unlock();
		this_thread::sleep_for(chrono::milliseconds(500));
	}

}

void consume(){
	for(int i = 0; i < 20; i++){
		int data = 0;
		data = number;

		bufferMutex.lock();
		if(!buffer.empty()){
			data = buffer.front();
			buffer.pop();
		}
		bufferMutex.unlock();

		ioMutex.lock();
		std::cerr << "Out put " << data << std::endl;
		ioMutex.unlock();
		this_thread::sleep_for(chrono::milliseconds(800));
	}

	return ;
}

int main()
{
	cerr.sync_with_stdio(true);
	SimpleThreadPool tpool;
	for(int i = 0; i < 3; i++){
		tpool.addTask(product);
		tpool.addTask(consume);
	}

	sleep(50);
	return 0;
}

#endif


