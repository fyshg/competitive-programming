#include <bits/stdc++.h>
using namespace std; 
typedef vector<int> vi; 
typedef pair<int, int> pii;
#define  FOR(i,a,n) for(int i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
typedef long long ll; 
const int MAXN = 2501; 
const ll oo = 0x3f3f3f3f3f3f3f3fLL; 


struct edge {
	int u, v;
	int weight;
	edge(int _u, int _v, ll _w) {
		u = _u;
		v = _v;
		weight = _w;
	}
};

vector<edge> adj[MAXN];
ll dist[MAXN];


void dijkstra(int start) {
	FOR(i,0,MAXN) dist[i] = oo;
	dist[start] = 0;
	priority_queue<pii, vector<pii>, greater<pii> > pq;
	pq.push(make_pair(dist[start], start));
	while (!pq.empty()) {
		int u = pq.top().second;
		int c = pq.top().first;
		pq.pop();
		if (dist[u] != c) continue;
		FORIT(i,adj[u]) if (i->weight + dist[u] < dist[i->v]) {
			dist[i->v] = i->weight + dist[u];
			pq.push(make_pair(dist[i->v], i->v));
		}
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int t; 
	cin >> t; 
	FOR(g,0,t){
		FOR(i,0,MAXN) adj[i] = vector<edge>(); 
		int n, m; 
		cin >> n >> m; 
		FOR(i,0,m) {
			int u, v; 
			ll w; 
			cin >> u >> v >> w; 
			adj[u].push_back(edge(u,v,w)); 
			adj[v].push_back(edge(v,u,w)); 
		}
		ll total = 0; 
		FOR(i,1,n+1) {
			dijkstra(i); 
			FOR(j,1,n+1) total += 2 * dist[j]; 
		}
		cout << "Case #"<< g+1 << ": " << total << endl; 
	}

}