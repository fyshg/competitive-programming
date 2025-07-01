#include <bits/stdc++.h>
using namespace std; 

map<vector<short int>, double> mem; 
vector<double> results; 
int dominant; 
vector<short int> basecase; 
int maxi; 
double rec(vector<short int> dist, short int n, bool start) {
	
	if ( n < dominant && n > maxi) return 0;
	if ( ! start && mem.count(dist)) return mem[dist];
	for(int i = 0; i < dist.size(); i++) {
		if (basecase[i] > dist[i]) return 0; 
	}

	if (!start) {
		double p = 0; 
		for (int i = 0; i < dist.size(); i++) {
			vector<short int> copy = dist; 
			copy[i]--; 
			p += ((double) (dist[i]-1) / (double) (n-1)) * rec(copy, n-1, false); 
		} 
		if (mem.count(dist)) return p; 
		mem[dist] = p; 
	}

	if ( n == maxi) {
		

		short int maxelem = *(max_element(dist.begin(), dist.end())); 
		int count = 0; 
		for (int i = 0; i < dist.size(); i++) {
			if (dist[i] == maxelem) count++; 
		}
		for(int i = 0; i < dist.size(); i++) {
			if (dist[i] == maxelem) results[i]+= mem[dist] * ((double) 1 / (double) count); 
		} 

	}
	


	if ( n < maxi){
		for (int i = 0; i < dist.size(); i++) {
			vector<short int> copy = dist; 
			copy[i]++; 

			rec(copy, n+1, false); 
		}
	}

	return mem[dist]; 
}

int main() {
	int t; 
	cin >> t; 
	for( int g = 0; g < t; g++) {
		int n; 
		maxi = 0; 
		cin >> n >> maxi; 
		basecase = vector<short int>(n); 
		dominant = 0; 
		mem = map<vector<short int>, double>(); 
		results = vector<double>(n,0);
		for(int i = 0; i < n; i++) {
			int var; 
			cin >> var; 
			basecase[i] = var; 
			dominant += var; 
		}
		mem[basecase] = 1.0; 
		rec(basecase, dominant, true); 
		cout << "Case #" << g+1 << ": " << endl;
		int i = 1; 
		for (auto a: results) {
			 a = round(a * 10000.0) / 100.0;
			cout << "pub " << i << ": " << a << " %"<< endl;
			i++; 
		}
	}
}
