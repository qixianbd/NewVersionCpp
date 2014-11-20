/*
 * BackLogger.h
 *
 *  Created on: 2014年11月17日
 *      Author: keyming
 */

#ifndef BACKLOGGER_H_
#define BACKLOGGER_H_
#include <queue>
#include <string>
#include <thread>
#include <fstream>
#include <mutex>
#include <condition_variable>



class BackLogger{
	private:
	std::mutex queueLock;
	std::mutex startLock;
	std::condition_variable_any cv;
	//std::condition_variable_any stcv;

private:
	std::ofstream logStream;
	std::queue<std::string> msgQueue;
	bool exitSingle;
	bool startInit;
	std::thread backThread;



private:
	void consumeMsg();
	bool queueEmpty()const;

public:
	BackLogger(std::string filename = "logger.txt");
	void logMsg(std::string msg);
	~BackLogger();
};




#endif /* BACKLOGGER_H_ */
