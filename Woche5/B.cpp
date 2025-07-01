#include<bits/stdc++.h>
using namespace std; 
typedef long long ll; 

int main(){
	int t; 
	cin >> t; 
	for (int j = 0; j < t; j++) {
		ll l, n, r; 
		cin >> l >> n >> r; 
		vector<pair<ll, ll>> lanterns; 
		lanterns.reserve(n);
		for(int i = 0; i < n; i++) {
			ll p; 
			cin >> p; 
			lanterns.push_back(make_pair(p-r, p+r)); 
		}
		sort(lanterns.begin(), lanterns.end(), [] (auto a, auto b ) {
			return a.first < b.first; 
		});

		lanterns.push_back(make_pair(60000, 60000));
		ll current_end = 0; 
		ll count = 0; 
		for ( int i = 0; i < n; i++) {
			if ( current_end < l &&  current_end >= lanterns[i].first && current_end < lanterns[i+1].first) count++,  current_end = lanterns[i].second; 
		}

		cout << "Case #" << j+1 << ": ";
		if (current_end >= l) cout << count << endl; 
		else cout << "impossible" << endl; 
			

	}
}