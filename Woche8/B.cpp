#include <bits/stdc++.h>
using namespace std; 

bool visited[100000] = {0}; 
int n; 
int depth( int i, vector<vector<int>>& edges, vector<vector<int>>& reachble) {
	 
	visited[i] = true; 
	if (edges[i].size() == 1)  {
		return 1;
	}

	int j = 0; 
	int sum = 1; 
	for (int neighbour : edges[i]) {
		if (!visited[neighbour]) {
		
		reachble[i][j] = depth(neighbour, edges, reachble);

		int index = -2; 
		for ( int k = 0; k < edges[neighbour].size(); k++) {
			if ( edges[neighbour][k] == i) index = k; 
		}
		reachble  [neighbour]  [index] = n-reachble[i][j];

		//cout << i << " | " << neighbour << " = " << reachble[i][j] << endl;
		//cout << neighbour << " | " << i  << " with index: " << index <<  " = " << reachble[neighbour][index] << endl;

		sum += reachble[i][j];
		
		}
		j++; 
	}


	return sum; 
}

int main() { 

	int t; 
	cin >> t; 
	for (int g = 0; g < t; g++) { 
		cin >> n;
		vector<vector<int>> edges(n, vector<int>()); 
		vector<vector<int>> reachble(n, vector<int>());
		fill(begin(visited), end(visited), false); 
		for (int i = 0; i < n-1; i++) {
			int u, v; 
			cin >> u >> v; 
			edges[u].push_back(v);
			reachble[u].push_back(v);
			edges[v].push_back(u);
			reachble[v].push_back(u); 
		}

		int begin = 0; 
		for (int i = 0; i < n; i++) {
			if (edges[i].size() > 1) {
				begin = i; 
				break; 
			}
		}
		depth( begin, edges, reachble); 

		
		int solution = -1; 
		for (int i = 0; i < n; i++) {
			
			if (*(max_element(reachble[i].begin(), reachble[i].end())) <= floor((double)n/2) ){
				solution = i; 
				 
			}
		}
		cout << "Case #" << g+1 << ": " << (solution == -1 ? "impossible" : to_string(solution)) << endl;
	}



}