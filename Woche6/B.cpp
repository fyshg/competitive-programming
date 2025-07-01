#include <bits/stdc++.h>
using namespace std; 
typedef long long ll; 

int main() {
	int t;
	cin >> t; 
	for (int q = 0; q < t; q++) {
		ll d, c, penalty; 
		cin >> d >> c >> penalty; 
		ll cart[d*(c+1)]; 
		ll bike[d*(c+1)]; 
		for (int i = 0; i < d*(c+1); i++) {
			ll in; 
			cin >> in; 
			if( i == 0 ) cart[i]= in;
			else cart[i] = cart[i-1] + in; 
		}
		for (int i = 0; i < d*(c+1); i++) {
			ll in; 
			cin >> in; 
			if( i == 0 ) bike[i]= in;
			else bike[i] = bike[i-1] + in; 	
		}
		ll total = 0; 
		for (int i = 0; i < d; i++) {
			ll result; 
			ll current_start = i * (c+1); 
			ll current_end = current_start + c; 
			if (i != 0) result = min(cart[current_end] - cart[current_start-1], bike[current_end] - bike[current_start-1]  ); 
			else result = min(cart[c], bike[c]); 
			for (int j = 0; j <= c ; j++) {
				ll carend = ( i == 0 ? 0 : cart[current_start - 1] ); 
				ll bikend = ( i == 0 ? 0 : bike[current_start - 1] ); 
				result = min(result, cart[current_end] - cart[current_start + j] + penalty + bike[current_start + j ] - bikend); 
				result = min(result, bike[current_end] - bike[current_start + j] + penalty + cart[current_start + j ] - carend);
			}
			total += result; 	
		}
		cout << "Case #" << q+1 << ": " << total << endl;
	}
}