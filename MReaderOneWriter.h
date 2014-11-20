/*
 * MReaderOneWriter.h
 *
 *  Created on: 2014年11月18日
 *      Author: keyming
 */

#ifndef MREADERONEWRITER_H_
#define MREADERONEWRITER_H_

#include <chrono>
#include <thread>
#include <queue>
#include <mutex>              // std::mutex
#include <condition_variable> // std::condition_variable_any


class MReaderOneWriter{
private:
	std::queue<int> contentQueue;
	std::mutex queueMutex;

};




#endif /* MREADERONEWRITER_H_ */
