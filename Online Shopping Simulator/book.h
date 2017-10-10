#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "product.h"
#include "util.h"

//derived book class
//two extra data members are isbn and the author 
class Book : public Product {
	public:
		Book(std::string name, double price, int qty, std::string isbn, std::string author);
		std::set<std::string>keywords() const ;
		std::string displayString() const;
		void dump(std::ostream& os) const; 

	private:
		std::string ISBN;
		std::string Author;
};

#endif
