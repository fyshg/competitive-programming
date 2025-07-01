#include <bits/stdc++.h>
using namespace std; 

#define  FOR(i,a,n) for(ll i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
#define  FORD(i,a,b)     for(ll i=(b);i>=(a);i--)
const double eps = 1e-10;
typedef long long ll; 
typedef __int128_t lll;
typedef __uint128_t ulll;
ostream & operator<< (ostream & os, ulll val) {
	if (val < 10) os << (int) val;
	else os << (ulll) (val / 10) << (int) (val % 10);
	return os;
}
ostream & operator<< (ostream & os, lll val) {
	if (val < 0) os << "-" << (ulll) (~val + 1);
	else os << (ulll) val;
	return os;
}
istream & operator>> (istream & is, lll & val) {
	string in;
	is >> in;
	val = 0;
	ll i = 0, sign = 1;
	if (in[i] == '+' || in[i] == '-')
		sign = (in[i]=='-' ? -1 : 1), i++;
	for ( ; i < in.size(); ++i)
		val = (val * 10) + (in[i] - '0');
	val *= sign;
	return is;
}
istream & operator>> (istream & is, ulll & val) {
	return is >> ((lll &) val);
}


lll egcd(lll a, lll b, lll& x, lll& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	} else {
		lll d = egcd(b, a % b, x, y);
		x -= a / b * y;
		swap(x, y);
		return d;
	}
}

lll inverse(lll A, lll N) {
	lll X,Y; 
	egcd(A,N,X,Y); 
	return X; 
	//return (X+N) % N;
}

int main() {
	lll t; 
	cin >> t; 
	FOR(g,0,t) {
		lll n, K;  
		cin >> n >> K; 
		lll N = 1; 
		vector<pair<lll,lll>> factors;  //size rest
		map<lll,lll> primes; 
		bool impossible = false; 
		FOR(i,0,n) {
			lll size, rest; cin >> size >> rest; 
			factors.push_back(make_pair(size,rest)); 
			if(primes.count(size) != 0 && primes[size] != rest) impossible = true; 
			primes[size] = rest;  


			N *= size; 
		}
		vector<ll> c; 
		lll result = 0; 
		FOR(i,0,n) {
			lll X = inverse((N/factors[i].first), factors[i].first);
			//cout << X << " : " << factors[i].first << " % " <<  N/factors[i].first << endl; 
			result = (result +( X * factors[i].second* (N/factors[i].first))) % N;
		}
		result = (result + N ) % N; 
		cout << "Case #" << g+1 << ": "; 
		lll x = (K-result) / N; 
		if( impossible || result > K) cout << "impossible" << endl; 
		else cout << result + x*N << endl; 
	}
}   