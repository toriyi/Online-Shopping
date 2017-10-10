#include "msort.h"
#include <iostream>
using namespace std;
// void printing(vector<int>&i){
// 	for(unsigned int t = 0; t < i.size(); t++){
// 		cout << i[t] << " " << endl;
// 	}
// }

struct LengthStrComp{ 
	bool operator()(string& lhs, string& rhs){
		return lhs.size() < rhs.size();
	}
};

struct LengthIntComp{ 
	bool operator()(int& lhs, int& rhs){
		return lhs < rhs;
	}
};

// template <class Comparator>
// void DoStringCompare(string& i,string& j, Comparator c){
// 	cout << c(i, j) << endl;
// 	//c(i);
// }
// template <class Comparator>
// void DoIntCompare(int& i,int& j, Comparator c){
// 	cout << c(i, j) << endl;
// 	//c(i);
// }

// int main(){
// 	vector<int> i;
// 	i.push_back(3);
// 	i.push_back(2);
// 	i.push_back(5);
// 	i.push_back(7);
// 	i.push_back(8);
// 	i.push_back(7);
// 	i.push_back(1);
// 	//i.push_back(6);	
// 	LengthStrComp c_o;
// 	LengthIntComp c_t;
// 	mergeSort<int, LengthIntComp> (i, c_t);
// 	//DoIntCompare(2, 3, c_t);
// 	return 0;
// }