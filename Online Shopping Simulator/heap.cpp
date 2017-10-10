#include "heap.h"

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;


// int main () {
//   Heap<string>h1;


//   //post top and pop 
//  	h1.push(1.0,"A");
//   h1.push(2.0,"B");
//   h1.push(3.0,"C");

//   h1.push(1.5,"E");
//   h1.push(2.5,"F");
//   h1.push(3.5,"K");

//   h1.push(0.3,"L");
//   h1.push(0.0,"T");

//   //cout << "SIZE " << h1.size() << endl;

//   h1.print();
//   cout << "==================================" << endl;

//   cout << "FIRST POP " << endl;
//   h1.pop();
//   cout << "==================================" << endl;
//   h1.print();

//   cout << "SECOND POP " << endl;
//   h1.pop();
//   cout << "==================================" << endl;
//   h1.print();

//   cout << "FIRST DK " << endl;
//   h1.decreaseKey(0.0, "F");
//   cout << "==================================" << endl;
//   h1.print();

//   cout << "SECOND DK " << endl;
//   h1.decreaseKey(1.1, "K");
//   cout << "==================================" << endl;
//   h1.print();

//   cout << "THIRD DK " << endl;
//   h1.decreaseKey(10, "A");
//   cout << "==================================" << endl;
//   h1.print();


//   return 0;
// }