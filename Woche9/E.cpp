#include <bits/stdc++.h>
using namespace std; 
typedef vector<int> vi; 
typedef pair<int, int> pii;
#define  FOR(i,a,n) for(int i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
typedef long long ll; 
#define INF 10000
#define MAXN (30*15 + 30 + 2 + 100)
int f[MAXN][MAXN] = {0}; // way to and way back; 
int cap[MAXN][MAXN]; 
int dontvisit[MAXN] = {false}; 
vi adj[MAXN]; //for fast iteration ..  
int pre[MAXN] = {-1}; 

//returns true if path exists else false; dont visit teamid in this case 
bool bfs(int s, int t) {
	queue<int> Q; 
	Q.push(s); 
	while(!Q.empty() && Q.front() != t) {
		int u = Q.front(); Q.pop(); 
		FORIT(i, adj[u]) if (pre[*i] == -1 && f[u][*i] != 0 && !dontvisit[*i]) {
			pre[*i] = u; 
			Q.push(*i); 
		}
	}
	if(pre[t] == -1) return false; //no path to t; 

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
	FOR(g,0,t) {
		int n, m; 
		cin >> n >> m; 
		vi wins(n+1); 
		vi matches(n+1,0); //how many matches does each team have
		FOR(i,0,MAXN) adj[i] = vi(); 
		FOR(i,0,MAXN) FOR(j,0,MAXN) cap[i][j]  = 0; 
		FOR(i,1,n+1) {
			int w; 
			cin >> w; 
			wins[i] = w;   
		}
		int s = 0; 
		int t = MAXN - 1; 
		int vertexid = 0; 
		map<pii, int> matchvertices;
		map<int, int> teamvertices;
		FOR(i,0,m) {
			int u, v; 
			cin >> u >> v; 
			matches[u]++; 
			matches[v]++; 
			if (u > v) swap(u,v); 
			//construct the flow graph ... 
			if(!matchvertices.count(make_pair(u,v))) {
				int matchid = ++vertexid; 
				matchvertices[make_pair(u,v)] = matchid; 
				adj[s].push_back(vertexid); 
				//connect to teams
				if(!teamvertices.count(u)){
					teamvertices[u] = ++vertexid; 
					adj[matchid].push_back(vertexid); 
					adj[vertexid].push_back(matchid); 
					adj[vertexid].push_back(t); 
					adj[t].push_back(vertexid); 
					cap[matchid][vertexid] = INF; 
				} else if (find(adj[matchid].begin(), adj[matchid].end(), teamvertices[u]) == adj[matchid].end()) {
					adj[matchid].push_back(teamvertices[u]); 
					adj[teamvertices[u]].push_back(matchid); 
					cap[matchid][teamvertices[u]] = INF; 
				}

				if(!teamvertices.count(v)){
					teamvertices[v] = ++vertexid; 
					adj[matchid].push_back(vertexid); 
					adj[vertexid].push_back(matchid); 
					adj[vertexid].push_back(t); 
					adj[t].push_back(vertexid); 
					cap[matchid][vertexid] = INF; 
				} else if (find(adj[matchid].begin(), adj[matchid].end(), teamvertices[v]) == adj[matchid].end()) {
					adj[matchid].push_back(teamvertices[v]); 
					adj[teamvertices[v]].push_back(matchid); 
					cap[matchid][teamvertices[v]] = INF; 
				}

			}

			cap[s][matchvertices[make_pair(u,v)]]++; 	//flow initialized to number of this match 
		}

		//FOR(i, 0, MAXN) FORIT(a, adj[i]) cout << i << " : " <<*a <<  "  = " << cap[i][*a] << endl; 
			

		cout << "Case #" << g+1 << ": "; 


		FOR(i,1,n+1) {    //can team x win //Fluss zu Spielen von team x auf null 
			//cout << " Round of team " << i << endl; 
			bool impossible = false; 
			FOR(j,0,MAXN) dontvisit[j] = false; 
			FOR(x,0,MAXN) FOR(y,0,MAXN) f[x][y] = cap[x][y]; 
			int maxi = wins[i] + matches[i]; 
			//cout << " maxi of " << i << ": " << maxi << " " << wins[i] << " " << matches[i] << endl;

			FORIT(a, adj[s]) { //set connections to games with i to zero 
				if (find(adj[*a].begin(), adj[*a].end(), teamvertices[i]) != adj[*a].end() ) {
					dontvisit[*a] = true; 
				}
			} 

			FOR(j,1,n+1) if ( j != i) {
				if (maxi - wins[j] < 0 ) impossible = true; 
				f[teamvertices[j]][t] = maxi - wins[j]; 
			} 
			//cout << "GRAPH: " << endl; 
			//FOR(i, 0, MAXN) FORIT(a, adj[i]) cout << i << " : " <<*a <<  "  = " << f[i][*a] << endl; 
			int outflow = 0; 
			if (!impossible){
			do{
				FOR(j,0,MAXN) pre[j] = -1;			
			} while (bfs(0, t));
			} else (outflow = -1); 

			//check if outgoing flow = matches - mi
			int matches_without_i = m - matches[i]; 
			
			FORIT(a, adj[t]) outflow += f[t][*a]; 
			
			cout << (outflow == matches_without_i ? "yes " : "no "); 
 		
		}
		cout << endl; 

	}
}