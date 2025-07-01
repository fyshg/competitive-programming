#include <bits/stdc++.h>
using namespace std; 

#define  FOR(i,a,n) for(ll i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
#define  FORD(i,a,b)     for(ll i=(b);i>=(a);i--)
const double eps = 1e-10;
typedef unsigned long long ll; 

int main() {
	int t; cin >> t; 
	cout << setprecision(200); 
	for(int g = 0; g < t; g++) {
		ll n, k, c; 
		cin >> n >> k >> c; 
		cout << "Case #" << g+1 << ": "; 
		ll first = powl(c, powl(n, 2)); 
		if(n == 1) cout << c << " " << c << " " << c; 
		else if (n==2) cout << first << " " << (first + c*2 + powl(c,2))/4         << " " << (first + c*2+ powl(c,2) *3 + powl(c,3)*2)/8; 
		else if (n==3) cout << first << " " << (first + 2*powl(c,3) + powl(c,5))/4  << " " << (first  + 2* powl(c,3) + powl(c,5) + 4 * powl(c,6))/ 8; 
		else if (n==4) cout << first << " " << (first + 2*powl(c,4) + powl(c,8))/4  << " " << (first + 2*powl(c,4) + powl(c,8) + 2*powl(c,8) + 2*powl(c,10))/8; 
		else if (n==5) cout << first << " " << (first + 2*powl(c,7) + powl(c,13))/4 << " " << (first + 2*powl(c,7) + powl(c,13) + 4*powl(c,15))/8; 
		cout << endl; 
 	}
}