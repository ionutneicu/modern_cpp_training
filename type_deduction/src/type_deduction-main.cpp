// Example program
#include <iostream>
#include <string>
#include <functional>
#include <initializer_list>


template < typename T, const std::size_t N >
constexpr const std::size_t size_of_array(  T(&)[N] ) noexcept
{
    return N;
}


template <typename T>
int f( T& arg )
{
	/*
	 *  There is ambiguity on pointer and array types when passed as template
	 *  The below code would work for both pointer and array except
	 *  for size_of_array() that requires array[N]
	 */

    int i;
    for( i = 0; i < size_of_array(arg); ++i )
    {
        std::cout << i << "." << arg[i] << std::endl;
    }
    return i;
}

template <typename T>
int g( T& arg , std::size_t N)
{
	/*
	 *  The version of f that works with pointers, needs extra size arg
	 */

    int i;
    for( i = 0; i < N; ++i )
    {
        std::cout << i << "." << arg[i] << std::endl;
    }
    return i;
}

int main() {

	/*
	 * the following lines are for arrays
	 *
	 */

	char c[] = "Hello world";
	int r[] = {1,2,3,4};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
	char* x = "abc";
#pragma GCC diagnostic pop

    std::cout << "size of array=" << size_of_array(c) << std::endl;
    f(c);
    std::cout << "size of array=" << size_of_array(r) << std::endl;
    f(r);

    /*
     * The above line won't work for pointers,
     * but g() should work at expense of an extra arg
     *
     * 		std::cout << "size of array=" << size_of_array(x) << std::endl;
     * 		f(x);
     */

    g(x, 4);

    // the type of "a" is "initializer_list"
    // the <initializer_list> header must be included directl or indirectly
    auto a = {1,2,3,4};

    return 0;
}
