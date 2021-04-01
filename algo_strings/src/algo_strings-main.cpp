#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <list>
#include <algorithm>
#include <optional>  // needs C++ 17, see CMakefile

/* Optimal way to find duplicate chars in a string*/
void print_duplicates( const std::string& str )
{
	std::unordered_map<char, bool> char_hash;
	for( auto c : str )
	{
		if( char_hash.find(c) != char_hash.end() )
		{
			if( ! char_hash[c] )
			{
				std::cout << "duplicate [" << c << "]" << std::endl;
				char_hash[c] = true;
			}
		}
		else
			char_hash[c] = false;
	}
}

/*
 * Helper function that convert a string to a hash having
 *      key = character that exists in the string and
 *      value = a positive integer with number of occurences of that char
 *
 *      Note: the return by value of this function is optimized away by the compiler
 */
std::unordered_map<char, std::size_t> str_hash( const std::string& str )
{
	std::unordered_map<char, std::size_t> char_hash;
	std::for_each( str.begin(),
			str.end(),
			[&char_hash](const char c)
		{
			auto iter = char_hash.find(c);
			if( iter == char_hash.end() ){
				char_hash.insert( std::make_pair(c, static_cast<std::size_t>(1) ));
			}else{
				++ iter->second;
			}
		} );
	return char_hash;
}

/*
 * Optimal way to determine if 'anagram' is an anagram or 'str'
 * As "anagram" is comutative it work both ways: 'str' is anagram of 'anagram'
 */
bool is_anagram( const std::string& str, const std::string& anagram )
{

	/* remove this if str can contain other chars that not in anagram*/
	if( str.size() != anagram.size() )
		return false;

	std::unordered_map<char,std::size_t> str_h = str_hash( str );
	std::unordered_map<char,std::size_t> anagram_h = str_hash( anagram );

	std::unordered_map<char,std::size_t>::iterator str_iter = str_h.begin();
	std::unordered_map<char,std::size_t>::iterator anagram_iter = anagram_h.begin();

/*
 *  the below code will work only for std::map but not for std::unordered_map as
 *  although the both containers we are trying to compare may have the same {key/values},
 *  there is no guarantee the keys are in the same order for unordered map
 *  /

	while( str_iter != str_h.end() )
	{
		++ str_iter;
		++ anagram_iter;
		if( str_iter->first != anagram_iter->first || str_iter->second != anagram_iter->second )
			return false;
	}
*/
	for( auto pair : anagram_h )
	{
		std::unordered_map<char,std::size_t>::iterator find_iter = str_h.find( pair.first );
		if( find_iter == str_h.end() )
			return false;
		else
		{
			if(  ( find_iter->second != pair.second )
			  || ( find_iter->first != pair.first ) )
				return false;
		}
	}
	return true;
}

/* find first non repeating char in a string - optimal O(n), assuming hash map ( unordered list )
 * has O(1) insert/find time
 */
std::optional<char> find_first_non_repeating_char( const std::string& str )
{
	std::optional<char> ret_val;
	std::unordered_map<char,std::list<char>::iterator> appeared_once;
	std::unordered_set<char> appeared_mode_than_once;
	std::list<char> ordered_appeared_once;


	for( auto c : str )
	{
		if( appeared_mode_than_once.find(c) == appeared_mode_than_once.end() )
		{
			if( appeared_once.find(c) == appeared_once.end() )
			{
				ordered_appeared_once.push_back(c);
				std::list<char>::iterator last_element_iter = std::prev(ordered_appeared_once.end());
				appeared_once[c] = last_element_iter;
			}
			else
			{
				ordered_appeared_once.erase(appeared_once[c]);
				appeared_once.erase(c);
				appeared_mode_than_once.insert(c);
			}
		}
	}

	if( ! ordered_appeared_once.empty() )
	{
		ret_val = *( ordered_appeared_once.begin() );
	}

	return ret_val;
}

// simple reversing string using recursive function
std::string reverse_string_recursive( const std::string& str )
{
	if( str.size() > 1 )
	{
		return reverse_string_recursive( str.substr(1) ) + str[0];
	}
	else
		return str;
}

// find middle element of a linked list in one iteration
template<class T>
T middle_element( const std::list<T>& strlist )
{
	typename std::list<T>::const_iterator current_iter = strlist.cbegin();
	typename std::list<T>::const_iterator middle_iter = strlist.cbegin();

	size_t middle_position = 0;
	size_t processed = 0;
	for( ; current_iter != strlist.end(); ++ current_iter )
	{
		++ processed;
		while( middle_position < processed / 2  )
		{
			++ middle_position;
			++ middle_iter;
		}
	}
	return *middle_iter;

}

int main()
{
	print_duplicates("aaabcddeffgag" );
	std::cout << "--------------------------------------------" << std::endl;
	std::string s1 = "abc";
	std::string s2 = "cba";
	std::string s3 = "aca";
	std::string s4 = "axbc";
	std::cout << s2 << " is anagram of " << s1 << " = " << is_anagram( s1, s2 ) << std::endl;
	std::cout << s3 << " is anagram of " << s1 << " = " << is_anagram( s1, s3 ) << std::endl;
	std::cout << s4 << " is anagram of " << s1 << " = " << is_anagram( s1, s4 ) << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
	std::string schar = "ababcddsefc";
	std::optional<char> optional_value = find_first_non_repeating_char( schar );
	if( optional_value.has_value() )
	{
		std::cout << "first non repeating char of " << schar << " is " << *( optional_value ) << std::endl;
	}
	else
	{
		std::cout << "no such char " << std::endl;
	}
	std::cout << "--------------------------------------------" << std::endl;
	std::cout << "reverse string "<< schar << " recursive " << reverse_string_recursive( schar ) << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
	std::list<char> char_list;
	std::string strorder = "abcdefghijk";
	std::copy( strorder.begin(), strorder.end(), std::back_inserter( char_list ));
	std::cout << "middle element of " << strorder << " is: " << middle_element( char_list ) << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
	return 0;
}
