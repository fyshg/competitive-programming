#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>  
#include <limits>

using namespace std; 


long double dist(long double ax, long double ay, long double bx ) {
	return ( sqrt( pow(ax - bx, 2) + pow(ay, 2)));
}

long double f(long double bx, vector<long double>& x, vector<long double>& y){
	long double result = 0; 
	for (size_t i = 0; i < x.size(); i++){
		long double distance = dist(x[i], y[i], bx);
		if( distance > result){
			result = distance; 
		}
	}
	return result; 
}

int main(){
	int N;
	cin >> N;
	
	for (int j = 0; j< N; ++j){
		vector<long double> x;
		vector<long double> y; 
		int t; 
		cin >> t; 
		for (int i = 0; i <t ; ++i){
			long double a, b;
			cin >> a >> b; 
			x.push_back(a);
			y.push_back(b);
		}

		//ternary search 
		long double start = -200000; 
		long double end =  200000;
		while ( abs(end - start) > pow(10, - 12) ){
			long double mid1 = start + (end - start)/ 3; 
			long double mid2 = end - (end - start)/3;

			if( f(mid1, x, y) < f(mid2, x, y)) {
				end = mid2; 
			} else {
				start = mid1; 
			}



		}
		cout << setprecision(10) << "Case #" << j+1 << ": "<< start << " " << setprecision(10) << f(start, x, y) << endl;
	}
}