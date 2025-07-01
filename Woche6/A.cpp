#include <bits/stdc++.h>
using namespace std; 

int main() {
	int t; 
	cin >> t; 
	for (int j = 0; j < t ; j++) {
		int n, c; 
		cin >> n >> c; 

		vector<int> coin; 

		for (int i = 0; i < n; i++) {
			int temp; 
			cin >> temp; 
			coin.push_back(temp); 
		}

		int mem[c+1]; 
		mem[0] = 0; 
		mem[1] = 1; 
		vector<vector<int>> amounts; 

		vector<int> a(n,0); 
		vector<int> b(n,0); 
		b[0] = 1; 
		amounts.push_back( a); 
		amounts.push_back(b);

		
		for (int i = 2; i <= c; i++) {

			int result = 1000000; 
			vector<int> balance; 
			int k = 0; 
			for (int d: coin) {
				if (d <= i) {
					int rec = 1 + mem[i -d]; 
					if (rec < result) {
						result = rec; 
						balance = amounts[i-d]; 
						balance[k]++;  
					}
					k++;
				}
			}
			mem[i] = result; 
			amounts.push_back(balance); 
		}

		
		cout << "Case #" << j+1 << ": "; 
		
		for (auto d : amounts[c]){
			cout << d << " "; 
		}
		
		cout << endl; 

	}
}