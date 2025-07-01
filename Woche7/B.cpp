#include <bits/stdc++.h>
using namespace std; 
vector<vector<int>> edgelist;

pair<int, int> rec(int vertex, int dontvisit) {
	//cout << vertex << " " << dontvisit <<  endl; 
	if (edgelist[vertex].size() == 1) return make_pair(1,0); 
	pair<int, int> result = make_pair(1,0); 
	for(int neighbour: edgelist[vertex]) {
		if (neighbour != dontvisit) {
		pair<int, int> nV = rec(neighbour, vertex); 
		result.first += nV.second; 
		result.second += max(nV.second, nV.first); 
	}
	}
	return result; 

}
int main() {
	int t; 
	cin >> t; 
	for (int g = 0; g < t; g++) {
		int n; 
		cin >> n; 
		edgelist = vector<vector<int>>(n+1, vector<int>());
		for (int i = 0; i < n-1; i++) {
			int u, v; 
			cin >> u >> v; 
			edgelist[u].push_back(v);
			edgelist[v].push_back(u); 
		}
		int start = 0; 
		for(int i = 1; i < n+1; i++){
			if (edgelist[i].size() != 1) {
				start = i; 
				break; 
			}
		}


		int end; 
		if (n != 2) {
		auto result = rec(start, start);
		end = max(result.first, result.second); 
		} else end = 1; 
		
		cout << "Case #" << g+1 << ": " << end << endl; 
 
	}
}