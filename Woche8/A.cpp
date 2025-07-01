#include <bits/stdc++.h>
using namespace std; 

//returns true if G consists of multiple components. 
bool components(vector<vector<int>>& edges, int n) {
	vector<int> component;

	vector<bool> visited(n+1, false); 
	queue<int> Q;
	Q.push(1);	
	visited[1] = false; 
	while (!Q.empty()) {

	}

}
//returns false if g contains a cycle
bool toposort(int u, const vector<vector<int>>& edges, vector<bool>& visited, vector<bool>& in_result, vector<int>& order ) {

	if(visited[u]) return true; 


	visited[u] = true; 
	for(int neighbour : edges[u]) {
		bool b = toposort(neighbour, edges, visited, in_result, order); 
		if (!b) return false; 
	}

	
	for(int neighbour : edges[u]) {
		if( !in_result[neighbour] ) return false; 
	}

	order.push_back(u);
	in_result[u] = true; 
	return true;  


}

int main() {
	int t; 
	cin >> t; 
	for (int g = 0; g < t; g++) {
		int n, m; 
		cin >> n >> m; 
		cout << "Case #" << g+1 << ": " ;

		vector<vector<int>> edges(n+1, vector<int>()); 
		vector<bool> start(n+1, true);

		vector<vector<int>> directed_edges(n+1, vector<int>());
		
		for (int i = 0; i < m; i++) {
			int u, v; 
			cin >> u >> v; 
			edges[u].push_back(v); 
			start[v] = false; 
		}
		
		for(int i = 0; i < m; i++) {
			if (edges[])
		}
		 	
		bool b = true; 
		int beginning = 0; 
		for (int i = 1; i< n+1; i++) {
			if(start[i]) {
				if(beginning != 0) {
					b = false; 
					break; 
				} else {
					beginning = i;
				}
			}
		}
		if (beginning == 0) b = false; 

		vector<bool> visited(n+1, 0); 
		vector<bool> in_result(n+1, 0); 

		vector<int> order; 
		cout << "begining: " << beginning << endl; 
		if (b) b = toposort(beginning, edges, visited, in_result, order);

		reverse(order.begin(), order.end());
		for (auto a : order) cout << a << " ";
						cout << endl;

		if (!b) {
			cout << "recheck hints found cycle or multiple beginnings" << endl;
		} else {

			if (order.size() < n) cout << "missing hints" << endl; 
			else {	
				bool possible = true; 
				for (int i = 0; i < n-1; i++) {
					if (find(edges[order[i]].begin(), edges[order[i]].end(), order[i+1]) == edges[order[i]].end() ) {
						for (auto a : edges[order[i]]) cout << a << " ";
							cout << endl;
						cout << " found no edge between " << order[i] << " and " << order[i+1] << endl;
						possible = false; 
						break; 
					}
				}
				if (!possible) cout << "recheck hints" << endl; 
				else {
					for (auto a : order) cout << a << " ";
						cout << endl;
				}
			}
		}



	}
}
