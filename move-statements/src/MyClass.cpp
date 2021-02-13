/*
 * MyClass.cpp
 *
 *  Created on: Feb 13, 2021
 *      Author: ionut
 */

#include "MyClass.h"
#include <iostream>

MyClass::MyClass() {
	std::cout << "default constructor" << std::endl;
}

MyClass::~MyClass() {
	std::cout << "default destructor" << std::endl;
}

MyClass::MyClass(const MyClass &other) {
	std::cout << "copy constructor" << std::endl;
}

MyClass& MyClass::operator=(const MyClass &other) {
	std::cout << "assignment operator" << std::endl;
	return *this;
}


#ifdef HAS_MOVE_SEMANTICS
MyClass& MyClass::operator=(MyClass &&other) {
	std::cout << "move operator" << std::endl;
	return *this;
}

MyClass::MyClass(MyClass &&other) {
	std::cout << "move constructor" << std::endl;
}
#endif
