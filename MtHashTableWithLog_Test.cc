/*
 * MtHashTable_Test.cc
 *
 *  Created on: 2014年11月17日
 *      Author: keyming
 */



/*
 * MtHashTable_Test.cc
 *
 *  Created on: 2014年11月14日
 *      Author: keyming
 */
#include <boost/thread.hpp>
#include <unistd.h>
#include "MtHashTableWithLog.h"
#include "Utility.h"
#include "Random.h"
using namespace boost;

//#define MTHASHTABLEWITHLOG_CC
#ifdef MTHASHTABLEWITHLOG_CC
static boost::mutex mu_io;
static boost::mutex mu_ht;
static void searchData(MtHashTable& ht){
	Random r;
	for(int i = 0; i < 8*100; i++){
		std::string upst = r.getPhoneNum(7);
		boost::lock_guard<boost::mutex> lg(mu_ht);
		bool ret = ht.contain(upst);
		if(ret == true){
			mu_io.lock();
			std::cerr  << "Thread id = " <<this_thread::get_id()  << ", " << upst << "is in the hash table" << "\n";
			mu_io.unlock();
		}
	}
}



static void insertData(MtHashTable & ht){
	Random r;
	for(int i = 0; i < 5*100; i++){
		std::string upst = r.getPhoneNum(7);
		boost::lock_guard<boost::mutex> lg(mu_ht);
		ht.put(upst);
		//this_thread::sleep_for(chrono::microseconds(100));
	}
}

static void deleteData(MtHashTable &ht){
	Random r;
	for(int i = 0; i < 3*100; i++){
		std::string upst = r.getPhoneNum(7);
		boost::lock_guard<boost::mutex> lg(mu_ht);
		ht.remove(upst);
		//this_thread::sleep_for(chrono::milliseconds(1));
	}
}


int main()
{

	std::cerr.sync_with_stdio(true);
	MtHashTable ht;
	Random r;

	//1. Make definition of the three kinds of thread pools.
	enum POOL_SIZE{PUTSIZE=2, SEARCHSIZE=4, DELETESIZE=1};
	thread* insertThreadPool[PUTSIZE];
	thread* searchThreadPool[SEARCHSIZE];
	thread* deleteThreadPool[DELETESIZE];


	//2. start the thread in the thread pool.
	for(int i = 0; i < PUTSIZE; i++){
		boost::lock_guard<boost::mutex> lg(mu_ht);
		insertThreadPool[i] = new  thread(insertData, ref(ht));
	}
	for(int i = 0; i < SEARCHSIZE; i++){
		boost::lock_guard<boost::mutex> lg(mu_ht);
		searchThreadPool[i] = new thread(searchData, ref(ht));
	}
	for(int i = 0; i < DELETESIZE; i++){
		boost::lock_guard<boost::mutex> lg(mu_ht);
		deleteThreadPool[i] = new thread(deleteData, ref(ht));
	}

	sleep(5);
	//this_thread::sleep_for(chrono::seconds(5));
	for(int i = 0; i < PUTSIZE; i++){
		insertThreadPool[i]->join();
	}
	for(int i = 0; i < SEARCHSIZE; i++){
		searchThreadPool[i]->join();
	}
	for(int i = 0; i < DELETESIZE; i++){
		deleteThreadPool[i]->join();
	}
	//ht.print(std::cerr);


	//4. the free the resource that have already malloc.
	for(int i = 0; i < PUTSIZE; i++){
		delete insertThreadPool[i];
	}
	for(int i = 0; i < SEARCHSIZE; i++){
		delete searchThreadPool[i];
	}
	for(int i = 0; i < DELETESIZE; i++){
		delete deleteThreadPool[i];
	}
	return 0;
}
#endif



