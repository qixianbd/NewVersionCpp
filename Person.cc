/*
 * Person.cc
 *
 *  Created on: 2014年11月13日
 *      Author: keyming
 */
#include "Person.h"



std::ostream& operator<<(std::ostream& os, const Person& p){
	os << p.key << "\t" << p.personName << "\t";
	return os;
}
