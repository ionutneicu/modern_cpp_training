#include <iostream>
#include <future>
#include <vector>


/* Copyright 2020-2021 Ionut Neicu
 * See License.txt for copyright and disclaimer 
 *
 * This program demonstrates the possible inconsistency 
 * when using thread_local with async.
 * This because async with default launc policy won't guarantee the
 * creation of a separate thread.
 * This can be tuned by using explicit launch policy as in this example
 * first 5 async tasks are deffered so won't execute in the separate thread,
 * the next 5 will execute in a separate thread.
 * Not passing launch policy will let system choose whether to start new thread
 * or defer the task into main thread producing inconsistent results
 * if thrad_local variable are involved*/

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
