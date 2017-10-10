#include <sstream>
#include <iomanip>
#include "product.h"
#include "review.h"

using namespace std;

Product::Product(const std::string category, const std::string name, double price, int qty) :
    name_(name),
    price_(price),
    qty_(qty),
    category_(category)
{

}

Product::~Product()
{
    for(unsigned int j = 0; j < reviews.size(); j++){
        delete reviews[j];
    }
}


double Product::getPrice() const
{
    return price_;
}

std::string Product::getName() const
{
    return name_;
}

void Product::subtractQty(int num)
{
    qty_ -= num;
}

int Product::getQty() const
{
    return qty_;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Product::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

void Product::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}
//adds the passed in review to the product's 
//reviews vector 
void Product::addReview(Review * r){
    reviews.push_back(r);
}
//gets the full vector of that product's reviews 
std::vector<Review*> Product::getReviews(){
    return reviews;
}
//averages all of the reviews for the products 
//if a product has no reviews then it will just have an average of 0 
double Product::averageReviews(){
    int sum = 0;
    int count = 0;
    std::vector<Review*> reviews = getReviews();
    if(reviews.size() == 0){
        sum = 0;
        count = 1;
    }
    else{
        for(unsigned int i = 0; i<reviews.size(); i++){
            sum += reviews[i]->rating;
            count++;
        }
    }
    return (double) sum/count;
}


