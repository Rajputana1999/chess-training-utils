/* This program is to train for the bishop moves, 
 * Two randomly generated squares are given and user have to tell if Bishop can travel those two squares or not.
 * if it cannot then just '\n' will suffice
 * if it can then user have to enter the square at the intersection
 */

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>
#include<vector>
#include<chrono>
#include<iomanip>
using namespace std;

int abs( int a ){
	return a > 0 ? a : -a;
}
class square{
	public :
		int rank, file;
		square(int f=1, int r=1) : file(f), rank(r) {};
		string value(){
			string val="";
			val.push_back(char('a'+file-1));
			val.push_back(char('1'+rank-1));
			return val;
		}
		
		bool isvalid(){
			return rank>=1 && rank<=8 && file>=1 && file<=8;
		}

		int color(){
			return (rank^file)&1;
		}

		vector<square> findIntersection( square target ){

			/* find and return the two intersecting squares
		 	* find two squares in the same rank as the target square ( r1, r2 )
		 	* if file difference b/w rx and target is odd => not reachable( different colors )
		 	*/
			if( color() ^ target.color() ) return {}; /// The colors are different
			
			if( abs(file-target.file) == abs(rank-target.rank) ) return {target};

			int rankDiff = abs( rank - target.rank );
			square horz1(file+rankDiff, target.rank), horz2(file-rankDiff, target.rank);
			int dir = (rank>=target.rank) ? +1 : -1;

			// vector for 1st intersecting square
			int direction1 = (horz1.file > target.file)? dir : -dir;
			int magnitude1 = abs( target.file - horz1.file)/2;
			int file1 = (target.file + horz1.file)/2;

			// vector for 2nd intersecting square
			int direction2 = (horz2.file < target.file)? dir : -dir;
			int magnitude2 = abs( target.file - horz2.file)/2;
			int file2 = (target.file + horz2.file)/2;

			return {
				square( file1 , target.rank + direction1*magnitude1),
				square( file2 , target.rank + direction2*magnitude2)
			};
		}
			
};

int main(){
	cout << " Enter the intersecting square for bishop (press 's' if on same diagonal) ( press 'n' if doesn't exist)\n";
	
	srand( time(0) );
	string mid;
	chrono::steady_clock::time_point start, end; 
	int total_time=0, total_q=0, correct=0;
	while(1){
		// generate two random squares
		square source, target;
		do{
			source = square(rand()%8 + 1, rand()%8 +1);
			target = square(rand()%8 + 1, rand()%8 +1);
		}while((rand()%4) && (source.color()!=target.color()));

		// input a string
		cout << " " << source.value() << " -> " << target.value() << " : ";
		start = chrono::steady_clock::now();
		cin>>mid;
		end = chrono::steady_clock::now();
		if(mid=="q")break;
		total_q++;
		auto time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
		total_time+=time;

		// check against correct value , empty string if NP
		vector<square> answers = source.findIntersection(target);
		cout<<" ";
		if( answers.size() == 0 ) cout<<"Opp.";
		int k=0;
		for( auto &i: answers) if(i.isvalid())k++,cout<< ":" <<i.value() << " ";
		if( k < 2 ) cout<<"\t";
		if( (answers.size()==0 && mid=="n")  
			|| (answers.size() == 1 && mid=="s") 
			|| (answers.size() > 1 && answers[0].isvalid() && mid==answers[0].value()) 
			|| (answers.size() > 1 && answers[1].isvalid() && mid==answers[1].value()) 
		){
			cout << " \t\t(+)\t+" << time/1000.0L << " sec\n";
			correct++;
		}
		else {
			cout << " \t\t(-)\t+" << time/1000.0L << " sec\n";
		}
	}
	cout	<< "\n Average time     : " << fixed << setprecision(3) << ( 1.0L * total_time/1000.0L)/total_q << " sec"
		<< "\n Accuracy         : " << ( 1.0L * correct / total_q ) * 100 << " %"
		<< "\n Total queries    : " << total_q << "\n";
	return 0;
}
