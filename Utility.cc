/*
 * Utility.cc
 *
 *  Created on: 2014年11月3日
 *      Author: qmwx
 */
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <string>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "Utility.h"

namespace myutility{

long long usec(void) {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000000)+tv.tv_usec;
}

std::string longToBinaryString(long number) {
	if(number == 0){
		return std::string("0");
	}
	char buf[64];
	char *p = buf;
	unsigned long int num = 0;
	if(number < 0){
		*p++ = '1';
		num = labs(number);
	}
	else{
		*p++ = '0';
		num = number;
	}

	while(num){
		*p++ = (num & 1) + '0';
		num >>= 1;
	}
	*p = '\0';
	stringConverse(buf+1);
	return std::string(buf);
}

std::string longToString(long number) {
	char buf[64];
	char*p = buf;

	int sign = number < 0 ? (*p++ = '-', -1): 1;
	unsigned long num = labs(number);

	do{
		*p++ = (num % 10 ) + '0';
		num /= 10;
	}while(num);
	*p = '\0';
	char* dest = sign < 0 ? buf+1 : buf;
	stringConverse(dest);
	return std::string(buf);
}

void memSwap(void* a, void* b, size_t length) {
	assert(length >= 0);
	unsigned char* c = new unsigned char[length];
	memmove(c, a, length);
	memmove(a, b, length);
	memmove(b, c, length);
	delete[] c;
	return ;
}

void stringConverse(char* str) {
	int len = strlen(str);
	char *p = str, *q = str+len-1;
	while(p < q){
		char t = *p;
		*p = *q, *q = t;
		p++, q--;
	}
	return ;
}

int stringCmpIngoreCase(const char* str1, const char* str2) {
	const char*p = str1, *q = str2;
	while(*p && *q){
		char a = tolower(*p);
		char b = tolower(*q);
		if(a != b){
			return a < b ? -1 : 1;
		}
		p++, q++;
	}
	if('\0' == *p && '\0' == *q){
		return 0;
	}
	return *p=='\0' ? -1 : 1;
}

bool startWithSubString(const std::string& str, const std::string& sub) {
	if(strncmp(str.c_str(), sub.c_str(), sub.length()) == 0){
		return true;
	}
	return false;
}

bool endWithSubString(const std::string& str, const std::string& sub) {
	int strLength = str.length(), subLength = sub.length();
	if(strLength < subLength){
		return false;
	}
	for(int i = strLength-1, j = subLength-1; i >= 0 && j >= 0; i--, j--){
		if(str[i] != sub[j]){
			return false;
		}
	}
	return true;
}


bool isAllDigit(const std::string& str){
	int length = str.length();
	for(int i = 0; i < length; i++){
		if(!isdigit(str[i])){
			return false;
		}
	}
	return true;
}

unsigned long hashFuncForString(const std::string& key,
		unsigned long hashSize) {
	int hashVal = 0;
	int len = key.length();
	for(int i = 0; i < len; i++){
		hashVal = 37*hashVal + key[i];
	}
	hashVal %= hashSize;
	if(hashVal < 0){
		hashVal += hashSize;
	}
	return hashVal;
}



}
