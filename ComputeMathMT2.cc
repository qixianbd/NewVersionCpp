/*
 * ComputeMathWithMultithread.cc
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
#include <math.h>

using namespace std;
typedef long long llong;

//#define COMPUTEMATHMT2_CC
#ifdef COMPUTEMATHMT2_CC

enum {ThreadNumbers = 1};

void calPowSum(int nth, int totalNum,  atomic<llong>& result){
	llong sum = 0;
	int block = totalNum/ThreadNumbers;
	int beg = nth*block;

	if(nth != ThreadNumbers -1){
		for(int i = 1; i <= block; i++){
			sum+= pow(beg+i, 3);
		}
	}
	else{
		for(int i = 1; i <= totalNum - block* (ThreadNumbers-1); i++){
			sum+= pow(beg+i, 3);
		}
	}
	result.fetch_add(sum);

}

int main()
{
	cerr.sync_with_stdio(true);


	atomic<llong> result(0);
	vector<thread> worktThreads;

	int n = 100123;
	for(int i = 0; i < ThreadNumbers; i++){
		worktThreads.push_back(thread(calPowSum, i, n, ref(result)));
	}
	for(int i = 0; i < ThreadNumbers; i++){
		worktThreads[i].join();
	}
	std::cerr << "result = " << result << endl;
	return 0;
}
#endif





