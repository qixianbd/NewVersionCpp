/*
 * TextString.h
 *
 *  Created on: 2014年11月21日
 *      Author: keyming
 */

#ifndef TEXTSTRING_H_
#define TEXTSTRING_H_
#include <vector>
#include <iostream>
#include <fstream>


class TextString{
private:
	std::ifstream textStream;
public:
	TextString(const char* filename);
	std::vector<std::string> parseText();
};




#endif /* TEXTSTRING_H_ */
