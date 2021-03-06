#include <thread>
#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include <unistd.h>
#include <sstream>
#include <stdlib.h>
#include "BackLogger.h"


void BackLogger::consumeMsg() {
//	startLock.unlock();
//	startInit = true;
//	stcv.notify_one();
//	startLock.unlock();

	while(true){
		queueLock.lock();
		while(msgQueue.empty() || !exitSingle){
			cv.wait(queueLock);
		}
		while(!msgQueue.empty()){
			logStream << msgQueue.front() << "\n" << std::flush;
			msgQueue.pop();
		}
		if(exitSingle){
			queueLock.unlock();
			break;
		}
		else{
			queueLock.unlock();
		}

	}
	logStream << "The thread exit." << std::endl;
	return ;
}




BackLogger::BackLogger(std::string logFilename):
		logStream(logFilename), msgQueue(std::queue<std::string>()), exitSingle(false),
		startInit(false), backThread(&BackLogger::consumeMsg, this){

}




void BackLogger::logMsg(std::string msg) {
	queueLock.lock();
	msgQueue.push(msg);
	cv.notify_one();
	queueLock.unlock();
	return ;
}

bool BackLogger::queueEmpty()const {
	return msgQueue.empty();
}

BackLogger::~BackLogger() {

//	startLock.lock();
//	while(!startInit){
//		wait(startLock);
//	}
//	startLock.unlock();

	queueLock.lock();
	exitSingle = true;
	cv.notify_one();
	queueLock.unlock();
	backThread.join();
}
/*
 * BackLogger.cc
 *
 *  Created on: 2014年11月17日
 *      Author: keyming
 */

//#define BACKLOGGER_SIMPLETEST_CC
#ifdef BACKLOGGER_SIMPLETEST_CC
std::mutex log_mutex;
void multithread_log(int threadId, BackLogger & log){
	for (int i = 0; i < 10; i++){
		std::string msgString("keyming");
		log_mutex.lock();
		log.logMsg(msgString);
		log_mutex.unlock();
	}
}

int main()
{
	std::vector<std::thread> threads;
	BackLogger log;
	for(int i = 0; i < 10; i++){
		log_mutex.lock();
		threads.push_back(std::thread(multithread_log, i, std::ref(log)));
		log_mutex.unlock();
	}
	for(int i = 0; i < 10; i++){
		threads[i].join();
	}

}
#endif

