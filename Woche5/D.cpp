#include <bits/stdc++.h>
using namespace std; 
//ap<char, ll> mapping = {{'A', 0}, {'C', 1}, {'D', 2}, {'E', 3}}; 
string genes = "ATCG"; 
typedef long long ll; 

int main() {
	ll t; 
	cin >> t; 
	for (ll j = 0; j < t; j++) {
		ll m, n; 
		cin >> n >> m; 
		vector<string> humans;  
		map<string, ll> Occurences; 
		for (ll i = 0; i < n; i++) {
			string s; 
			cin >> s; 
			humans.push_back(s); 
		}
		for (char c1 : genes) {
			for (char c2: genes) {
				string s = ""; 
				s.push_back(c1); 
				s.push_back(c2); 
				sort(s.begin(), s.end()); 
				Occurences[s] = 0; 
			} 
		}
		for(ll i = 0; i < m; i++) {
			string dolphin; 
			cin >> dolphin; 
			for(string& human : humans ) {

				ll h = 0; 
				for (char c: dolphin) {
					string key =  ""; 
					key.push_back(c); 
					key.push_back(human[h]);  
					sort(key.begin(), key.end());
					Occurences[key] += 1;
					h++; 
				}
			}
		}
		vector<ll> occ; 
		vector<ll> occq; 
		for (auto& a: Occurences) {
			string k1 = a.first.substr(0,1); 
			string k2 = a.first.substr(1,1);
			if( k1 != k2) {
				occ.push_back( a.second);
			} else occq.push_back(a.second);
		}
		
		sort(occ.begin(), occ.end(), greater<ll>());
		sort(occq.begin(), occq.end(), greater<ll>()); 

		ll result = -1000000; 
		for (ll a = 10; a >= 1; a--) {
			for (ll b = 10; b >= 1; b--) {
				for  (ll c = 10; c >= 1; c--) {
					for (ll d = 10; d >= 1; d--) {
						ll sum = a+b+c+d; 
						if (sum % 2 == 0){
					
							result  = max( a* occq[0] + b*occq[1] + c*occq[2]+ d*occq[3] + 
								10 * occ[0] + 10*occ[1] -10*occ[3]-10*occ[4]-10*occ[5] + (
									(20 - sum)/2)*occ[2], result); 


						}
					}
				}
			}
		}



		cout << "Case #" << j+1 << ": "<< result<< endl;


	}
}