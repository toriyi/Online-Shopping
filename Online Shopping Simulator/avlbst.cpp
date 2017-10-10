
#include "avlbst.h"
//#include "bst.h"


using namespace std;

int main() {
	std::cout << "INSERT" << std::endl;
	AVLTree <int, int> avl_tree;

	avl_tree.insert(make_pair(9,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(8,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(7,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(6,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(5,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(4,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(3,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(2,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(1,1));
	avl_tree.print();
	std::cout << std::endl;


	avl_tree.insert(make_pair(3,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(14,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(40,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(10,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(5,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(26,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(19,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(9,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(13,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(1,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(2,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(17,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(87,1));
	avl_tree.print();
	std::cout << std::endl;
 
	avl_tree.insert(make_pair(20,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(30,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(15,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(25,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(11,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(5,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(55,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(99,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(24,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(59,1));
	avl_tree.print();
	std::cout << std::endl;

	avl_tree.insert(make_pair(59,1));
	avl_tree.print();
	std::cout << std::endl;
	
	std::cout << "REMOVE" << std::endl;
	std::cout <<"DELETE 11"<< std::endl;
	avl_tree.erase(11);
	avl_tree.print();
	std::cout << std::endl;
	std::cout <<"DELETE 9"<< std::endl;
	avl_tree.erase(9);
	avl_tree.print();
	std::cout << std::endl;
	std::cout <<"DELETE 25"<< std::endl;
	avl_tree.erase(25);
	avl_tree.print();
	std::cout << std::endl;
	std::cout <<"DELETE 99"<< std::endl;
	avl_tree.erase(99);
	avl_tree.print();
	std::cout << std::endl;
	std::cout <<"DELETE 13"<< std::endl;
	avl_tree.erase(13);
	avl_tree.print();
	std::cout << std::endl;

	std::cout <<"DELETE 1"<< std::endl;
	avl_tree.erase(1);
	avl_tree.print();
	std::cout << std::endl;

	std::cout <<"DELETE 10"<< std::endl;
	avl_tree.erase(10);
	avl_tree.print();
	std::cout << std::endl;
	std::cout <<"DELETE 2"<< std::endl;
	avl_tree.erase(2);
	avl_tree.print();
	std::cout << std::endl;
	std::cout <<"DELETE 17"<< std::endl;
	avl_tree.erase(17);
	avl_tree.print();
	std::cout << std::endl;

	return 0;
	}	
