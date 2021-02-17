#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <optional>


//  A more or less naive implementation of
//  Dining philosophers problem  -  https://en.wikipedia.org/wiki/Dining_philosophers_problem
//  Instantiate "fork" class in main() to highlight the problem
//  Instantiate "smart_fork" class in main() which provide one possible solution


#define NUM_FORKS 5

class philosopher;

class abs_fork
{
public:
	virtual bool acquire(philosopher& ph) = 0;
	virtual void release() = 0;
};


class fork : public abs_fork
{
	std::mutex m_mutex;
public:
	bool acquire( philosopher& ph )
	{
		m_mutex.lock();
		return true;
	}
	void release()
	{
		m_mutex.unlock();
	}
};


class smart_fork : public abs_fork
{
	std::mutex 		m_mutex;
	philosopher*	m_ph;
public:
	bool acquire( philosopher& ph )
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		if( m_ph != nullptr)
		{
			m_ph = &ph;
			return true;
		}
		else
		{
			return ( m_ph == &ph );
		}
	}
	void release()
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		m_ph = nullptr;
	}
};

class philosopher
{
	std::thread m_thread;
	std::string m_name;
	bool		m_run;
	abs_fork&		m_left_fork;
	abs_fork& 		m_right_fork;
public:
	philosopher(const std::string& name, abs_fork& left_fork, abs_fork& right_fork)
		: m_name( name ),
		  m_left_fork( left_fork ),
		  m_right_fork( right_fork )
	{
		m_run = true;
		std::thread thread( &philosopher::run, this );
		std:swap( m_thread, thread );
	}

	void run()
	{
		std::cout << "start " << m_name << std::endl;
		while( m_run )
		{
			eat();
			think();
		}
	}

	void eat()
	{
		std::cout << "eat start" << m_name << std::endl;
		if( m_left_fork.acquire( *this ) )
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10)); // adding this sleep actually triggers cyclic lock if fork is not "smart"
			if( m_right_fork.acquire( *this ) )
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				m_right_fork.release();
			}
		}
		m_left_fork.release();
		std::cout << "eat done " << m_name << std::endl;
	}

	void think()
	{
		std::cout << "think start" << m_name << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		std::cout << "think start" << m_name << std::endl;
	}

	~philosopher()
	{
		m_run = false;
		m_thread.join();
	}
};




int main()
{
	std::array<smart_fork, NUM_FORKS> forks;
	//std::array<fork, NUM_FORKS> forks;
	std::array<philosopher, NUM_FORKS> philosophers =
	{ {
			{ "philosopher_1", forks[4],  forks[0] },
			{ "philosopher_2", forks[0],  forks[1] },
			{ "philosopher_3", forks[1],  forks[2] },
			{ "philosopher_4", forks[2],  forks[3] },
			{ "philosopher_5", forks[3],  forks[4] },
	} };


	std::this_thread::sleep_for(std::chrono::seconds(100));
	std::cout << "done" << std::endl;
	return 0;
}
