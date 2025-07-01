#include <bits/stdc++.h>
using namespace std; 
typedef long long ll; 
typedef vector<ll> vi; 
typedef pair<ll, ll> pii;
#define  FOR(i,a,n) for(ll i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
#define MAXN 205
ll f[MAXN][MAXN] = {0}; // way to and way back; 
ll cap[MAXN][MAXN] = {0}; 
vi adj[MAXN]; //for fast iteration ..  
ll pre[MAXN] = {-1}; 

constexpr ll INF = 0x3f3f3f3f3f3f3f3fLL;

//returns true if path exists else false;  
bool bfs(ll s, ll t) {
	queue<ll> Q; 
	Q.push(s); 
	while(!Q.empty() && Q.front() != t) {
		ll u = Q.front(); Q.pop(); 
		FORIT(i, adj[u]) if (pre[*i] == -1 && f[u][*i] != 0) {
			pre[*i] = u; 
			Q.push(*i); 
		}
	}
	if(pre[t] == -1)  return false; //no path to t; 
	ll mini =  INF; 
	stack<pii> path; 
	ll a = t; 
	while (a != s) {
		mini = min(mini, f[pre[a]][a]); 
		path.push( make_pair(pre[a], a) ); 
		a = pre[a]; 
	}
	//flow mini through all edges on the path .. 

	while(!path.empty()) {
		pii ver = path.top(); path.pop(); 
		ll u = ver.first; ll v = ver.second; 
		f[u][v] -= mini; 
		f[v][u] += mini; 
	}

	return true; 
}

int main(){
	ll t; 
	cin >> t; 
	FOR(g,0,t){
		ll n; 
		cin >> n; 
		FOR(i,0,MAXN) adj[i] = vi(); 
		FOR(i,0,MAXN) FOR(j,0,MAXN) cap[i][j]  = 0; 
		ll enemy[MAXN] = {false}; 
		ll s = MAXN - 2; 
		ll t = MAXN -1 ; 
		ll regions = 0; 
		FOR(i,0,n) {
			ll count; 
			cin >> count; 
			if (count == 0) enemy[i] = true; 
			else {
				adj[s].push_back(i); 
				adj[i].push_back(s);
				adj[i].push_back(i+100); 
				adj[i+100].push_back(i); 
				cap[i][i+100] = INF; 
				cap[s][i] = count; 
				++regions; 

				adj[i+100].push_back(t);
				adj[t].push_back(i+100);  
				cap[i+100][t] = 1; 
				
			}
		}
		vi borders; 
		FOR(i,0,n) {
			FOR(j,0,n) {
				char c; cin >> c; 
				if (c == 'Y') {
					if (enemy[i] && !enemy[j]) { 
						if(find(borders.begin(), borders.end(),j+100) == borders.end()) borders.push_back(j+100); 
						//border region
					} else if ( !enemy[i] && !enemy[j]) {
						adj[i].push_back(j+100); 
						adj[j+100].push_back(i);
						cap[i][j+100] = INF;  //Zwischenkante 
					}
				}	
			}
		}


		//Starte die Binäre suche ... 
		ll inner_regions = regions - borders.size(); 
		ll lo = 1,
		hi = 100* 100;
		while (lo + 1 < hi) {
			ll m = (lo + hi) / 2;

			  // p ist true, wenn der Fluss nicht erfüllt ist ... 

			FOR(x,0,MAXN) FOR(y,0,MAXN) f[x][y] = cap[x][y]; //reset
			FORIT(a, borders) f[*a][t] = m; 

			//cout << "flow" << endl;
			//FOR(i, 0, MAXN) FORIT(a, adj[i]) cout << i << " : " <<*a <<  "  = " << f[i][*a] << endl; 

			do{
				FOR(j,0,MAXN) pre[j] = -1;			
			} while (bfs(s, t));

			//cout << "After FLOW" << endl; 
			//FOR(i, 0, MAXN) FORIT(a, adj[i]) cout << i << " : " <<*a <<  "  = " << f[i][*a] << endl; 

			ll total = 0; 
			FORIT(a, adj[t]) {
				total += f[t][*a]; 	
			}

			//cout << " total: " << total << endl;
			//cout << "should: " << borders.size() * m + inner_regions << endl; 
			//cout << m << " p: " << p << endl;
			if (total != ((ll)borders.size() * m + inner_regions)) {
				hi = m;
			} else {
				lo = m;
			}
		}

		cout << "Case #" << g+1 << ": " << lo << endl; 

	}
}