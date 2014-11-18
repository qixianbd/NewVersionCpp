/*
 * FlagSweepGCSimulator.cc
 *
 *  Created on: 2014年11月17日
 *      Author: keyming
 */

#include <memory>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>
#include <vector>
#include <math.h>
#include "Random.h"
#include "Person.h"

//#define FLAGSWEEPGCSIMULATOR_CC
#ifdef FLAGSWEEPGCSIMULATOR_CC

using namespace std;

struct PersonObject{
	Person peo;
	bool noused;
	PersonObject():peo(Person()), noused(false){
	}
	bool operator()(PersonObject p){
		return p.noused;
	}
};
enum {MAX_NUM = 10*1024};
mutex gcMutex;
mutex clockMutex;
std::condition_variable_any cv, excv;
bool timeCome = true;
atomic<int> timeCounters(0);
bool exitSingle = false;



bool twoManyRubbish(std::vector<PersonObject>& gcArea){
	lock_guard<mutex> lk(gcMutex);
	return gcArea.size() >= 7 *1024;
}

void productObject(std::vector<PersonObject>& gcArea){
	while(true){
		{
			if(exitSingle){
				break;
			}
		lock_guard<mutex> lock(gcMutex);
		gcArea.push_back(PersonObject());
		//std::cerr << "push into a object." << std::endl;
		}
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}

void deleteObject(std::vector<PersonObject>& gcArea){
	Random r;
	while(true){
		{
			if(exitSingle){
				break;
			}
			lock_guard<mutex> lock(gcMutex);
			if(!gcArea.empty()){
				int index = r.nextInt(0, gcArea.size());
				gcArea[index].noused = true;
				//std::cerr << "mark a object to delete." << std::endl;
			}
		}
		this_thread::sleep_for(chrono::milliseconds(50));
	}
}

void timeCounter(){
	while(true){
		int increateCount = 4;
		this_thread::sleep_for(chrono::seconds(1));
		clockMutex.lock();
		timeCome = true;
		timeCounters.fetch_add(increateCount);
		if(timeCounters >= 100){
			exitSingle = true;
			cv.notify_all();
			clockMutex.unlock();
			break;
		}
		cv.notify_all();
		clockMutex.unlock();
	}
}

void backGroundSweep(std::vector<PersonObject>& gcArea){
	while(true){
		if(exitSingle){
			break;
		}
		clockMutex.lock();
		while(!timeCome &&  !twoManyRubbish(gcArea)){
			cv.wait(clockMutex);
		}
		{
			std::cerr << "begin to delete" << std::endl;
			lock_guard<mutex> lock(gcMutex);
			remove_if(gcArea.begin(), gcArea.end(), PersonObject());
			timeCome = false;
			std::cerr << "sweep the vector" << std::endl;
		}
		clockMutex.unlock();
	}
}

int main()
{
	std::vector<PersonObject> gcArea;
	thread t0(timeCounter);
	thread t1(productObject, ref(gcArea));
	thread t2(deleteObject, ref(gcArea));
	thread t3(backGroundSweep, ref(gcArea));

	t0.join();t1.join(); t2.join(); t3.join();
	return 0;
}

#endif
