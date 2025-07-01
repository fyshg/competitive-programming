#include <bits/stdc++.h>
using namespace std; 
typedef vector<int> vi; 
typedef pair<int, int> pii;
#define  FOR(i,a,n) for(size_t i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)

const int n = 10001;
vi adj[n];
int low[n]; int num[n];
int curnum = 0;
vector<pii> bridges;

void find_bridges(int u, int p) {
	low[u] = num[u] = curnum++;
	FORIT(i,adj[u]) {
		if (*i == p) continue;
		if (num[*i] == -1) {
			find_bridges(*i, u);
			low[u] = min(low[u], low[*i]);
		} else low[u] = min(low[u], num[*i]);
		if (low[*i] > num[u])
			bridges.push_back(make_pair(u, *i));
	}
}

int main() {
	int t; 
	cin >> t; 
	FOR(g,0,t){
	int N, M; 
	cin >> N >> M; 	
	map<pii, int> id; 
	curnum = 0; 
	bridges = vector<pii>();

	FOR(i, 1, N+1)  adj[i] = vector<int>(); 
		
	
	FOR(i, 1, M+1) {
		int u, v; 
		cin >> u >> v; 
		adj[u].push_back(v);
		adj[v].push_back(u);
		id[make_pair(u,v)] = i;
		id[make_pair(v,u)] = i;  
	}

	FOR(i,1,n) num[i] = -1;
	FOR(i,1,N+1) if (num[i] == -1)
		find_bridges(i, -1);


	vi result; 
	for( auto p : bridges) {
		result.push_back(id[p]); 
	}
	sort(result.begin(), result.end()); 

	cout << "Case #" << g+1 << ": "; 
	for (auto a : result) cout << a << " "; 
		cout << endl;
	}



	
}
