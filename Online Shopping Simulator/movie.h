#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include "product.h"
#include "util.h"

//derived movie class
//two extra data members are genre and rating  
class Movie : public Product {
	public:
		Movie(std::string name, double price, int qty, std::string genre, std::string rating);
		std::set<std::string>keywords() const ;
		std::string displayString() const;
		void dump(std::ostream& os) const; 

	private:
		std::string Genre;
		std::string Rating;
};

#endif