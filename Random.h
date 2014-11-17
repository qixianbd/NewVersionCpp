/*
 * Random.h
 *
 *  Created on: 2014年10月29日
 *      Author: qmwx
 */

#ifndef RANDOM_H_
#define RANDOM_H_
#include<vector>
#include <string>
#include <boost/shared_array.hpp>
class Random{
public:
	Random(unsigned long s = 1);
	int nextInt(unsigned int beg, unsigned int end);
	int nextInt(int n);

	long int nextLong(long beg, long end);

	double nextDouble();
	double nextDouble(double beg, double end);
	std::string getRandomString(int len = 31);
	std::string getFixLengthString(int length = 8);
	std::vector<int> randomUniqueIntArray(int beg, int end);
	std::vector<int> randomIntArray(int beg, int end, int n);
	boost::shared_array<int>  generateUniqueIntArray(int beg, int end);
	std::vector<double> randomDoubleArray(double beg, double end, int n);
	std::string getPhoneNum(int length = 7);
	std::string getPhoneNumWithPrefix(const char* prefixBuf, size_t length = 7);
private:
	unsigned long seeds;
};



#endif /* RANDOM_H_ */
