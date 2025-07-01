#include <bits/stdc++.h>
using namespace std; 
typedef vector<int> vi; 
typedef pair<long long, int> pii;
#define  FOR(i,a,n) for(int i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
typedef long long ll; 
#define INF 1000000000000

const int maxn = 100001; 
vi adj[maxn]; 
int iron, coal; 

vector<pii> coald; 
vector<pii> irond; //pair distance vertex 
bool hascoal[maxn]; 
bool hasiron[maxn]; 
//bool visited[maxn]; 
ll dist[maxn];
ll pre[maxn];
ll resdist[maxn]; 

void search_ore(char c) {
	queue<int> Q; 
	Q.push(1);
	dist[1] = 0; 
	while(!Q.empty()) {
		int u = Q.front(); Q.pop(); 
		if ( c == 'c' && hascoal[u]) {
			int a = u; 
			int distance = dist[u]; 
			while(a != -1 && (resdist[a] == -1 || resdist[a] > distance)){
				coald.push_back(make_pair(distance, a));
				resdist[a] = distance; 
				a = pre[a]; 
		
			}
			 
		}
		else if (c == 'i' && hasiron[u]) {
			int a = u; 
			int distance = dist[u]; 
			while(a != -1 && (resdist[a] == -1 || resdist[a] > distance)){
				irond.push_back(make_pair(distance, a));
				resdist[a] = distance; 
				a = pre[a]; 
		
			} 
		}

		FORIT(i, adj[u]) if (dist[*i] == -1) {
			Q.push(*i); 
			pre[*i] = u; 
			dist[*i] = 1 + dist[u]; 
			
		}
	}

}

ll search_second(char c) {

	priority_queue<pii, vector<pii>, greater<pii>> pq; 
	if (c == 'c') for(auto a: coald) { 
		pq.push(a); 
		dist[a.second] = a.first; 
	}
	else if (c == 'i') for(auto a: irond) {
	 	pq.push(a); 
	 	dist[a.second] = a.first; 
	}
	//cout << " found ore of type " << c << " : " << pq.size() << endl;
	while( !pq.empty()) {
		pii a = pq.top(); pq.pop(); 
		int u = a.second; 
		if (dist[u] != a.first) continue; 
		//cout << "current el: " << a.first <<  " : " <<  a.second << endl; 

		if (c == 'c' && hasiron[u]) return dist[u]; 
		else if (c == 'i' && hascoal[u]) return dist[u]; 

		FORIT(i, adj[u]) if ( dist[u] + 1 < dist[*i]) {
			dist[*i] = 1+ dist[u]; 
			pq.push(make_pair(dist[*i],*i)); 
			
		}
	}
	return INF; 
 }


int main() {
	int N;
	cin >> N >> iron >> coal; 
	coald = vector<pii>(); 
	irond = vector<pii>();  
	FOR(i,0, N+1) {
		adj[i] = vi(); 
		hascoal[i] = false; 
		hasiron[i] = false; 
	}

	FOR(i, 0, iron) {
		int pos; 
		cin >> pos; 
		hasiron[pos] = true; 
	}
	FOR(i, 0, coal) {
		int pos; 
		cin >> pos; 
		hascoal[pos] = true; 

	}


	FOR(i,1,N+1) {
		int size; 
		cin >> size; 
		FOR(j,0,size) {
			int v; 
			cin >> v; 
			adj[i].push_back(v);
		}
	}

	FOR(i, 0, N+1) dist[i] = pre[i] = resdist[i] = -1; 
	search_ore('c'); 
	//cout << "distance coal: " << endl;
	FOR(i, 0, N+1) dist[i] = pre[i] = resdist[i] = -1; 
	//FOR(i,1,N+1) visited[i] = false; 
	search_ore('i');
	FOR(i,1,N+1) dist[i] = INF; 

	//for(auto a: irond) cout << a.first << " : " << a.second << endl;
	ll a = search_second('c');
	FOR(i,1,N+1) dist[i] = INF; 
	//for(auto a: irond) cout << a.first << " : " << a.second << endl;

	//cout << "searching with iron as start: " << endl;
	ll b = min(search_second('i'), a); 
	cout << (b == INF ? "impossible" : to_string(b)) << endl;
}
