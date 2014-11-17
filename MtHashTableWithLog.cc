/*
 * MtHashTable.cc
 *
 *  Created on: 2014年11月14日
 *      Author: keyming
 */

#include <iostream>
#include <algorithm>
#include <iterator>
#include <queue>
#include "Utility.h"
#include "MtHashTableWithLog.h"
#include "FixedSizeHeap.h"

MtHashTable::MtHashTable():bucketNum(INIT_BUCKETNUM), elementNum(0), bucketPtr(new BucketNode[bucketNum]), log("hashLog.txt"){
}

MtHashTable::~MtHashTable() {
	finalize();
}

void MtHashTable::put(const std::string& str) {
	unsigned long index = hash(str);
	BucketNode *pNode = &bucketPtr[index];

	// 1. insert the element into the bucket.     add the bucket lock.
	pNode->bucketLock.lock();
	if(NULL == pNode->head){
		pNode->head = new std::list<std::string>();
	}
	pNode->head->push_back(str);
	pNode->length++;
	pNode->bucketLock.unlock();

	//2. add the element counter. add the table lock.
	tableLock.lock();
	elementNum++;
	log.logMsg(std::string("Insert one str: ") + str);
	tableLock.unlock();
	return ;
}

void MtHashTable::remove(const std::string& str) {
	unsigned long index = hash(str);
	int removedCount= 0;			// the element, which equals @parameter str,  count number in the head list
	BucketNode *pNode = &bucketPtr[index];


	// 1. remove the element in the bucket, and record the count.  add bucket write lock.
	pNode->bucketLock.lock();
	if(NULL != pNode->head){
		removedCount = std::count(pNode->head->begin(), pNode->head->end(), str);
		pNode->head->remove(str);
		pNode->length -= removedCount;
		assert(pNode->length >= 0);
	}
	pNode->bucketLock.unlock();

	//2. update the elementNum of this object. add the table lock with write lock.
	tableLock.lock();
	elementNum -= removedCount;
	log.logMsg("remove the strings");
	assert(elementNum >= 0);
	tableLock.unlock();
	return ;
}

bool MtHashTable::contain(const std::string& str)const {
	unsigned long index = hash(str);
	BucketNode *pNode = &bucketPtr[index];
	pNode->bucketLock.lock_shared();
	if(NULL == pNode->head){
		pNode->bucketLock.unlock_shared();
		return false;
	}
	std::list<std::string>::iterator pos = std::find(pNode->head->begin(), pNode->head->end(), str);
	bool ret = (pos == pNode->head->end() ? false : true);
	pNode->bucketLock.unlock_shared();
	return ret;
}

void MtHashTable::print(std::ostream& os)const {

	myutility::FixedSizeHeap<int> listLengthQueue(50);
	// 1. Out put the elements stored in the hash table. add bucket lock for each bucket (read).
	for(unsigned long int i = 0; i < bucketNum; i++){
		BucketNode *pNode = &bucketPtr[i];
		pNode->bucketLock.lock_shared();
		if(NULL != pNode->head){
			listLengthQueue.push(pNode->length);
			os << "listSize= " << pNode->length << "\t";
			std::copy(pNode->head->begin(), pNode->head->end(), std::ostream_iterator<std::string>(os, "\t"));
			os << "\n";
		}
		pNode->bucketLock.unlock_shared();
	}

	//2. Count and get the statistic data of the hash table. add table lock (read).
	tableLock.lock_shared();
	double capRatio = (double) elementNum / bucketNum;
	long theElementNum = elementNum;
	tableLock.unlock_shared();

	//3. Out put the hash table statistic data.
	os << "\n************************************\nThe hash table statistic data:\n" << std::endl;
	os << "Element count = " << theElementNum << std::endl;
	os << "Hash table capability ratio = " << capRatio << std::endl;
	while(!listLengthQueue.empty()){
		os << listLengthQueue.top() << "\n";
		listLengthQueue.pop();
	}

	return ;
}

void MtHashTable::finalize() {
	for(unsigned long  i = 0; i < bucketNum; i++){
		// perhaps may occur "delete NULL" situation, when bucketPtr[i].basePtr is NULL. The key is delete NULL is safe.
		delete bucketPtr[i].head;
		bucketPtr[i].head = NULL; // set to be NULL to avoid double delete.
	}
	bucketPtr.reset();
}

unsigned long MtHashTable::hash(const std::string& key)const {
	return myutility::hashFuncForString(key, bucketNum);
}
