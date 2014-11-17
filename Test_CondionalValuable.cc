/*
 * Test_CondionalValuable.cc
 *
 *  Created on: 2014年11月15日
 *      Author: keyming
 */
// condition_variable_any::wait (with predicate)
#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex
#include <condition_variable> // std::condition_variable_any
#include <chrono>

#ifdef TEST_CONDITIONALVALUABLE_CC
using namespace std;

std::mutex queueLock;
std::condition_variable_any cv;
int productId = 0;


bool productNotEmpty() {
	return productId!=0;
}

void consume () {
	while(true){
		queueLock.lock();
		cv.wait(queueLock, productNotEmpty);				// invoke queueLock.lock(); and queueLock.unlock() in this function. And between the two
																						// subcalls, this thread is waiting for the predicate to be true.
		std::cout << "The " << productId << " th product." << std::endl;
		productId = 0;
		queueLock.unlock();
	}
	return ;
}

void product(){
	int backProduct = 0;
	while(true){
		queueLock.lock();
		backProduct++;
		productId = backProduct;
		cv.notify_one();						// only sending the unlock singnal to the consumer thread.    do not do unlock and lock pair as the wait do.
		queueLock.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(800));
	}
}


int main ()
{
  std::thread consumer_thread (consume);
  std::thread producter_thread(product);
  consumer_thread.join();
  producter_thread.join();

  return 0;
}
#endif


