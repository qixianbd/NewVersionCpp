/*

 * Random.cc
 *
 *  Created on: 2014年10月29日
 *      Author: qmwx
 */
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "Random.h"

int Random::nextInt(unsigned int beg, unsigned int end) {
	assert(end >= beg);
	int data = rand();
	int base = end - beg;
	data %=  base;

	data += beg;
	return data;
}



int Random::nextInt(int n) {
	return nextInt(0, n);
}

double Random::nextDouble() {
	int data = rand();
	double ret = (double)data/RAND_MAX;
	return ret;
}

long int Random::nextLong(long beg, long end){
	assert(end >= beg);
	long data = lrand48();
	long base = end - beg;
	data %=  base;

	data += beg;
	return data;
}

double Random::nextDouble(double beg, double end){
	assert(end - beg >= 1);
	double data = nextDouble();
	data = data * (end - beg);
	return data+beg;
}

std::vector<int> Random::randomUniqueIntArray(int beg, int end) {
	std::vector<int> v;
	for(int i = beg; i < end; i++){
		v.push_back(i);
	}
	int n = end - beg;
	for(int i = 0; i < n; i++){
		int j = nextInt(0, n);
		std::swap(v[j], v[n-1-j]);
	}
	return v;
}

Random::Random(unsigned long s):seeds(s) {
	unsigned long seeds = time(NULL);
	srand(seeds);
}

std::vector<int> Random::randomIntArray(int beg, int end, int n) {
	std::vector<int> v;
	for(int i = 0; i < n; i++){
		v.push_back(nextInt(beg, end));
	}
	return v;
}

std::vector<double> Random::randomDoubleArray(double beg, double end, int n) {
	std::vector<double> v;
	for(int i = 0; i < n; i++){
		v.push_back(nextDouble(beg, end));
	}
	return v;
}


std::string Random::getFixLengthString(int length){
	assert(length >= 0);
	static const char* charString =  "abcdefghigklmnopqrstuvwxyz";
	char* buf = new char[length + 1];
	int index = 0;
	for(int i = 0; i < length; i++){
		index = nextInt(0, 26);
		buf[i] = charString[index];
	}
	buf[length] = '\0';
	std::string retString(buf);
	delete[] buf;
	return retString;
}

std::string Random::getRandomString(int len) {
	int realLength = nextInt(1, len+1);
	return getFixLengthString(realLength);
}

std::string Random::getPhoneNum(int length) {
	assert(length >= 1);
	static const char* phoneString = "0123456789";
	char* buf = new char[length + 1];
	int index = 0;
	for(int i = 0; i < length; i++){
		index = nextInt(0, 10);
		buf[i] = phoneString[index];
	}
	buf[length] = '\0';
	std::string retString(buf);
	delete[] buf;
	return retString;
}
static bool _isAllDigit(const std::string& str){
	int length = str.length();
	for(int i = 0; i < length; i++){
		if(!isdigit(str[i])){
			return false;
		}
	}
	return true;
}

std::string Random::getPhoneNumWithPrefix(const char* prefixBuf, size_t length) {
	char *prefix = NULL;
	static const char* prefixNum[] = {"132", "136", "139", "151", "158", "159", "183", "186", "187"};
	int len = sizeof(prefixNum)/ sizeof(prefixNum[0]);
	if(prefixBuf == NULL){
		prefix = new char[4];
		int index = nextInt(0, len);
		strncpy(prefix, prefixNum[index], 4);
		prefix[3] = '\0';
	}
	else{
		prefix = const_cast<char*>(prefixBuf);
	}
	assert(length > strlen(prefix));

	std::string ret(prefix);
	std::string temp = getPhoneNum(length - strlen(prefix));
	ret += temp;
	if(prefixBuf == NULL){
		delete[] prefix;
	}
	assert(_isAllDigit(ret));
	return ret;
}

boost::shared_array<int> Random::generateUniqueIntArray(int beg, int end) {
	assert(end >= beg);
	int* buf = new int[end - beg];
	boost::shared_array<int> ap(buf);
	for(int i = beg; i < end; i++){
		ap[i] = i;
	}
	int n = end - beg;
	for(int i = 0; i < n; i++){
		int j = nextInt(0, n);
		std::swap(ap[j], ap[n-1-j]);
	}
	return ap;
}
