#include "clothing.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

//clothing constructor has to call the product constructor 
Clothing::Clothing(const std::string name, double price, int qty, string sizes, string brand) 
	: Product("clothing", name, price, qty) {
		Sizes = sizes;
		Brand = brand;
}

//calls the parseStringToWords function in product 
//to get the individual keywords 
std::set<std::string> Clothing::keywords() const {
	string key = Brand + " " + name_;  
	std::set<std::string> word = parseStringToWords(key);
	return word;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Clothing::displayString() const {
	stringstream ss;
	ss << name_<<std::endl;
	ss << "Sizes:" << " " << Sizes << " " << "Brand: " << Brand << std::endl;
	ss << price_ << " " << qty_ << " " << "Left" << std::endl;
	return ss.str(); 
}

/**
 * Outputs the product info in the database format
 */
void Clothing::dump(std::ostream& os) const{
	Product::dump(os);
	os << Sizes << endl;
	os << Brand << endl;
}