#include <iostream>

typedef  long long ll;
using namespace std; 

ll leaCookies(ll* bowls, int size,ll a,ll b) {
	ll left = bowls[a];
	ll mid = bowls[b]-bowls[a];
	ll right = bowls[size]- bowls[b];
	return bowls[size] - max(left, max(mid, right)); 
}


int main() {
	int t; 
	cin >> t; 
	for (int j = 0; j < t; j++) {
		ll n, p, q, r, s; 
		cin >> n >> p >> q >> r >> s;
		ll bowls[n+1] ;// = {0,4,7,9,10};
		bowls[0] = 0; 
		for (int i = 1; i <= n; i++){
			ll next = ((i*p + q)%r)+s;
			bowls[i] = bowls[i-1] + next; 
		}
		
		ll a = 0;
		ll b = 1; 

		for(;;){
			ll current = leaCookies(bowls, n, a, b);


			if ( b != n &&  (leaCookies(bowls, n, a, b+1) >= current )) b++;
			else if (b - a > 1 && leaCookies(bowls, n, a+1, b) >= current) a++; 
			else if (b != n && leaCookies(bowls, n, a+1, b+1) > current){ a++; b++;}
			else break; 
			

		}
		
		cout << "Case #" << j+1<< ": "<< leaCookies(bowls, n, a,b) << endl; 


	}
}