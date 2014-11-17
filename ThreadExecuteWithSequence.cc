/*
 * Test_LockGuard.cc
 *
 *  Created on: 2014年11月17日
 *      Author: keyming
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>
#include <vector>

using namespace std;

//#define THREADEXECUTEWITHSEQUENCE_CC
#ifdef THREADEXECUTEWITHSEQUENCE_CC
mutex seqLock;
condition_variable_any cvy;
int seqNum = 1;
enum {FlowerCount = 999};



void firstThreadGroup(int threadId, atomic<int>& fcounts){
	while(true){
		seqLock.lock();
		while(seqNum != 1 && fcounts < FlowerCount){
			cvy.wait(seqLock);
		}
		if(fcounts >= FlowerCount){
			seqLock.unlock();
			break;
		}
		std::cerr << "Keyming " ;
		seqNum = 2;
		cvy.notify_all();
		seqLock.unlock();
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	return ;
}

void secondThreadGroup(int threadId, atomic<int>& fcounts){
	while(true){
		seqLock.lock();
		while(seqNum != 2 && fcounts < FlowerCount){
			cvy.wait(seqLock);
		}
		if(fcounts >= FlowerCount){
			seqLock.unlock();
			break;
		}
		std::cerr << "Love Wangxin " ;
		seqNum = 3;
		cvy.notify_all();
		seqLock.unlock();
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	return ;
}

void thirdThreadGroup(int threadId, atomic<int>& fcounts){
	while(true){
		seqLock.lock();
		while(seqNum != 3 && fcounts < FlowerCount){
			cvy.wait(seqLock);
		}
		if(fcounts >= FlowerCount){
			seqLock.unlock();
			break;
		}
		std::cerr << "from deep heart. And with the full happiness to give her " << (++fcounts) << " flowers"  << endl;
		seqNum = 1;
		cvy.notify_all();
		seqLock.unlock();
		this_thread::sleep_for(chrono::milliseconds(500));
	}

	return ;
}


int main()
{
	enum {ThreadNumbers = 100};
	cerr.sync_with_stdio(true);


	std::vector<thread> firstThreads, secondThreads, thirdThreads;
	atomic<int> flowflowerCountserCounts(0);

	for(int i = 0; i < ThreadNumbers; i++){
		firstThreads.push_back(thread(firstThreadGroup, i, ref(flowerCounts)));
	}
	for(int i = 0; i < ThreadNumbers; i++){
		secondThreads.push_back(thread(secondThreadGroup, i, ref(flowerCounts)));
	}
	for(int i = 0; i < ThreadNumbers; i++){
		thirdThreads.push_back(thread(thirdThreadGroup, i, ref(flowerCounts)));
	}
	for(int i = 0; i < ThreadNumbers; i++){
		firstThreads[i].join();
		secondThreads[i].join();
		thirdThreads[i].join();
	}

}
#endif



