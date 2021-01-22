/* This Program generates a random board square location, user have to enter the color of the square ( White or Black ).
 * Time taken for this will be noted for every entry and an average time taken will be given as ( maybe part of ) final output.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "getch_in_linux.c"
int main(){
	std::cout << " Hit <enter>, Q, q to Quit\n";
	std::cout << " Enter color of the following squares  White ( w, W, 1, <space> ) | Black ( b, B, 0, <tab> ) \n";
	srand( time(0) );
	char value;
	int rank, file, white, total_sqrs=0, correct=0, total_time=0;
	std::chrono::steady_clock::time_point start, end; 
	do{
		rank = rand() % 8;
		file = rand() % 8;
		white = ( (rank+1)^(file+1) ) & 1;  /// 1 => white , 0 => black
		std::cout << ' ' << char( 'a' + file ) << rank+1 << " : ";

		// Start timer
		start = std::chrono::steady_clock::now();
		value = getch();
		// end timer
		end = std::chrono::steady_clock::now();
		//time taken
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		++total_sqrs;
		if( ( white && ( value == ' ' || value == 'w' || value == 'W' || value == '1' ) ) 
			|| ( !white && ( value == '\t' || value == 'b' || value == 'B' || value == '0' ) ) ){
			std::cout << "\t\t+" << time/1000.0L << " sec\n";
			++correct;
			total_time += time;
		}
		else if ( value != '\n' && value != 'Q' && value != 'q' ){
			std::cout << " ???\t+" << time/1000.0L << " sec\n";
			total_time += time;
		}
		//print accuracy after it all ends
	}while( value != '\n' && value != 'Q' && value != 'q' );
	--total_sqrs;
	std::cout << "\n Total square/Total time : " << total_sqrs << "/"<<total_time/1000.0L << " sec"
		  << "\n Average time per square : " << std::fixed << std::setprecision(3) << ( 1.0L * total_time/1000.0L)/total_sqrs << " sec"
		  << "\n Accuracy		 : " << ( 1.0L * correct / total_sqrs ) * 100 << " % ";
	std::cout << '\n';
	return 0;
}
