#include <bits/stdc++.h>
using namespace std; 
typedef long long ll; 

int main() {
	int t; 
	cin >> t; 
	for (int j = 0; j < t; j++) {
		int n; 
		cin >> n; 
		timeslots; 
		for (int i = 0; i < n; i++) {
			int a,b,p; 
			cin >> a >> b >> p; 
			if (!timeslots.count(b)) timeslots[b] = vector<pair<int, int>>(); 
			timeslots[b].push_back( make_pair(a,p)); 
		}

		ll mem[5001]; 
		mem[0] = 0; 
		for (int i = 1; i < 5001; i++) {
			ll maxi= -1; 
			if (timeslots.count(i)) {
				for (int h = 0; h < timeslots[i].size(); h++) {
					maxi = max(maxi, mem[timeslots[i][h].first-1] + timeslots[i][h].second); 
				}
			}
			maxi = max(maxi, mem[i-1]);
			mem[i] = maxi; 
		}
		cout << "Case #" << j+1 << ": " << mem[5000] << endl;
	}


}