/* This Program generates a random board square location, user have to enter the color of the square ( White or Black ).
 * Time taken for this will be noted for every entry and an average time taken will be given as ( maybe part of ) final output.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "getch_in_linux.c"
int main(){
	std::cout << " Hit <enter> or ^C or Q to Quit\n";
	std::cout << " Enter color of the following squares  White ( w, W, 1, <space> ) | Black ( b, B, 0, <tab> ) \n";
	srand( time(0) );
	char value;
	do{
		std::cout << ' ' << char( 'a' + rand()%8 ) << rand() % 8 << " : ";
		value = getch();
		//check against the right value
		//print the time taken as +0.80 sec
		//for now just print the input to screen
		if( value == ' ' || value == 'w' || value == 'W' || value == '1' ){
			std::cout<<" WHITE\n";
		}
		else if( value == '\t' || value == 'b' || value == 'B' || value == '0' ){
			std::cout << " BLACK\n";
		}
		else {
			std::cout << " NOT VALID\n";
		}
	}while( value != '\n' && value != 'Q' );
	std::cout << '\n';
	return 0;
}
