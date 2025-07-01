#include <bits/stdc++.h>
using namespace std; 
typedef long long ll; 

int main() {
	int t; 
	cin >> t; 
	for (int g = 0; g < t; g++) {
		int n; 
		cin >> n; 
		vector<pair<int,int>> farmers;   //iq   weight
		farmers.reserve(n); 
		for (int i = 0; i < n; i++) {
			int iq, weight; 
			cin >> iq >> weight; 
			farmers.push_back(make_pair(iq, weight)); 
		}
		sort(farmers.begin(), farmers.end(), [] (auto a, auto b) {
			if (a.second == b.second) return a.first > b.first; 
			return a.second > b.second; 
		});

		
		vector<int> mem = vector<int>(); // Index des Elements, dass aktuell die längste Kette der Größe i-1 bildet; 
		vector<int> pre(n+1, 0); // Vorgänger des Elements i 
		mem.push_back(0); //Zeigt auf Element mit höchstem gewicht
		for (int i = 1; i < n; i++) {
			auto candidate = farmers[i]; 
			for (int j = mem.size()-1; j >=0; j--) {
				auto current = farmers[mem[j]]; 
				//cout << " cand: " << candidate.first  << ", " << candidate.second << " currentw: " << current.first  << ", " << current.second << endl;
				if (candidate.first >= current.first && candidate.second < current.second ) {
					if ( j == mem.size() - 1 ) mem.push_back(i); 
					else mem[j+1] = i; 
					pre[i] = mem[j]; 
					break; 
				} else if (candidate.first < current.first && candidate.second <= current.second && (j == 0 || (farmers[pre[mem[j]]].second > candidate.second && farmers[pre[mem[j]]].first <= candidate.first))   ) {
					pre[i] = pre[mem[j]]; 
					mem[j] = i; 
					break; 
				}


			}
			/**
			for (auto a: mem) {
			cout << "(" << farmers[a].first << ", " << farmers[a].second << ") " ; 
			}
			cout << endl;
			**/

			
		}
		
		cout << "Case #"<< g+1 << ": " << mem.size() << endl; 
	}
}