#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates)  
 */

//since and is for sets in both set1 and set2 need to 
//check if in both sets and then insert into the new set 
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	typename std::set<T>:: iterator it;
	std::set<T> s3;
	for(it = s1.begin(); it != s1.end(); ++it){
	    if(s2.find(*it) != s2.end()){
	    	s3.insert(*it);
	    }
	}
	return s3;
}

//since or is for sets in either set1 or set2 then need 
//to go through both and insert into the new set 
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	typename std::set<T>:: iterator it;
	std::set<T> s3;
	for (it = s1.begin(); it!= s1.end(); ++it)
		s3.insert(*it);
	for (it = s2.begin(); it!= s2.end(); ++it)
		s3.insert(*it);
	return s3;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) ;

// trim from end
std::string &rtrim(std::string &s) ;

// trim from both ends
std::string &trim(std::string &s) ;
#endif
