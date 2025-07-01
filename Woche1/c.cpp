#include <iostream>
#include <cmath>
using namespace std; 

long double dist(long double xa,long double xb, long double ya, long double yb) {
	return sqrt( pow((xa - xb), 2.0) + pow((ya - yb), 2.0) );
}

int main() {

	long double first[2];
	cin >> first[0] >> first[1];
	long double second[2]; 
	cin >> second[0] >> second[1]; 
	long double third[2]; 
	cin >> third[0] >> third[1]; 

	long double incircle; 
	cin >> incircle; 

	long double a = dist(first[0], second[0], first[1], second[1]); 
	long double b = dist(second[0], third[0], second[1], third[1]);
	long double c = dist(third[0], first[0], third[1], first[1]);



	long double A = (1.0/4.0) * sqrt(4.0*pow(a, 2.0) * pow(b,2.0) - pow( (pow(a, 2.0) + pow(b,2.0) - pow(c,2.0)), 2.0)); 

	long double r = A / ( (a + b + c) / 2.0 );

	//long double s = (a+b+c) /2.0; 
	//long double r = sqrt( ((s-a)*(s-b)*(s-c))/s);

	long double ratio = (r / incircle) * 100; 
	long double result = ratio - 100.0; 



	//cout << "r: " << r << "incircle: " << incircle << " ratio: " << ratio << endl; 
	//cout << ratio * incircle << endl; 
	
	cout << result << endl; 

}

