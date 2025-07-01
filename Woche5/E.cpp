#include <bits/stdc++.h>
using namespace std; 

int main() {
	int t; 
	cin >> t; 

	for (int j = 0; j < t; j++) {
		int n, k; 
		cin >> n >> k; 
		vector<pair<int, int >> cards; 
		for (int i = 0; i < n; i++) {
			int x, y; 
			cin >> x >>  y; 
			if (x < y) swap(x,y); 
			cards.push_back(make_pair(x,y)); 
		}

		sort(cards.begin(), cards.end(), [] (auto a, auto b) {
			if (a.first != b.first) return a.first > b.first; 
			else return a.second >= b.second; 
		});
		
		
		vector<int> width; 
		for (auto& a: cards) {
			if (width.empty()) width.push_back(a.second); 
			else {
			int smallest= 101; 
			int index = 0; 
			int h = 0; 
			for (int b: width) {
				if (b >= a.second && b < smallest) {
					smallest = b; 
					index = h; 
				}
				h++;
			}
			if (smallest != 101) {
				width.erase(width.begin()+index);
			}
			width.push_back(a.second); 
			}
		}
		
		
		cout << "Case #" << j+1 <<": " << (width.size() <= k ? "possible" : "impossible") << endl; 
	}
}