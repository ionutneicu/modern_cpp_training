#include <iostream>
#include <thread>
#include <future>
#include <iostream>
#include <chrono>


// global object
static int a;

using namespace std::chrono_literals;



static void do_work(std::promise<void> barrier1, std::promise<void> barrier2)
{


    std::this_thread::sleep_for(1s);
    a = 1;
    barrier1.set_value();
    std::this_thread::sleep_for(3s);
    a = 2;
    barrier2.set_value();
}


int main()
{

	{
		// using promises<void> as barrier to synchronize a global object
		// Across 2 threads
		std::promise<void> barrier1, barrier2;
		std::future<void> barrier_future1 = barrier1.get_future();
		std::future<void> barrier_future2 = barrier2.get_future();

		std::thread my_thread(do_work, std::move(barrier1), std::move(barrier2));
		barrier_future1.wait();
		// here a must be 1:
		std::cout << "a = " << a << std::endl;

		std::future_status status;
		do
		{
			std::cout << "waiting one second for future2..." << std::endl;
			status = barrier_future2.wait_for(500ms);

		}while( status != std::future_status::ready );

		barrier_future2.wait();
		// here a must be 2:
		std::cout << "a = " << a << std::endl;
		my_thread.join();
	}
	std::cout << "done" << std::endl;
	return 0;
}
