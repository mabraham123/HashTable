#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include <vector>
#include <list>
#include "HashTable.h"


/* Implement mc_dlog in this file */

using namespace std;

void orderOfG (int g, int a, int n);

int main(){
	orderOfG(12,24,10);
	return 0;
}



void orderOfG(int g, int a, int n){
 default_random_engine e(static_cast<unsigned int>(time(0)));
 uniform_int_distribution<int> distribution(0,n-1);

 HashTable Ord;
 
	//Repeart sqrt n times
	for (int i = 0; i < sqrt(n); ++i)
	{
		//Generate a random number(r) between 0 and n-1
		int r= distribution(e);


		//If y=g^r is already a key in Ord
		for (int i = 0; i < (int)Ord.size(); ++i)
		{
			//for (HashNode &hashNode: Ord){
		      //get value
				if (Ord.getValue(pow(g,r)) != 101){
					cout<<"Yas"<<endl;
				}
		     
			
		}
			//return r-Ord[h(y)] or r-Ord[h(y)]-r which ever is begger than 0

		//else
			//Add key y to Ord with value r
	
	}

	//If after sqrt n attempts you fail to find a duplicate key- assume order of g is n-1
}
