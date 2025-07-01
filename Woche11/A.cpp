#include <bits/stdc++.h>
using namespace std; 
typedef long long ll;  
typedef vector<ll> vi; 
typedef pair<ll, ll> pii;
#define  FOR(i,a,n) for(ll i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
#define  FORD(i,a,b)     for(ll i=(b);i>=(a);i--)
const double eps = 1e-10;


ll egcd(ll a, ll b, ll& x, ll& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	} else {
		ll d = egcd(b, a % b, x, y);
		x -= a / b * y;
		swap(x, y);
		return d;
	}
}

int main() {
	ll t; 
	cin >> t; 
	FOR(g,0,t) {
		ll K, C, X, Y;  
		cin >> K >> C; 
		cout << "Case #" << g+1 << ": "; 
		if(egcd(K,C, X, Y) != 1) cout << "impossible" << endl; 
		else cout << (Y + K) % K << endl; 
	}
}