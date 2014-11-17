/*
 * MtHashTable.h
 *
 *  Created on: 2014年11月14日
 *      Author: keyming
 */

#ifndef MTHASHTABLE_H_
#define MTHASHTABLE_H_

/**
 * Add background log for MtHashTable class. The hash table can now log a message in a background thread.
 */
#include <list>
#include <string>
#include <iostream>
#include <boost/utility.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include "BackLogger.h"

class MtHashTable : boost::noncopyable {
private:
	struct BucketNode{					// Bucket Type.
		std::list<std::string> *head;		// point to a list.
		int length;								// the length of the elements have already stored in this bucket.
		boost::shared_mutex bucketLock;
		BucketNode():head(NULL), length(0){
		}
		BucketNode(std::list<std::string> * h, int len): head(h), length(len){
		}
	};
	typedef boost::mutex mutex_t;										// simple mutex lock.
	typedef boost::shared_mutex shared_mutex_t;				// write-read lock.
	enum{INIT_BUCKETNUM= 20959};

public:
	MtHashTable();
	~MtHashTable();
	void put(const std::string &str);
	void remove(const std::string &str);
	bool contain(const std::string &str)const;
	void print(std::ostream &os = std::cout)const;

private:
	unsigned long  bucketNum;			// the bucket number in the hash table. In most case, it is better for it to be a prime.
	long elementNum;		// the actual element number have stored in the hash table.
	boost::shared_array<BucketNode> bucketPtr;		// the base pointer point to the bucket base address.
	mutable shared_mutex_t tableLock;
	BackLogger log;
	void finalize();
	unsigned long hash(const std::string& key)const;
};


#endif /* MTHASHTABLE_H_ */
