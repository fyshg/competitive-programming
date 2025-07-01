#include <bits/stdc++.h>
typedef long long ll; 
using namespace std; 
#define pii pair<ll, ll>
int main() {
	int t;
	cin >> t;  
	for(int j = 0; j < t; j++){
		ll n; 
		cin >> n; 
		vector<pii> slots; 
		for (int i = 0; i < n; i++) {
			ll d, l; 
			string h; 
			cin >> d >> h >> l;  
			ll minutes = (d -1)* 24 * 60; 
			minutes += stoi(h.substr(0, 2)) * 60; 
			minutes  += stoi(h.substr(3, 2));
			slots.push_back(make_pair(minutes, minutes+l));
		}
		sort(slots.begin(), slots.end(), [](auto a, auto b) {
			return a.first < b.first; 
		}); 
		priority_queue<int, vector<int>,  greater<int>> pq; 
		pq.push(-42);
		for (auto a: slots) {
			if (pq.top() <= a.first) pq.pop();
			pq.push(a.second);
		} 
		 

		cout << "Case #" << j+1 << ": " << pq.size() * 500 << endl; 
	}
}