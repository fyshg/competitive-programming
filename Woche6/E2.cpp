#include <bits/stdc++.h>
using namespace std; 
typedef long long ll; 



int main() {
	int t; 
	cin >> t; 
	for (int h = 0; h < t; h++) {
		int n; 
		cin >> n; 
		ll cash[n]; 
		ll population[n];
		ll sum = 0; 
		for (int i = 0; i < n; i++) {
			ll c, p; 
			cin >> p >> c ; 
			cash[i] = c; 
			population[i] = p; 
			sum +=p; 
		}

		vector<ll> cost_for_population(sum + 1,1000000000000);
		vector<ll> districts(sum +1,0); 
		map<ll, vector<bool>> assignments; 
		

		
		assignments[0] = vector<bool>(n, false); 

		cost_for_population[0] = 0; 
		
	
		for(int i = 1; i < sum +1; i++) {
			ll result = 1000000000000; 
			ll district_count = 10000; 
			vector<bool> chosen; 
			for (int j = 0; j < n; j++) {

				if(population[j] <= i && population[j] - i <= (sum + 1) / 2) {

					ll candidate = cost_for_population[i-population[j]] + cash[j]; 
					//cout << candidate << endl;
					if (( candidate < result || (candidate == result && district_count < districts[j])) && !assignments[i-population[j]][j]) {
						result = candidate; 
						chosen = assignments[i-population[j]];
						chosen[j] = 1; 
						district_count = districts[i-population[j]] + 1	;  


					}
				}
			}
			cost_for_population[i] = result; 
			districts[i] = district_count; 
			assignments[i] = chosen; 
			//update mem
		}
		ll result = 1000000000000; 
		ll count = 101; 
	


		for (int i = (sum + 1) / 2; i < sum +1 ; i++ ) {
			//cout << "i: " << i << " " << cost_for_population[i] << endl;
			if ( cost_for_population[i] < result || (cost_for_population[i]  == result && districts[i] < count)) {
				result = cost_for_population[i]; 
				count = districts[i];
			}
			
		}

		cout << "Case #" << h+1 << ": " << result << " " << count <<  endl; 


	}
}