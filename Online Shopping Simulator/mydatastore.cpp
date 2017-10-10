#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <map>
#include <cmath>
#include <limits>
#include <iomanip>
#include "mydatastore.h"
#include "datastore.h"
#include "util.h"
#include "product.h"
#include "user.h"
#include "review.h"
#include "heap.h"
#include "msort.h"
using namespace std;


//constructor 
MyDataStore::MyDataStore(){

}

//destructor
//goes through the vector of Product*
//and the vector of User* and deletes  
MyDataStore::~MyDataStore(){
	for(unsigned int i = 0; i < products.size(); i++){
		delete products[i];
	}
	for(unsigned int j = 0; j < users.size(); j++){
		delete users[j];
	}
	for(unsigned int x = 0; x < reviews.size(); x++){
		delete reviews[x];
	}
}

/**
 * Adds a product to the data store
 * adds the string key and its corresponding set of Product*
 * to the map map_p and the Product* is pushed pack 
 * to the products vector 
 */
void MyDataStore::addProduct(Product* p){
	products.push_back(p);
	std::set<std::string> keys = p->keywords(); 
	std::set<std::string>::iterator it; 
	for(it=keys.begin(); it!=keys.end(); ++it){
		if(map_p.find(*it) != map_p.end()){
			map_p.find(*it)->second.insert(p);
		}
		else{
			std::set<Product*> found;
			found.insert(p);
			map_p.insert(make_pair(*it, found));
		} 
	}
}

/**
 * Adds a user to the data store
 * adds a string name and its corresponding User*
 * to the map map_u and the User* is pushed back
 * to the users vector 
 */
void MyDataStore::addUser(User* u){
	users.push_back(u);
	std::string keys = u->getName();
	map_u.insert(make_pair(keys,u));
}

// //added this
// void MyDataStore::addUserLogin(User* u){
	
// }

//added this
std::string MyDataStore::chooseUser(std::string username){
	return username;
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 * iterates through map_p to find the first matching set of Product* to the
 * specified term and then loop through the rest of the terms
 * to search for matches between terms and the sets in map_p
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
	vector<Product*> p;
	std::set<Product*> set_nt;
	if (map_p.find(terms[0])!=map_p.end())
		set_nt = (map_p.find(terms[0])->second);
	for (unsigned int i=0; i<terms.size(); i++){
		if(map_p.find(terms[i]) != map_p.end()){
			if(type == 0){
				set_nt = setIntersection(set_nt,map_p.find(terms[i])->second);
			}
			if(type == 1){
				set_nt = setUnion(set_nt,map_p.find(terms[i])->second);
			}
		}
	}
    std::set<Product*>::iterator it; 
    for(it=set_nt.begin(); it!=set_nt.end(); ++it){
    	p.push_back(*it);
    }
    return p;
}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile){
	ofile << "<products>" << endl;
	for(unsigned int i=0; i<products.size(); i++){
		products[i]->dump(ofile);
	}
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;
	for(unsigned int j=0; j<users.size(); j++){
		users[j]->dump(ofile);
	}
	ofile << "</users>" << endl;
	ofile << "<review>" << endl;


	//will print all the reviews 
	for(unsigned int i=0; i<products.size(); i++){
		Product* p = products[i];
		std::vector<Review*> reviews = p->getReviews();
		for(unsigned int x=0; x<reviews.size(); x++){
			ofile << reviews[x]->prodName << endl;
			ofile << reviews[x]->rating << " " << reviews[x]->username << " " << reviews[x]->date 
			<< " " << reviews[x]->reviewText << endl;
		}
	}
	std::cout << endl;
	ofile << "</review>" << endl;
}
//will pass in a review and add it to the map of reviews
//will also find the review's corresponding product
//if it has one and add it to that product 
//by calling the addReview function and passing in the review 
void MyDataStore::addReview(Review* r){
	reviews.push_back(r);
	std::string key = r->prodName; 
	for(unsigned int i = 0; i < products.size(); i++){
		if(products[i]->getName() == key){
			products[i]->addReview(r);
		}
	}
	if(map_r.find(key) != map_r.end()){
		map_r.find(key)->second.push_back(r);	
	}
	else {
		vector<Review*> found;
		found.push_back(r);
		map_r.insert(make_pair(key,found));
	}
}
//adds product p to the cart that belongs to name
//looks through the cart to find the name 
//and either just inserts the product into an
//existing cart or creates and inserts into a whole
//new cart for someone 
void MyDataStore::addCart(std::string name, Product* p){
	if(map_u.find(name) == map_u.end()){
		cout << "Invalid request" << endl;
		return;	
	}

	std::map<std::string, std::vector<Product*> >::iterator it = cart.find(name);
	if(it != cart.end()){
		it->second.push_back(p);	
	}
	else {
		vector<Product*> prod;
		prod.push_back(p);
		cart.insert(make_pair(name,prod));
	}
}
//will pass in a nae of the user and the selected product's
//index that needs to be deleted from the user's cart 
void MyDataStore::removeCart(std::string name, unsigned int index){
	if(map_u.find(name) == map_u.end()){
		cout << "Invalid request" << endl;
		return;	
	}
	std::map<std::string, std::vector<Product*> >::iterator it = cart.find(name);
	if(index < it->second.size()){
    	it->second.erase(it->second.begin()+index);
    }
}

//iterates through items in a user's cart 
//if item is in stock the user has enough money
//then will remove from the cart
//and the stock quantity should be reduced by one
//and the price should be debited from the user's credit
void MyDataStore::buyCart(std::string name){
	std::map<std::string, std::vector<Product*> >::iterator it = cart.find(name);
	User* user;
	if(map_u.find(name) == map_u.end()){
		cout << "Invalid username" << endl;
		return;	
	}
	else{
		std::vector<Product*> pr = it->second;
		std::map<std::string, User* >::iterator itr = map_u.find(name); 
		if (itr != map_u.end()){
			user = itr->second; 
		}
	}
	std::vector<Product*> pi = it->second;
	std::vector<Product*> nc;	
	std::vector<Product*>:: iterator pro = pi.begin();
	for(pro = pi.begin(); pro != pi.end(); ++pro){
		Product* p = (*pro);
		if(p->getQty() > 0 && user->getBalance() >= p->getPrice()){
			p->subtractQty(1);
			user->deductAmount(p->getPrice());
		}
		else{
			nc.push_back(p);
		}
	}
	it->second = nc;
}

//views the items in the requested person's cart 
//iterates through it and assigns item values
//to them in the order they are added 
void MyDataStore::viewCart(std::string name){
	if(map_u.find(name) == map_u.end()){
		cout << "Invalid username" << endl;
		return;	
	}
	int count = 1;
    std::map<std::string, std::vector<Product*> >::iterator iter; 
    for(iter = cart.begin(); iter != cart.end(); ++iter){
        std::vector<Product*> pr = iter->second; 
        std::vector<Product*>::iterator print = pr.begin();
        for(print = pr.begin(); print!=pr.end();++print){
        	cout << "Item " << count << endl;
            cout << (*print)->displayString();
            count++;
        }
    } 
}

//takes in two users and returns a double which is the similarity value bt those users 
double MyDataStore::calculateBasicSimilarities(std::string user1, std::string user2){
	std::map<std::string, std::pair<int,int> > basicSim;
	double similarity = 0;
	for(unsigned int i = 0; i < reviews.size(); i++){
		if(reviews[i]->username == user1){
			std::map<std::string, std::pair<int, int> > ::iterator it = basicSim.find(reviews[i]->prodName);
			if (it == basicSim.end())
			{
				basicSim[reviews[i]->prodName] = std::make_pair(reviews[i]->rating, -1);
			}
			else
			{
				it->second.first = reviews[i]->rating;
			}
		}

		if(reviews[i]->username == user2){
			std::map<std::string, std::pair<int, int> > ::iterator it = basicSim.find(reviews[i]->prodName);
			if (it == basicSim.end())
			{
				basicSim[reviews[i]->prodName] = std::make_pair(-1, reviews[i]->rating);
			}
			else
			{
				it->second.second = reviews[i]->rating;
			}
		}
	}

	int numProducts = 0;

	std::map<std::string, std::pair<int,int> >::iterator bSim;
	for(bSim = basicSim.begin(); bSim != basicSim.end(); ++bSim){
		if (bSim->second.second != -1 && bSim->second.first != -1)
		{
			similarity += abs(bSim->second.first - bSim->second.second)/4.0;
			++numProducts;
		}	
	}

	return (numProducts == 0) ? 1 : similarity/numProducts;
}

//returns a map with the current user and a map with another user and their similarity value 
std::map<std::string, std::map<std::string, double> > MyDataStore::returnMap(){
	vector<User*> u = getUser();
	for(unsigned int i = 0; i < u.size(); i++){
		for(unsigned int j = 0; j < u.size(); j++){

			if(u[i]->getName() != u[j]->getName()){
				double similar = calculateBasicSimilarities(u[i]->getName(),u[j]->getName());
				basic.insert(std::make_pair(u[i]->getName(), std::map<std::string, double>()));
				if(basic.find(u[i]->getName()) != basic.end()){
					basic[u[i]->getName()].insert(std::make_pair(u[j]->getName(), similar));				
				}
			}//ends if
		}
	}

	return basic;
}

//runs dijkstras and finds the shortest path for the users 
std::map<std::string, double> MyDataStore::refineSimilarityEstimates(std::string currentuser){

	std::map<std::string, double> refinedSims;
	std::map<std::string, std::map<std::string, double> > basic = returnMap();

	Heap<string> dijkstra;
	
	dijkstra.push(0, currentuser);
	refinedSims.insert(std::make_pair(currentuser, 0));
	
	vector<User*> u = getUser();

	// stores basic similarities between current user and all other users
	if(basic.find(currentuser) == basic.end()){
		//set user distance to number of users 
		refinedSims.insert(std::make_pair(currentuser, u.size()));
	}
	else{
		std::map<std::string, double> start = basic.find(currentuser)->second;
		for(std::map<std::string, double>::iterator it = start.begin();
			it != start.end(); ++it){
			dijkstra.push(it->second, it->first);
			refinedSims.insert(std::make_pair(it->first, it->second));

		}//ends for
		
	}

	while(!dijkstra.empty()){
		std::string user = dijkstra.top();
		dijkstra.pop();
		std::map<std::string, double> neighbors = basic.find(user)->second;
		//added this
		// iterates through neighbors
		std::map<std::string, double>::iterator it;
		for(it = neighbors.begin(); it != neighbors.end(); ++it){	
			//added
			if(it->second > 1){
				break;
			}
			//
			double weight = it->second;	// edge weight from user to neighbor
			if((refinedSims[user] + weight) < refinedSims[it->first]){
				refinedSims[it->first] = refinedSims[user] + weight; 
				dijkstra.decreaseKey(refinedSims[it->first], it->first);
			}
		}
	}
	
	return refinedSims;
}

//reccomendations made for products the current user has not reviewed 
std::vector<std::pair<std::string, double> > MyDataStore::makeSuggestion(std::string currentUser){

	std::map<std::string, double> refinedSims = refineSimilarityEstimates(currentUser);
	// holds names of all products that current user has already reviewed
	std::set<std::string> currentUserProd;
	for(unsigned int h = 0; h < reviews.size(); h++){
		if(currentUser == reviews[h]->username){
			currentUserProd.insert(reviews[h]->prodName);
		}
	}//ends for

	// map of product names to the set of users that reviewed that product
	std::map<std::string, std::set<std::string> >map_prodtouser;
	
	std::map<std::string, std::vector<Review*> >::iterator map_reviews;
	for(map_reviews = map_r.begin(); map_reviews!= map_r.end(); ++map_reviews){
		string prodName = map_reviews->first;
		if(currentUserProd.find(prodName) == currentUserProd.end()){		
			std::set<std::string> otherUsers;	
			for(unsigned int i = 0; i < map_reviews->second.size(); ++i){
				if(map_reviews->second[i]->username != currentUser){
					// if the main user hasn't reviewed this product yet,  
					// add the other user's name to the set of usernames 
					if(currentUserProd.find(map_reviews->second[i]->username) == currentUserProd.end()){
						otherUsers.insert(map_reviews->second[i]->username);
					}
				}
			}
			map_prodtouser[map_reviews->first] = otherUsers;
		}
	}

	//added this
	std::vector<std::pair<std::string, double> > productRating;
	//

	// for each product, go through each user who reviewed this product (other than our current user),
	// and calculate (1-s)*r

	std::map<std::string, std::set<std::string> >::iterator mProd;
	for(mProd = map_prodtouser.begin(); mProd != map_prodtouser.end(); ++mProd){
		string prodName = mProd->first;
		std::set<std::string> usernames = mProd->second;
		// product_rev contains all of the reviews for this product
		vector<Review*> product_rev;
		for(unsigned int i = 0; i < products.size(); i++){
			if(prodName == products[i]->getName()){
				product_rev = products[i]->getReviews();
			}
			
		}
		double rpSum = 0;
		double wSum = 0;

		// iterates through set of users corresponding to current product

		std::set<std::string>::iterator userN;
		for(userN = usernames.begin(); userN != usernames.end(); ++userN){
			string username = *userN;
			// refined similarity between our user and the current user 
			double sim = refinedSims.find(username)->second;	

			for(unsigned int i = 0; i < product_rev.size(); i++){
				if(product_rev[i]->username == username){
					double rate = product_rev[i]->rating;
					rpSum += (1-sim)*rate;
					wSum += (1-sim);
				}
			}		
		}	

		double rating = (wSum == 0) ? 0 : rpSum/wSum;

		//added this
		if(rpSum == 0 || wSum == 0){ 
			productRating.push_back(std::make_pair(mProd->first, 0));			
		}
		else{
			std::cout<<std::fixed<<std::setprecision(2)<<rating;
			productRating.push_back(std::make_pair(mProd->first, rating));
		}

	}

	//comparator
	CompareRate cr;
	mergeSort (productRating, cr);
	return productRating;
}

//will print into a file 
void MyDataStore::dumpReviews(std::ostream& os, std::string user){
	std::vector<std::pair<std::string, double> > dumped = makeSuggestion(user);
	std::vector<std::pair<std::string, double> >::iterator it;
    os << user << std::endl;
    for(std::vector<std::pair<std::string, double> >::iterator it = dumped.begin(); 
    	it != dumped.end(); ++it){
    	os << std::fixed<<std::setprecision(2) << it->second << " " << it->first << std::endl;
    }
}