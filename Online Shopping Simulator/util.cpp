#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
//used a count and index variable to 
//move the substring 
//used ispunct to check for punctuation
//and checked if the word is at least two letters 
std::set<std::string> parseStringToWords(string rawWords)
{

    std::set<string> rw;  
    string word;
    std::stringstream ss(rawWords);
    while(ss >> word){
        word = convToLower(word);
        int count = 0;
        int index = 0;
        string temp;
        temp = word;
        
        string nt = word;
        for(unsigned int i=0; i < word.size(); i++){
            if(!ispunct(word[i])){ 
                count++;
                nt = temp.substr(index,count); 
            }
            else{
                index = count + 1;
                word = word.substr(index,count);
                if(word.size()>=2){
                    rw.insert(word);
                }
                break;
            }

        }
        if(nt.size() >= 2){
            rw.insert(nt);
        }  
    }
    return rw;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
