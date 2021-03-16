#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <functional>
#include <type_traits>
#include <vector>

/*
 * This example illustrates one possible implementation
 * of std::async( std::launch_policy::async, ... ) called launch_async
 * It uses varidic templates to accommodate a variable number of arguments.
 */

#ifdef CXX_11
//
//  https://stackoverflow.com/questions/33436336/capture-stdpromise-in-a-lambda-c14"
//  C++11 does not allow mutable in lambdas so parameters must be copied ?
//
template <typename T>
struct destructive_copy_constructible
{
    mutable T value;

    destructive_copy_constructible() {}

    destructive_copy_constructible(T&& v): value(std::move(v)) {}

    destructive_copy_constructible(const destructive_copy_constructible<T>& rhs)
        : value(std::move(rhs.value))
    {}

    destructive_copy_constructible(destructive_copy_constructible<T>&& rhs) = default;

    destructive_copy_constructible&
    operator=(const destructive_copy_constructible<T>& rhs) = delete;

    destructive_copy_constructible&
    operator=(destructive_copy_constructible<T>&& rhs) = delete;
};

template <typename T>
using dcc_t =
    destructive_copy_constructible<typename std::remove_reference<T>::type>;

template <typename T>
inline dcc_t<T> move_to_dcc(T&& r)
{
    return dcc_t<T>(std::move(r));
}

#endif

int f( int x, float y, std::string z )
{
	return x + (int)y + z.length();
}

std::string update_string( const std::string& x )
{
	return x + "_updated";
}


// My implementation of std::async:

template<class CallableT, class ...Ts>
std::future< std::result_of_t<CallableT(Ts...)> >
launch_async( CallableT callable, Ts... args )
{

	std::promise< std::result_of_t<CallableT(Ts...) > > p;
	std::future< std::result_of_t <CallableT(Ts...) > > ff = p.get_future();
	std::thread th( [ pr{std::move(p)}, callable, args...]() mutable {
					//using namespace std::chrono_literals;
		 	 	 	//std::this_thread::sleep_for(1s);
					pr.set_value( callable( args... ) );
			} );
	th.detach();
	return ff;
}


template<class MemberType, class ...Ts>
std::vector<MemberType> make_me_a_vector_of( Ts... args )
{
	return std::vector<MemberType>{ args... };
}




int main()
{
	auto async_result1 = launch_async(update_string, "a");
	async_result1.wait();
	std::cout << "result1 = " << async_result1.get() << std::endl;

	auto async_result2 = launch_async(f, 1, 2.0, "abc");
	async_result2.wait();
	std::cout << "result2 = " << async_result2.get() << std::endl;

	/*
	 * Another way to initialize a vector
	 */
	auto v = make_me_a_vector_of<int>( 2.1, 1.2, 2, 3, 5 );

	for( auto element: v )
	{
		std::cout << "Int element v=" << element << std::endl;
	}

	auto v2 = make_me_a_vector_of<float>( 2.1, 1.2, 2, 3, 5 );

	for( auto element: v2 )
	{
		std::cout << "Float element v=" << element << std::endl;
	}

	return 0;
}
