#include <bits/stdc++.h>
using namespace std; 
typedef long long ll; 
#define INF 10000000000000
#define INV 10000000000001
ll mem[1001][1001];   //t+1 n + 1
vector<vector<int>> edgelist(1001, vector<int>()); // v to v
vector<pair<int, int>> values(1001, make_pair(0, 0));  // minutes costs per vertex
int t; 

ll topdown(int time, int vertex) {
	//cout << "topdown(" << time << ", " << vertex << ") " << endl;
	if (time < values[1].first || mem[time][vertex] == INV) return INF; 
	if (mem[time][vertex] != INF ) {
		return mem[time][vertex]; 
	}
	ll result = topdown(time - values[vertex].first, vertex) + values[vertex].second; 
	for (int a : edgelist[vertex]) {
		result = min(result, topdown(time - (values[vertex].first + t), a)  + values[vertex].second ); 
	}
	mem[time][vertex] = (result == INF ? INV : result); 
	return result; 
}

int main() {
	int x; 
	cin >> x; 
	int n, m; 
	cin >> n >> m >> t; 
	
	for (int i = 0; i < m; i++) {
		int u, v; 
		cin >> u >> v; 
		edgelist[u].push_back(v); 
		edgelist[v].push_back(u); 
	}
	
	for (int i = 1; i < n+1; i++) {
		ll minutes, costs; 
		cin >> minutes >> costs;
		values[i] = make_pair(minutes, costs); 
	}

	for (int i = 0; i < 1001; i++) {
		for (int j = 0; j < 1001; j++) {
			mem[i][j] = INF; 
		}
	}
	
	mem[values[1].first][1] = values[1].second; 

	ll result = topdown(x, 1);
	if ( result >= INF) cout << "It is a trap." << endl; 
	else cout << result << endl; 


}