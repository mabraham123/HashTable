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

int main(){
	//cout << orderOfG(3,8436401) <<endl;
	int ans=descreteLog(3, 8436400,8436401)%orderOfG(3,8436401);


	///cout << descreteLog(12,145123123,11231323) <<endl;


	return 0;
}


ulint orderOfG(ulint g,ulint n){
 default_random_engine e(static_cast<unsigned int>(time(0)));
 uniform_int_distribution<int> distribution(0,n-1);

 HashTable Ord;
 
	//Repeart sqrt n times
	for (ulint i = 0; i < sqrt(n); ++i)
	{
		//Generate a random number(r) between 0 and n-1
		ulint r= distribution(e);
		//cout<< r<<endl;


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

ulint modPower(ulint g, ulint r, ulint n){
	ulint result=1;

	//if even
	if(r != 0){
		if(r%2==0){
			result=modPower(g*g,r/2,n);	
		}else{
			result=g*modPower(g,r-1,n);		
		}
	}
	return result;



}

ulint descreteLog(ulint g, ulint a, ulint n){
	default_random_engine e(static_cast<unsigned int>(time(0)));
 	uniform_int_distribution<int> distribution(0,n-1);

 	HashTable A;
 	HashTable B;
 	ulint output=0;

	for (ulint i = 0; i < sqrt(n); ++i){
		//Get a random number
		ulint r= distribution(e);

		//If y=a*g^r mod n is a key in table A
		ulint y=modPower(a,1,n)*modPower(g,r,n);
		
		try{
			//Find if the value exists
			ulint v = B.getValue(y);

			//is found
			output=(v-r);
			return output;
		}catch(HashTableError q){
		//store the value r under the key y in table A
			A.insert(y,r);
		}


		//Pick a random number r between 0 and n-1
		r= distribution(e);

		//If y=g^r mod n is a key in tale A
		y=modPower(g,r,n);
		try{
			//You are done, output r-(tableA K's value)
			ulint v = A.getValue(y);
			
			if(r<v){
				output= ((r+orderOfG(g,n))-v);
			}else{
				output=(r-v);
			}
			return output;
		}catch(HashTableError l){
		//Else Store the value r under the key y in table B
			B.insert(y,r);
		}
	}
	return output;
}