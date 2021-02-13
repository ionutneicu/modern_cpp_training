#include <iostream>
#include "MyClass.h"


MyClass createInstance()
{
	MyClass a;
	return a;
}

int main()
{
	MyClass a = createInstance();
	return 0;
}
