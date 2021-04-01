#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <list>
#include <queue>
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

	// assuming there is a "true" linked list, we cannot use size
	// otherwise it would be something like
	// std::advance( middle_iter,  strlist.size() / 2 )
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

/* Optimal check palindrome with minimum iterations
 * It could be implemented with random access [] operator on vector and string
 * Or like below with reversible iterators on vector, string, doubly-linked lists
 */
bool check_string_palindrome( const std::string& candidate )
{
	std::string::const_iterator fwd_iter = candidate.cbegin();
	std::string::const_iterator backward_iter = candidate.cend();

	while( fwd_iter != candidate.cend() )
	{
		std::advance( backward_iter, -1 );

		if( backward_iter == candidate.end()  )
			return false;

		if( backward_iter == fwd_iter )
			break;
		//std::cout << "fwd = " << *fwd_iter << " bwd = " << *backward_iter << std::endl;
		if( *fwd_iter != * backward_iter )
			return false;

		std::advance( fwd_iter, 1 );
	}
	return true;
}


/*
 * get the maximum sequence of 2 characters
 */


bool queue_add( std::list<char>& aqueue, const char chr )
{
	std::list<char>::const_iterator found = aqueue.end();

	for( std::list<char>::const_iterator q = aqueue.begin(); q != aqueue.end(); ++ q )
	{
		if( *q == chr )
			found = q;
	}

	// make sure it gets the last
	// remove it
	if( found != aqueue.end() )
	{
		aqueue.erase(found);
		aqueue.push_back( chr );
		return false;
	}
	// append it:
	aqueue.push_back( chr );
	while( aqueue.size() > 2 )
	{
		aqueue.pop_front();
	}
	return true;
}

/*
 * Gets the longest substring made of 2 chars in a given string
 * It keeps 2 pointers( iterators ) in the string, pointing to:
 * (1.) where the last repeating 2 char sequence started
 * (2.) where the last repeating 1 char sequence started
 *
 * It keeps a list of maximum 2 chars containing the last 2 distinct chars
 * The list is ordered, so last encountered char is always last
 *
 * If new char that is not in the list, this is checked by queue_add() :
 *   - the list is updated so the first char is removed, new char added at the end
 *   - the size of last repeating seq is std::distance( (1), (2) )
 *     it higher that the maximum known, is kept
 *   - the the pointer(1) is updated with pointer(2)
 *   - the pointer (2) is updated with the position of the new char
 * If  char is in the 2 char list, but not last, it is moved at the end of the list by queue_add()
 * At the end of the string, additional check is made to detect the longest sequence
 *
 * Known issue ( std::distance() has performance penalty so it must be avoided.
 * External counter to be added instead of std::distance(), i.e. how many chars have
 * added since last queue change )
  */

std::size_t get_max_seq_of_two_chars( const std::string& str )
{
	std::list<char> last_2_chars; // must stay at maximum 2 chars
	std::string::const_iterator begin_of_last_2_chars  = str.begin();
	std::string::const_iterator begin_of_last_char 	   = str.begin();
	std::string::const_iterator current = str.begin();
	std::size_t max_seq = 0;
	char last_char = *begin_of_last_char;
	while( current != str.end() )
	{
		//std::cout << "******" << std::endl;
		//std::cout << "current = " << *current << std::endl;
		if( last_char != *current )
		{
				//std::cout << "last char = " << last_char << std::endl;

				// already a sequence of 2 chars
				int prev_size = last_2_chars.size();
				if(  queue_add( last_2_chars, *current ) )
				{
					if( prev_size == 2 )
					{
						/* std::distance to be optimized away*/
						std::size_t distance = std::distance(begin_of_last_2_chars, current);
						//std::cout << "last 2 chars changed length of seq was: " << distance << " " << std::string( begin_of_last_2_chars, current) << std::endl;
						if( distance > max_seq )
							max_seq = distance;

						begin_of_last_2_chars = begin_of_last_char;
					}
				}

			begin_of_last_char = current;
			last_char = *current;
		}

		++ current;

		if( current == str.end() )
		{
			std::size_t distance = std::distance(begin_of_last_2_chars, current);
			//std::cout << "last 2 chars changed length of seq was: " << distance << " " << std::string( begin_of_last_2_chars, current) << std::endl;
			if( distance > max_seq )
				max_seq = distance;
		}
	}
	return max_seq;
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

	std::string palindrome = "abcdcba";
	std::string non_palindrome = "abcdaba";
	std::cout << "check string palindrome " << palindrome << " : " << check_string_palindrome( palindrome ) << std::endl;
	std::cout << "check string palindrome " << non_palindrome << " : " << check_string_palindrome( non_palindrome ) << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

	std::string seq_string = "ababcdeedecab";
	std::cout << "max seq of 2 chars of " << seq_string << " = " << get_max_seq_of_two_chars( seq_string ) << std::endl;
	std::string seq_string2 = "ababcdeedecabzzwzww";
	std::cout << "max seq of 2 chars of " << seq_string2 << " = " << get_max_seq_of_two_chars( seq_string2 ) << std::endl;
	std::string seq_string3 = "zzwzwwababcdeedecab";
	std::cout << "max seq of 2 chars of " << seq_string3 << " = " << get_max_seq_of_two_chars( seq_string3 ) << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
	return 0;
}
