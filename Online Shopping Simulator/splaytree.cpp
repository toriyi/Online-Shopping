#include "splaytree.h"
#include "bst.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]){
	SplayTree<int, char> sTree;


	sTree.insert(make_pair(8,'i'));
	sTree.insert(make_pair(3,'i'));
	sTree.insert(make_pair(22,'i'));
	sTree.insert(make_pair(14,'i'));
	sTree.insert(make_pair(12,'i'));
	sTree.insert(make_pair(2,'i'));
	sTree.insert(make_pair(21,'i'));
	sTree.insert(make_pair(19,'i'));
	sTree.insert(make_pair(5,'i'));
	sTree.insert(make_pair(18,'i'));
	sTree.print();

	std::cout <<"DELETE 14"<< std::endl;
	sTree.erase(14);
	sTree.print();

	SplayTree<int, char>::iterator iter = sTree.find(22);
	std::cout<<"FOUND " <<  (*iter).first <<std::endl;

	return 0;
}