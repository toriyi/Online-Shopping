#ifndef HASH_H
#define HASH_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
//write our hash struct 
struct HashHelper{
    unsigned long long Hasher(string password){
        int size = password.length()-1;
        unsigned long long hValue = 0;
        unsigned long long number = 0;
        unsigned int array[4];
        for(unsigned int i = 0; i < password.length(); i++){
            number += (unsigned long long)pow(128,i) * (unsigned long long)password[size]; 
            size--;
        }
        unsigned long long temp = number;
        
        for(int j = 3; j >= 0; j--){
            array[j] = (temp%65521);
            temp /= 65521;
        }

        hValue = (45912 * array[0] + 35511 * array[1] + 65169 * array[2] + 4625 * array[3]) % 65521;
        cout << setw(5) << setfill('0') << hValue << endl; 
        return hValue;
    }
};

#endif