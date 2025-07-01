#include <bits/stdc++.h>
using namespace std; 
typedef vector<int> vi; 
typedef pair<long long, int> pii;
#define  FOR(i,a,n) for(int i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
typedef long long ll; 
#define INF 1000000000000
#define INDEX(a,x) find(a.begin(), a.end(),x) - a.begin() 

const int n = 10001;
vi visited[n]
vi adj[n]; 

int visitneighbours(int u, int gate_vertex_p, gate_vertex_c){
	int count = 0; 
	if (u == gate_vertex_p) {
		int indexneighbour = INDEX(adj[gate_vertex_p], gate_vertex_c); 
		if  (!visited[gate_vertex_c][indexneighbour]) {

		}
	}

}

vertex_cover(stack<int>& vertices, int mini, int gate_vertex, int gate_vertex_c,  int cplaced) {

	if ( iscomplete) {
		if (placed < mini || (placed == minimum && placed[gate_vertex])) {
			mini = placed; 
		}
	}

	int u = vertices.top(); vertices.pop(); 

	visitneighbours(u, true)

}

int main() {

}