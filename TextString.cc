/*
 * TextString.cc
 *
 *  Created on: 2014年11月21日
 *      Author: keyming
 */
#include "TextString.h"
#include <assert.h>
#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive.hpp>

using namespace std;

TextString::TextString(const char* filename):textStream(filename){
	if(!textStream){
		assert(0);
	}
}

std::vector<std::string> TextString::parseText() {
	vector<string> vs;
	string tempString;
	using namespace boost;
	using namespace boost::xpressive;


	while(textStream){
		textStream  >>  tempString;
	}
}


int main()
{

	return 0;
}
