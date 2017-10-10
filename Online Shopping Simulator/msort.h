 #ifndef MSORT_H  
 #define MSORT_H  

 #include <vector>
 #include <iostream>
 using namespace std;

 template <class T, class Comparator>
 void msort(vector<T>& mylist, vector<T>& output, int start, int end);
 template <class T, class Comparator>
 void merge(vector<T>& mylist, vector<T>& output, Comparator comp, int s1, int e1, int s2, int e2);
 
 template <class T, class Comparator>
 void msort(vector<T>& mylist, vector<T>& output, Comparator comp, int start, int end){
 	if(start >= end){
 		return;
 	}
 	int middle = (start+end)/2;


 	//cout << "START " << start << "END " << middle << endl;
 	msort<T, Comparator>(mylist, output, comp, start, middle);
 	//cout << "START " << middle << "END " << end << endl;
 	msort<T, Comparator>(mylist, output, comp, middle+1, end);

 	//for(unsigned int i = start; i<=middle; i++)
 		//cout<<mylist[i]<<" ";
 	//cout<<"|";
 	//for(unsigned int i = middle+1; i<=end; i++)
 		//cout<<mylist[i]<<" ";
 	//cout<<endl;
 	merge<T, Comparator>(mylist, output, comp, start, middle, middle, end); 

 	//for(unsigned int i = start; i<=end; i++)
 		//cout<<mylist[i]<<" ";
 	//cout<<endl;
 }
 
 template <class T, class Comparator>
 void mergeSort (vector<T>& mylist, Comparator comp){
 	vector<T> other(mylist);
 	msort<T, Comparator>(other, mylist, comp, 0, mylist.size()-1);
 }

 template <class T, class Comparator>
 void merge(vector<T>& mylist, vector<T>& output, Comparator comp, int s1, int e1, int s2, int e2){
	int a,b,c;
	a = s1;
	b = s1;
	c = s2+1;
 	while(a <= e1 && c <= e2){
 		if(comp(mylist[a], mylist[c])){
 			output[b] = mylist[a];
 			a++;
 			b++;
 		}
 		else{
 			output[b] = mylist[c];
 			c++;
 			b++;
 		}
 	}
 	if(a <= e1){
 		 for (int i = a; i <= e1; i++){
			output[b] = mylist[i];
			b++;
 		}
 	}
	else{
 		for (int i = c; i <= e2; i++){
 			output[b] = mylist[i];
 			b++;
 		}	
 	}

 	for(int i = s1; i <= e2; i++){ //copy from temporary to original 
 		mylist[i] = output[i];
 	}
 }

 #endif