#pragma once

#include <chrono>


#define NUM_EXECUTION_TO_AVERAGE 10

#define BEGIN_PERFORMANCE_BLOCK( __NAME__ ) \
		{ \
		   std::string  block_name = #__NAME__; \
		   size_t sum_durations = 0; \
           for( size_t i  = 0; i < NUM_EXECUTION_TO_AVERAGE; ++i ) { \
        	   auto t1 = std::chrono::high_resolution_clock::now(); {


#define END_PERFORMANCE_BLOCK } \
				auto t2 = std::chrono::high_resolution_clock::now(); \
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count(); \
				sum_durations+=duration; \
				} \
			std::cout << "Average duration of " << block_name << " = " << sum_durations / NUM_EXECUTION_TO_AVERAGE << " microseconds" << std::endl; \
			}
