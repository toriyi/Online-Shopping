#include "movie.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

//movie constructor has to call the product constructor 
Movie::Movie(const std::string name, double price, int qty, string genre, string rating) 
	: Product("movie", name, price, qty) {
		Genre = genre;
		Rating = rating;
}

//calls the parseStringToWords function in product 
//to get the individual keywords 
std::set<std::string> Movie::keywords() const {
	string key = Genre +" " + name_;  
	std::set<std::string> word = parseStringToWords(key);
	return word;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Movie::displayString() const {
	stringstream ss;
	ss << name_<<std::endl;
	ss << "Genre:" << " " << Genre << " " << "Rating: " << Rating << std::endl;
	ss << price_ << " " << qty_ << " " <<"Left" << std::endl;
	return ss.str(); 
}

/**
 * Outputs the product info in the database format
 */
void Movie::dump(std::ostream& os) const{
	Product::dump(os);
	os << Genre << endl;
	os << Rating << endl;
}