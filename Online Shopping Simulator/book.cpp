#include "book.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

//book constructor has to call the product constructor 
Book::Book(const std::string name, double price, int qty, string isbn, string author) 
	: Product("book", name, price, qty) {
		ISBN = isbn;
		Author = author;

}

//calls the parseStringToWords function in product 
//to get the individual keywords 
std::set<std::string> Book::keywords() const {
	string key = Author + " " + name_;
	std::set<std::string> word = parseStringToWords(key);
	word.insert(ISBN);
	return word;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Book::displayString() const {	
	stringstream ss;
	ss << name_<<std::endl;
	ss << "Author:" << " " << Author << " " << "ISBN: " << ISBN << std::endl;
	ss << price_ << " " << qty_ << " " <<"Left" << std::endl;
	return ss.str(); 
}

/**
 * Outputs the product info in the database format
 */
void Book::dump(std::ostream& os) const{
	Product::dump(os);
	os << ISBN << endl;
	os << Author << endl;
}