#include <iostream>


class A
{
public:
	A()  { std::cout << "A" << std::endl; }
	~A() { std::cout << "~A" << std::endl; }
	A( const A& rhs ){ std::cout << "A:copy" << std::endl; }
	A& operator=(const A&){ std::cout <<"A:="<< std::endl; }
	A( A&& rhs ){ std::cout << "A:move" << std::endl; }
	A& operator=(A&&){ std::cout <<"A:=move"<< std::endl; }

};

class B
{
	A m_a;
public:
	B(){std::cout << "B" << std::endl;}
	~B(){std::cout << "~B" << std::endl;}
	B( const B& rhs ){ m_a = rhs.m_a; std::cout << "B:copy" << std::endl; }
	B( B&& rhs ){ m_a = std::move(rhs.m_a); std::cout << "B:move" << std::endl;}
	B& operator=(const B& rhs){ m_a = rhs.m_a; std::cout <<"B:="<< std::endl; }
	B& operator=(B&& rhs){ m_a = std::move( rhs.m_a ); std::cout << "B:=move" << std::endl;}
};


int main()
{
	B b;
	B c = b;
	B d = std::move(b);
	return 0;
}
