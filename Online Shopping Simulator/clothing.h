#ifndef CLOTHING_H
#define ClOTHING_H

#include <string>
#include "product.h"
#include "util.h"

//derived clothing class
//two extra data members are sizes and the brand
class Clothing : public Product {
	public:
		Clothing(std::string name, double price, int qty, std::string sizes, std::string brand);
		std::set<std::string>keywords() const ;
		std::string displayString() const;
		void dump(std::ostream& os) const; 

	private:
		std::string Sizes;
		std::string Brand; 
};

#endif