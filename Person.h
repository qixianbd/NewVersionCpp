/*
 * Person.h
 *
 *  Created on: 2014年11月10日
 *      Author: qmwx
 */

#ifndef PERSON_H_
#define PERSON_H_
#include <iostream>

class Person{
		std::string key;
		std::string personName;
	public:
		Person():key("1234"), personName("wqm"){

		}
		Person(const std::string& id, const std::string& name): key(id), personName(name){

		}
		~Person(){
			//std::cerr << "delete the object. " << std::endl;
		}
		std::string getKey()const{
			return key;
		}
		std::string getName()const{
			return personName;
		}
		void print(std::ostream& os)const{
			os << key << "\t" << personName << "\t" << std::endl;
		}
		bool operator== (const Person& p){
			return key == p.key && personName == p.personName;
		}
		friend std::ostream& operator<<(std::ostream& os, const Person& p);
};





#endif /* PERSON_H_ */
