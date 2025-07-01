#include <bits/stdc++.h>
typedef unsigned long long ull; 
using namespace std; 

ull gcd(ull a, ull b){
return b == 0 ? a : gcd(b, a % b);
}


ull factors(ull N) {
	//cout << "factors(" << N <<") " << endl; 
	ull primepower = 0; 
	for(ull i = 2; i <= static_cast<ull>(sqrt(N+1)); ++i) {	
		if (N % i == 0 && gcd(i, N/i) == 1){
			return factors(i)* factors(N/i); 
		} else if (N % i == 0 && primepower== 0) {
			primepower = i; 
		}

	}
	if(primepower != 0) return log(N)/log(primepower) + 1; 
	return 2; //if prime
}

int main() {
	ull t; 
	cin >> t; 
	

	for(ull g = 0; g < t; g++){
		ull number; cin >> number;   
		cout << "Case #" << g+1 << ": " << factors(number) << endl; 
	} 
	

}

