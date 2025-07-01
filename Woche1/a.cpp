
#include <iostream>
using namespace std;

int main() {

	long long n; 

	cin >> n; 

	long long a[n];

	long long cash = 100; 

	bool bought = false; 
	long long stocks = 0; 

	for (long long i = 0; i < n; i++) {
		cin >> a[i];
	}

	for (long long i = 0; i< n; i++) {

		if (bought) {
			// sell if bought previously  
			cash += a[i] * stocks;
			bought = false; 
			stocks = 0; 

		}
		
		//cout << "i: " << i << " a[i]: " << a[i] << "a[i+1]" << a[i+1] << endl;
		if (i != n -1 && a[i+1] >= a[i] ) {

			//buy 
			stocks =  min(cash / a[i], (long long) 100000);
			cash -= stocks * a[i]; 

			bought = true; 
		} 


	}

	cout << cash << endl;
}