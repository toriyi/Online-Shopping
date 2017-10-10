#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <map>
#include "product.h"
#include "datastore.h"
#include "util.h"
#include "review.h"
#include "msort.h"
//need to reference DataStore  
class MyDataStore : public DataStore {
public:
	MyDataStore();
    ~MyDataStore();
    virtual void addProduct(Product* p);
    virtual void addUser(User* u); 
	virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);
    virtual void dump(std::ostream& ofile);

    virtual void addReview(Review* r);

    void addCart(std::string name, Product *p);
    void buyCart(std::string name);
    void viewCart(std::string name);

    void removeCart(std::string name, unsigned int index);

    //added this
    std::string chooseUser(std::string username);
    //

    double calculateBasicSimilarities(std::string user1, std::string user2);
	std::map<std::string, std::map<std::string, double> > returnMap();

	std::map<std::string, double> refineSimilarityEstimates(std::string currentuser);
	std::vector<std::pair<std::string, double> > makeSuggestion(std::string currentUser);
	
	void dumpReviews(std::ostream& os, std::string user);

	//ADDED THESE ACCESSOR METHODS 
	//gets the various users
	std::vector<User*> getUser(){
		return users;
	}
	//gets all the products in the database 
	std::vector<Product*> getProduct(){
		return products;
	}
	//gets the reviews for a certain product 
	std::vector<Review*> gr(std::string name){
		std::vector<Review*> n;
		if(map_r.find(name) != map_r.end()){
			n = map_r.find(name)->second;
		}
		return n;
	}
	//gets the cart for a certain user 
	std::vector<Product*> cart_products(std::string name){
		std::vector<Product*> n;
		if(cart.find(name) != cart.end()){
			n = cart.find(name)->second;
		}
		return n;
	}


	//added this
	std::map<std::string, User* > getMapUser(){
		return map_u; 
	}

	std::vector<Review*> getReviews(){
		return reviews;
	}

	
	//added this
	//comparator to compare the ratings highest to lowest 
	struct CompareRate{ 
		bool operator()(std::pair<std::string, double>  lhs, std::pair<std::string, double> rhs){
			return lhs.second > rhs.second;	
		}
	};


private:  
	std::map<std::string, std::set<Product*> > map_p; 
	std::map<std::string, User* > map_u; 
	std::vector<Product*> products;
	std::vector<User*> users;
	std::map<std::string, std::vector<Product*> > cart;
	// map from product names to a vector of corresponding reviews
	std::map<std::string, std::vector<Review*> > map_r;
	std::vector<Review*> reviews;

	//added this
	//map with user name and neighbor and distance bt two  
	std::map<double, std::pair<std::string, std::string> > map_distance;

	//added this
	// maps two users to basic similarity
	std::map<std::string, std::map<std::string, double> > basic;

};


#endif