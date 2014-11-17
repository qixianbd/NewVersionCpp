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

#define COMPUTEMATHWITHMULTITHREAD_CC
#ifdef COMPUTEMATHWITHMULTITHREAD_CC
void calPowSum(int n, atomic<llong>& result){
	llong sum = 0;
	for(int i = 0; i <= n; i++){
		sum+= pow(i, 3);
	}
	result.fetch_add(sum);
}

int main()
{
	enum {ThreadNumbers = 100};
	cerr.sync_with_stdio(true);


	atomic<llong> result(0);
	vector<thread> worktThreads;

	for(int i = 0; i < ThreadNumbers; i++){
		worktThreads.push_back(thread(calPowSum, i, ref(result)));
	}
	for(int i = 0; i < ThreadNumbers; i++){
		worktThreads[i].join();
	}
	std::cerr << "result = " << result << endl;
	return 0;
}
#endif
