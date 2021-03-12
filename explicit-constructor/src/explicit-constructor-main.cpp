#include <iostream>
#include <vector>
#include <algorithm>

/* In this file will explore C++ implicit conversions and explicit constructors
 *
 * First, class A has one "conversion constructor" which allow A to be constructed as:
 *
 * A a = some_int;
 *
 * Deeper, pluses and minuses of this construction
 */

class A
{
protected:
	int m_i;
public:
	A() 			  = delete;
	A( const A& rhs ) = default;
	A( const int i )
		: m_i(i)
	{
		std::cout << "conversion ctor" << std::endl;
	}

	int get() const {return m_i;}
	A& operator ++() { ++m_i; return *this; }
	bool operator < ( const A& rhs )const { return m_i < rhs.m_i; }

};

class B : public A
{
public:
	B() 			  = delete;
	B( const B& rhs ) = default;
	B( const int i ):
		A( i )
	{

	}
	operator int() const { std::cout << "conversion back to int" << std::endl; return m_i; }
};

class C : public B
{
public:
	C() 			  = delete;
	C( const C& rhs ) = default;
	explicit C( const int i ):
		B( i )
	{

	}
};

void printA( A value )
{
	std::cout << "print A " << value.get() << std::endl;
}

void printB( B value )
{
	std::cout << "print B" << value.get() << std::endl;
}

void printC( C value )
{
	std::cout << "print B" << value.get() << std::endl;
}

//int operator=( const A& a ) const { return a.get(); }

int main()
{
	std::vector<int> v_int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	// calling conversion constructor of A 10 times for each vector:
	std::vector<A> v_a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<B> v_b{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};


	// the following for loop has several problems
	// 1. unwanted calling conversion constructor 10 times more in a<10 ?
	// 2. this won't work for B ( ambiguous overload for ‘operator<’ (operand types are ‘A’ and ‘int’) )
	for(  A a=1; a < 10 ; ++a )
	{
		std::cout << "value a(1)= " << a.get() << std::endl;

	}
	// possible way to overcome this?
	const A max_a = A{ 100 };
	for( A a = A{1}; a < max_a ; ++a )
	{
		std::cout << "value a(2)= " << a.get() << std::endl;
	}

	// works also for b
	const B max_b = B{ 100 };
	for(  B b = B{1}; b < max_b ; ++b )
	{
		std::cout << "value b(1)= " << b.get() << std::endl;
	}

	// the preferred and fastest way:
	for(  auto b : v_b )
	{
		std::cout << "value b(2)= " << b.get() << std::endl;
	}

	// the following loops are legal thanks to conversion constructors, but with some
	// performance penalty as it converts from vector element to a different type
	for( B b : v_int )
	{
		std::cout << "value b(3)= " << b.get() << std::endl;
	}

	for( int i : v_b )
	{
		std::cout << "value i= " << i << std::endl;
	}

	// the same loop won't convert in place int to C due explicit constructor
#if 0
	for( C c : v_int )
	{
		std::cout << "value c= " << c.get() << std::endl;
	}
#endif

	printA(1);
	printB(1);

	// for same reason, cannot call printC with an integer
#if 0
	printC(1);
#endif
	return 0;
}
