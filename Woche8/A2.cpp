#include <bits/stdc++.h>
using namespace std; 
typedef vector<int> vi; 
typedef pair<int, int> pii;
#define  FOR(i,a,n) for(size_t i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)

const int n = 10001;  

int low[n]; int num[n]; vi licomp[n]; int comp[n];  int ccomp; int curnum; 
stack<int> st; 

vi adj[n];
int visited[n]; 
bool is_start[n]; 
bool is_end[n];
bool visi[n]; 
vi order; 
bool cycle = false; 
//returns true if visited component contains a cylce .. 

void toposort(int u) {

	if(visi[u]) return; 
	visi[u] = true; 

	FORIT(i, adj[u]) toposort(*i); 

	order.push_back(u); 


}

void scc(int u) {
	st.push(u); low[u] = num[u] = curnum++;
	FORIT(i,adj[u])
	if (num[*i] == -1) {
		scc(*i); low[u] = min(low[u], low[*i]);
	} else if (comp[*i] == -1)
		low[u] = min(low[u], num[*i]);

	if (num[u] == low[u]) {
		while (true) {
			int cur = st.top(); st.pop();
			licomp[ccomp].push_back(cur); 
			comp[cur] = ccomp; 
			if (licomp[ccomp].size() > 1 ) cycle = true; 
			if (cur == u) break;
		}
		ccomp++;
	}
}


bool new_component(int u, int num) {
	if (visited[u] != -1 && visited[u] != num) return false; 
	if (visited[u] != -1 && visited[u] == num) return true; 
	visited[u] = num;
	FORIT(i, adj[u]) if( !new_component(*i, num)) return false; 
	return true; 
}
int main() {
	int t; 
	cin >> t; 
	FOR(g,0,t) {
		int N, M; 
		cin >> N >> M; 
		FOR(i, 0, N+1) {
			visited[i] = -1; 
			is_start[i] = true; 
			is_end[i] = true; 
 			adj[i] = vi(); 
			licomp[i] = vi(); 
		}
		FOR(i,0,M) {
			int u, v; 
			cin >> u >> v; 
			adj[u].push_back(v); 
			is_start[v] = false; 
			is_end[u] = false; 
		}
		bool missinghints = false; bool recheckhints = false; 
		int components = 0; int starts = 0; int ends = 0; 
		cycle = false; 
		ccomp = curnum =  0;
		st = stack<int>(); 

		// check for sccs ... 
		FOR(i,0,N+1) comp[i] = num[i] = -1; 
		FOR(i,1,N+1) if (num[i] == -1) scc(i);
		
		//check for multiple starts and count ends
		FOR(i,1,N+1) { //checks components
			if (is_start[i]) {
				starts++; 
				if (new_component(i, i)){ 
				components++; 
			        } else recheckhints = true; // multiple starts in the same component
			} 
			if (is_end[i]) ends++; 
		}

		if(cycle) recheckhints = true; // a component has a cycle
		//if (cycle) cout << "Graph has cycle" << endl;
		//if (recheckhints) cout << "graph contains multiple starts or a cycle" << endl;
		if (!recheckhints){
			//schauen ob alle Komponenten einen gültigen Weg haben 
			// wenn nicht -> rechceckhints
			//sonst missinghints ausser components = 1; 
			int totalsize= 0; 
			FOR(i,1,N+1) visi[i] = false; 
			FOR(i,1,N+1) {
				if(is_start[i]) {
					order = vi(); 
					toposort(i);
					totalsize += order.size();
					
					reverse(order.begin(), order.end());
					if (order.size() > 1) FOR(j,0, order.size()-1) {
						if (find(adj[order[j]].begin(), adj[order[j]].end(), order[j+1]) == adj[order[j]].end()) recheckhints = true; 
					} 
				}
			}
			//cout << totalsize << "c: " << components << ", " << starts << ", " << ends << endl;
			if (totalsize != N || starts != ends) recheckhints = true; 
			else if (totalsize == N && components > 1 && starts == ends && starts == components) missinghints = true;  
			if ( )
		}



		cout << "Case #" << g+1 << ": "; 
		if( recheckhints) cout << "recheck hints" << endl; 
		else if (missinghints) cout << "missing hints" << endl; 
		else { 
			for (auto a: order)  cout << a << " "; 
				cout << endl; 
		}
	}
}