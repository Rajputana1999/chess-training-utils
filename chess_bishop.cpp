/* This program is to train for the bishop moves, 
 * Two randomly generated squares are given and user have to tell if Bishop can travel those two squares or not.
 * if it cannot then just '\n' will suffice
 * if it can then user have to enter the square at the intersection
 */

#include<iostream>
#include<time>
#include<stdlib>
#include<string>
using namespace std;

class square{
	public :
		int rank, file;
		square(int r=0, int f=0) : rank(r), file(f);
		string value(){
			return to_string(rank+'a') + to_string(file+'1');
		}
		bool color(){
			return rank^file;
		}
};

int main(){
	cout << " Enter the intersecting square for bishop\n
		( press enter if doesn't exist)\n";
	
	// generate two random squares
	srand( time(0) );
	square begin(rand()%8, rand()%8), end(rand()%8, rand()%8);
	
	// input a string
	cout << begin.value() << " -> " << end.value() << " : ";
	string mid;
	getline(cin, mid);
	
	// check against correct value , empty string if NP
	
	
