/*
 * MyClass.h
 *
 *  Created on: Feb 13, 2021
 *      Author: ionut
 */

#ifndef SRC_MYCLASS_H_
#define SRC_MYCLASS_H_

// check C++ standard is at least 11

#if __cplusplus > 199711L
#define HAS_MOVE_SEMANTICS
#endif

class MyClass {
public:
	MyClass();
	virtual ~MyClass();
	MyClass(const MyClass &other);
	MyClass& operator=(const MyClass &other);
#ifdef HAS_MOVE_SEMANTICS
	MyClass(MyClass &&other);
	MyClass& operator=(MyClass &&other);
#endif
};


#endif /* SRC_MYCLASS_H_ */
