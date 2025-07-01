#include <bits/stdc++.h>
using namespace std; 
typedef vector<int> vi; 
typedef pair<int, int> pii;
#define  FOR(i,a,n) for(int i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)

const int n = 100001;  
int ingoing[n]; 
vi adj[n]; 
vi order; 

int main() {
	int t; 
	cin >> t; 
	FOR(g,0,t) {
		int N, M; 
		cin >> N >> M; 
		FOR(i,0,N+1) { 
			ingoing[i] = 0;
			adj[i] = vi(); 
		}
		order = vi(); 
		FOR(i,0,M) {
			int u, v; 
			cin >> u >> v; 
			adj[u].push_back(v);
			ingoing[v]++;
		}
		
		stack<int> zeroes; //first entry is ingoing vertices, second is id 
		FOR(i, 1, N+1) if (ingoing[i] == 0) zeroes.push(i);	 
		
		bool recheck = false; 
		bool missing = false; 
		while (!zeroes.empty()){
			int elem = zeroes.top(); zeroes.pop(); 
			order.push_back(elem);
			if ( !zeroes.empty()) missing = true; 
			FORIT(i,adj[elem])  if (--ingoing[*i] == 0) zeroes.push(*i) ;
		}
		if (order.size() != N) recheck = true; 

		cout << "Case #" << g+1 << ": "; 
		if(recheck) cout << "recheck hints" << endl; 
		else if (missing) cout << "missing hints" << endl; 
		else { 
			for (auto a: order)  cout << a << " "; 
				cout << endl; 
		}
		
	}
}