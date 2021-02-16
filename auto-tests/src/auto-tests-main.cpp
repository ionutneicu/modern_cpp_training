#include <iostream>
#include <sstream>
#include <map>
#include <string>

#include "perf-measurement.h"

int main()
{
	std::map< int, std::string > my_map;
	for( int i = 0; i < 1000000; ++ i )
	{
		std::ostringstream stringi;
		stringi << "String " << i;
		my_map.insert( std::make_pair( i, stringi.str()) );
	}
	size_t sum = 0;
	// it should be const std::pair<const int, std::string> otherwise
	// a temporary value is being created causing slower performance
	BEGIN_PERFORMANCE_BLOCK( read_with_no_auto )
	for( const std::pair<int, std::string>& i : my_map )
	{
		sum += i.first;
	}
	END_PERFORMANCE_BLOCK
	// using auto leads to best performance

	BEGIN_PERFORMANCE_BLOCK( read_with_auto )
	for( const auto & i : my_map )
	{
			sum += i.first;
	}
	END_PERFORMANCE_BLOCK

	return 0;
}
