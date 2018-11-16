#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include <vector>
#include <list>
#include "HashTable.h"


/* Implement mc_dlog in this file */

using namespace std;

ulint orderOfG (ulint ,ulint);
ulint modPower(ulint, ulint, ulint);
ulint descreteLog(ulint, ulint, ulint);


int main(int argc, char *argv[]){
	//Check if 3 parameters were passed
	if (argc != 4) {
        cerr << "Enter values 3 values only" << endl;
        return 1;
    }
    
    //Parse the parameters from string
	ulint g= atoi(argv[1]);
	ulint r= atoi(argv[2]);
	ulint n= atoi(argv[3]);
	
	//Get the values
    ulint descrete= descreteLog(g,r,n);
    ulint orderOf= orderOfG(g,n);

    //Work out the answer
	long long int answer= descrete%orderOf;

	//Check if the answer is negative
	if(answer <0){
		answer=answer+orderOf;
	}

	//Print the answer
	cout<<answer<< endl;

	return 0;
}

/*
	Method to work out the order of G
	Parameters:
	g-	base
	n- 	value to mod by
*/
ulint orderOfG(ulint g,ulint n){
 default_random_engine e(static_cast<unsigned int>(time(0)));
 uniform_int_distribution<int> distribution(0,n-1);

 HashTable Ord;
 
	//Repeart sqrt n times
	for (ulint i = 0; i < sqrt(n); ++i)
	{
		//Generate a random number(r) between 0 and n-1
		ulint r= distribution(e);


		//If y=g^r is already a key in Ord
		      //get value
				ulint y= modPower(g,r,n);
				try{
					//Find if the value exists
					ulint v = Ord.getValue(y);
					//return r-Ord[h(y)] or Ord[h(y)]-r which ever is begger than 0
					if(r>v){
						return r-v;
					}else if((v>r)){
						return (v-r);
					}
				}catch(HashTableError k){
					//If the key is not in the table
					Ord.insert(y,r);
				}
	
	}
	//If after sqrt n attempts you fail to find a duplicate key- assume order of g is n-1
	return (n-1);

}

/*
	Method to work out the exponetial modulo
	Parameters:
	g-	Base
	r- 	Power/Exponetial
	n- 	Value to mod by
*/
ulint modPower(ulint g, ulint r, ulint n){
	ulint result=1;
	g=g%n;

	//Was done mostly by myself but did use: 
	//http://www.cs.ucf.edu/~dmarino/progcontests/modules/matexpo/RecursionFastExp.pdf
	//page 1 for refrence
	if(r == 0){
	//Power is 0
		result= 1;
	}else if(r==1){
	//Power is 1
		result= g;
	}else if(r%2==0){
	//Is even
		result= modPower(g*g%n,r/2,n);
	}else{
	//Is odd
		result= g*modPower(g,r-1,n)%n;
	}




	return result;
}

/*
	Method to work out the descrete logarithm
	Parameters:
	g-	Base
	a-	Base
	n- 	Value to mod by
*/
ulint descreteLog(ulint g, ulint a, ulint n){
	default_random_engine e(static_cast<unsigned int>(time(0)));
 	uniform_int_distribution<int> distribution(0,n-1);

 	HashTable A, B;
 	ulint output=0;

	for (ulint i = 0; i < sqrt(n); ++i){
		//Get a random number
		ulint r= distribution(e);

		//If y=a*g^r mod n is a key in table A
		ulint y=modPower(((modPower(a,1,n))*(modPower(g,r,n))),1,n);
		
		try{
			//Find if the value exists
			ulint v = B.getValue(y);

			//is found
			output=(v-r);
			return output;
		}catch(HashTableError k){
			//If the key is not in the table
			A.insert(y,r);
		}


		//Pick a random number r between 0 and n-1
		r= distribution(e);

		//If y=g^r mod n is a key in tale A
		y=modPower(g,r,n);
		try{
			//You are done, output r-(tableA K's value)s
			ulint v = A.getValue(y);
			
			if(r<v){
				output= ((r+orderOfG(g,n))-v);
			}else{
				output=(r-v);
			}
			return output;
		}catch(HashTableError k){
		//Else Store the value r under the key y in table B
			B.insert(y,r);
		}
	}
	return output;
}
