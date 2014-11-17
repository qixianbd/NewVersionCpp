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
#include "MtHashTableWithLog.h"
#include "Utility.h"
#include "Random.h"
using namespace boost;


static boost::mutex mu_io;
static void searchData(MtHashTable& ht){
	Random r;
	for(int i = 0; i < 5*myutility::IMID_NUMCOUNT; i++){
		std::string upst = r.getPhoneNum(7);
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
	for(int i = 0; i < 5*myutility::IMID_NUMCOUNT; i++){
		std::string upst = r.getPhoneNum(7);
		ht.put(upst);
		this_thread::sleep_for(chrono::microseconds(100));
	}
}

static void deleteData(MtHashTable &ht){
	Random r;
	for(int i = 0; i < myutility::IMID_NUMCOUNT; i++){
		std::string upst = r.getPhoneNum(7);
		ht.remove(upst);
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}


int main()
{

	MtHashTable ht;
	Random r;

	//1. Make definition of the three kinds of thread pools.
	enum POOL_SIZE{PUTSIZE=8, SEARCHSIZE=60, DELETESIZE=2};
	thread* insertThreadPool[PUTSIZE];
	thread* searchThreadPool[SEARCHSIZE];
	thread* deleteThreadPool[DELETESIZE];


	//2. start the thread in the thread pool.
	for(int i = 0; i < PUTSIZE; i++){
		insertThreadPool[i] = new  thread(insertData, ref(ht));
	}
	for(int i = 0; i < SEARCHSIZE; i++){
		searchThreadPool[i] = new thread(searchData, ref(ht));
	}
	for(int i = 0; i < DELETESIZE; i++){
		deleteThreadPool[i] = new thread(deleteData, ref(ht));
	}


	this_thread::sleep_for(chrono::seconds(5));
	for(int i = 0; i < PUTSIZE; i++){
		insertThreadPool[i]->join();
	}
	for(int i = 0; i < SEARCHSIZE; i++){
		searchThreadPool[i]->join();
	}
	for(int i = 0; i < DELETESIZE; i++){
		deleteThreadPool[i]->join();
	}
	ht.print(std::cerr);


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




