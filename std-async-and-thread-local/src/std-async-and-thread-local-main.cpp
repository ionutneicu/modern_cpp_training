#include <iostream>
#include <future>
#include <vector>

thread_local int x = -1;


int my_function( int i )
{
	if( x == -1 )  // if thread is new
	      x = i;
	else
	      x = i+1;
	return x;
}


int main()
{
	constexpr size_t NUM_FUTURES=10;
	std::vector< std::future<int> > async_futures(NUM_FUTURES);
	for( int i = 0; i < NUM_FUTURES; ++i )
	{
		if( i < NUM_FUTURES/2 )
			async_futures[i] =std::async( std::launch::deferred , my_function, i );
		else
			async_futures[i] = std::async( std::launch::async , my_function, i );
		//async_futures[i] = std::async(  my_function, i );
	}

	for( int i = 0; i < NUM_FUTURES; ++ i )
	{
	      	int expected_value = async_futures[i].get();
	      	std::cout << " final result " << i << " = " << expected_value <<  ( ( i == expected_value ) ? " GOOD" : " BAD"  ) << std::endl;
	}
	return 0;
}
