#include <bits/stdc++.h>
using namespace std; 
typedef long long ll; 
struct coords {
	ll x,y,z; 
};

int main() {
	int t; 
	cin >> t; 
	for (int j = 0; j< t; j++) {
		int h, n;
		cin >> h >> n; 
		vector<coords> pile; 
		pile.reserve(6*n);
		for (int i = 0; i < n; i++) {
			ll x, y, z; 
			cin >> x >> y >> z; 
			coords a = {x,y,z};
			coords b = {x,z,y};
			coords c = {y,x,z};
			coords d = {y,z,x}; 
			coords e = {z, x, y}; 
			coords f = {z, y, x};
			pile.push_back(a); pile.push_back(b); pile.push_back(c); pile.push_back(d); pile.push_back(e); pile.push_back(f);
		}

		sort(pile.begin(), pile.end(), [] (coords a, coords b) {
			if (a.x == b.x) {
				if (a.y == b.y) {
					return a.z < b.z;
				}
				return a.y < b.y; 
			}
			return a.x < b.x; 
		});
		
		vector<ll> mem; 
		mem.push_back( pile[0].z); 
		for (int i = 1; i < pile.size(); i++) {
			ll maxi = pile[i].z;
			for (int h = 0; h < i; h++ ) {
				if (pile[i].x > pile[h].x && pile[i].y > pile[h].y) {
					maxi = max(pile[i].z + mem[h], maxi);
				}
			}
			mem.push_back(maxi); 
		}
		

		cout << "Case #" << j+1 << ": " << ((*max_element(mem.begin(), mem.end())) >= h ? "yes" : "no") << endl;
	}
}