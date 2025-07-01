#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

int main() {
	int t; 
	cin >> t; 
	for (int j = 0; j < t; j++){
		int n, m; 
		cin >> n >> m; 
		vector<pair<ll, ll>> activities; 
		activities.reserve(n); 
		for(int i = 0; i < n; i++ ) {
			string trash; 
			ll fun, length; 
			cin >> trash >> fun >> length; 
			activities.push_back(make_pair(fun, length));

			
		}
		

		sort(activities.begin(), activities.end(), [] (auto a, auto b){
		return a.first  > b.first; 
		});

		

		ll fun = 0; 
		ll time = m*60; 
		for (auto a : activities) {
			
			if (a.second > time){
				fun += time * a.first; 
				break; 
			}
			else {
				fun += a.second * a.first; 
				time -= a.second; 
			}
		}
		cout << "Case #" << j+1 << ": " << fun << endl; 
	}
}