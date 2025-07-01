#include <bits/stdc++.h>
using namespace std; 
typedef long long ll; 
#define INF 10000000000000


int main() {
	ll t; 
	cin >> t; 
	for (ll h = 0; h < t; h++) {
		ll n; 
		cin >> n; 
		ll cash[n]; 
		ll population[n];
		ll sum = 0; 
		for (ll i = 0; i < n; i++) {
			ll c, p; 
			cin >> p >> c ; 
			cash[i] = c; 
			population[i] = p; 
			sum +=p; 
		}
		//cout << n << sum << endl; 
		vector<vector<ll>> mem;    // ll[n][sum]; 
		vector<vector<ll>>  district_count;
		for (ll i = 0; i < n; i++) {
			mem.push_back(vector<ll>((sum + 1)/2, 0)); 
			district_count.push_back(vector<ll>((sum + 1)/2, 0));
		}
		
		
		for (ll i = 0; i < n; i++) {
			for (ll j = 0; j < (sum + 1)/2; j++) {
				ll result = INF; 
				ll no_districts = INF; 
				

				if (i >= 1 && population[i] <= j) {
					
					ll test = mem[i-1][j - population[i]] + cash[i]; 
					if ( test < result || (test == result && district_count[i-1][j-population[i]] + 1 < no_districts)) {
						result = test; 
						no_districts = district_count[i-1][j-population[i]] + 1 ; 
					} 
				}
				if (i >= 1) {
					
					ll test = mem[i-1][j]; //candidate i 
					if ( test < result || (test == result && district_count[i-1][j] < no_districts)) {
						result = test; 
						no_districts = district_count[i-1][j]; 
					} 
				} 

				if(population[i] >= j+1) {
					ll test = cash[i]; 
					if ( test < result || (test == result && 1 < no_districts)) {
						result = test; 
						no_districts = 1; 			
					}
				}

				mem[i][j] = result; 
				district_count[i][j] = no_districts; 
				//cout << mem[i][j] << " "; 
			}
			//cout << endl;
		}
		
		cout << "Case #" << h+1 << ": " << mem[n-1][(sum+1)/2 - 1 ] << " " << district_count[n-1][(sum+1)/2 -1 ] <<  endl; 


	}
}