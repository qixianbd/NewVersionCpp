#include <thread>
#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include <unistd.h>
#include <sstream>
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
		logStream(logFilename), exitSingle(false),
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


#ifdef BACKLOGGER_SIMPLETEST.CC
std::mutex log_mutex;
void multithread_log(int threadId, BackLogger & log){
	for (int i = 0; i < 10; i++){
		std::string msgString;
		std::stringstream ss;
		ss << i;
		ss >> msgString;
		msgString += "keyming";
		log_mutex.lock();
		log.logMsg(msgString);
		log_mutex.unlock();
	}
}

int main()
{
	std::thread* threads[10];
	BackLogger log;
	for(int i = 0; i < 10; i++){
		threads[i] = new std::thread(multithread_log, i, std::ref(log));
	}
	for(int i = 0; i < 10; i++){
		threads[i]->join();
	}

	for(int i = 0; i < 10; i++){
		delete threads[i];
	}
}
#endif

