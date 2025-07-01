#include <bits/stdc++.h>
using namespace std; 
typedef vector<int> vi; 
typedef pair<int, int> pii;
#define  FOR(i,a,n) for(int i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
typedef long long ll; 
#define INF 10000000
#define INDEX(a,x) find(a.begin(), a.end(),x) - a.begin() 

int p[101];
int find(int x) {
return p[x] == x ? x : p[x] = find(p[x]); }
void unite(int x, int y) { p[find(x)] = find(y); }


struct edge {
	int u,v; 
	int demolition, construction, renovation; 
	int treevalue; 
	edge(int _u, int _v, int _demo, int _renovation) {
		u = _u; 
		v = _v; 
		demolition = _demo; 
		renovation = _renovation; 
		treevalue = -1; 
		construction = 0;
	}
	edge(int _u, int _v, int _demo, int _renovation, int _tre) {
		u = _u; 
		v = _v; 
		demolition = _demo; 
		renovation = _renovation; 
		treevalue = _tre;  
		construction = 0;
	}

	edge(){}; 
};

int main() {
	int t; 
	cin >> t; 
	FOR(g,0,t){
		int n, ed; 
		cin >> n >> ed;
		map<pii, vector<edge>> edges; 
		int total = 0; 
		FOR(i,0,ed){
			int u, v, demo, renovation; 
			cin >> u >> v >> demo >> renovation; 
			total += demo; 
			if (u > v) swap(u,v); 
			if(edges.count(make_pair(u,v))) edges[make_pair(u,v)].push_back(edge(u,v,demo, renovation)); 
			else edges.insert({make_pair(u,v), vector<edge>(1,edge(u,v,demo, renovation))});
			//edges[make_pair(u,v)].treevalue = renovation - demo;
		} 
		FOR(i, 0,  ((n*(n-1))/2) ){
			int u, v, build; 
			cin >> u >> v >> build; 
			pii e = make_pair(u,v); 
			if(!edges.count(e)) edges.insert({e, vector<edge>(1,edge(u, v, 0,INF, build))});
			else for(auto& E: edges[e] ) {
				E.construction = build; 
				E.treevalue = min(E.renovation - E.demolition, E.construction);
				//cout << " edge " << u << " : " << v << " with dem: " << E.demolition << " reno: " << E.renovation << " build: " << build << " value: " << E.treevalue << endl;		
			} 
			//if (edges[e].treevalue == -1 )edges[e].treevalue = build;
	
			
		}
		//cout << "summed demolition costs " << total << endl;
		vector<edge> edgelist; 
		for (auto b: edges) for (auto a : b.second ) edgelist.push_back(a); 

		FOR(i,0,101) p[i] = i;
		sort(edgelist.begin(), edgelist.end(), [] (edge a, edge b) {
			return a.treevalue < b.treevalue; 
		}); 

		
		FORIT(e, edgelist) if(find(e->u) != find(e->v)) {
			unite(e->u, e->v); 
			total += e->treevalue; 
			//cout << "build " << e->u << ": " << e->v <<  " with value: " << e->treevalue << endl;
		}

		cout << "Case #" << g+1 << ": " << total << endl;
	}
}
