// Anzahl Boxen auf Städte verteilen 

#include <bits/stdc++.h>
typedef long long ll; 
using namespace std; 
int main() {
	int t; 
	cin >> t; 
	for (int j = 0; j < t; j++){
		long long N,B;
		cin >> N >> B; 
		ll maxi = -1; 
		ll a[N];
		for ( int i = 0; i < N; i++) {
			cin >> a[i]; 
			maxi = max(maxi, a[i]);
		}

		ll lo = 1; 
		ll hi = maxi; 
		B = B - N;
		ll mid = 0; 
		ll divs = 0; 
		while (lo + 1 	< hi) {
			mid = (hi + lo)/2;
		
			divs = 0; 
			for (int i = 0; i  < N ; ++i){
				if (a[i] > mid){
					//teilen solange bis kleiner als mid
				ll curren_divs = 0; 
				if (a[i] % mid == 0) curren_divs = ((a[i] + mid) / mid) -2 ;
				else {
					curren_divs = (a[i]/ mid);
				}
				divs += curren_divs; 

				//cout << mid << " a: " << a[i] << " currentdivs: " << curren_divs << endl;
			}
			}
				//cout << " hi: " << hi << " lo: " << lo << " mid: " << mid << " divs: " << divs << endl; 
			if (divs <= B ) {
				hi = mid; 
			} else {
				lo = mid; 
			}
		}
		mid = (hi + lo) / 2; 

		

		cout << "Case #" << j+1 << ": " <<  mid +1<< endl; 


	}

}