#include <bits/stdc++.h>
using namespace std; 
typedef vector<int> vi; 
typedef pair<int, int> pii;
#define  FOR(i,a,n) for(int i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
typedef long long ll; 
#define INF 1000000
int cap[501][501] = {0};
int f[501][501] = {0}; // way to and way back; 
vi adj[501]; //for fast iteration ..  
int pre[501]; 

//returns true if path exists else false; 
bool bfs(int s, int t) {
	queue<int> Q; 
	Q.push(s); 
	while(!Q.empty() && Q.front() != t) {
		int u = Q.front(); Q.pop(); 
		//cout << u << endl;
		FORIT(i, adj[u]) if (pre[*i] == 0 && f[u][*i] != 0) {
			pre[*i] = u; 
			Q.push(*i); 
		}
	}
	if(pre[t] == 0) return false; //no path to t; 

	int mini = 10000; 
	stack<pii> path; 
	int a = t; 
	while (a != s) {
		mini = min(mini, f[pre[a]][a]); 
		path.push( make_pair(pre[a], a) ); 
		a = pre[a]; 
	}
	//flow mini through all edges on the path .. 

	while(!path.empty()) {
		auto ver = path.top(); path.pop(); 
		int u = ver.first; int v = ver.second; 
		f[u][v] -= mini; 
		f[v][u] += mini; 
	}

	return true; 
}

int main() {
	int t; 
	cin >> t; 
	FOR(g,0,t){
		int n, m; 
		cin >> n >> m; 
		FOR(i,0,501) adj[i] = vi(); 
		FOR(i,0,501) FOR(j,0,501) cap[i][j] = f[i][j] = 0; 
		FOR(i,0,m){
			int u, v, c; 
			cin >> u >> v >> c; 
			cap[u][v] += c; cap[v][u] += c; 
			f[u][v] += c; f[v][u] +=  c; 
			if( find(adj[u].begin(), adj[u].end(),v) == adj[u].end()){
			adj[u].push_back(v); 
			adj[v].push_back(u); 
			}
		}
		do{
			FOR(i,0,n+1) pre[i] = smallest[i] = 0; 
		} while (bfs(1, n)); 

		ll result = 0; 
		FORIT(i, adj[1]) result += ((ll)cap[1][*i]) - ((ll)f[1][*i]); 

		cout << "Case #" << g+1 << ": " << (result == 0 ? "impossible" : to_string(result))<< endl;   
		//find path from s to t...
	}
}