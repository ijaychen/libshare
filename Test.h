#ifndef _TEST_H
#define _TEST_H

#include "Singleton.h"
#include <iostream>
using namespace std;

class Test : public Singleton<Test>
{
	friend class Singleton<Test>;
protected:
	Test(){}
public:
	~Test(){}
	void CallbackFunc(){
		cout << "CallbackFunc...\n";
	}
	
	void send_ping_msg(){
		cout << "sending ping msg...\n";
	}
public:
	void run(){
		cout << "hello world\n";
	}
};

#define sTest (*Test::instance())

#endif