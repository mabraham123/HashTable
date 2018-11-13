#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include "HashTable.h"


/* Implement mc_dlog in this file */

using namespace std;

void orderOfG (int g, int a, int n);

int main(){

	return 0;
}



void orderOfG(int g, int a, int n){

	//Repeart sqrt n times

		//Generate a random number(r) between 0 and n-1

		//If y=g^r is already a key in Ord
			//return r-Ord[h(y)] or r-Ord[h(y)]-r which ever is begger than 0

		//else
			//Add key y to Ord with value r

	//If after sqrt n attempts you fail to find a duplicate key- assume order of g is n-1
}
