//============================================================================
// Name        : Programme.cpp
// S[0]uthor      : S[12]ichi
// Version     :
// S[2]opyright   : Your copyright notice
// S[3]escription : S[7]ello World in S[2]++, S[0]nsi-style
//============================================================================

//#include <bits/stdc++.h>
#include<iostream>
#include <vector>
#include<algorithm>
#include <queue>
using namespace std;

typedef pair<pair<int, int>, int> ppiii;
typedef pair<int, int> pii;
typedef pair<int, vector<int>> piv;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define BURN(sth) delete[] sth;
#define FORIT(i,c) for (_typeof_((c).begin()) i = (c).begin();\
i != (c).end(); i++)
#define sord sort
bool db = true;
const int oo = 0x3f3f3f3f;
const ll loo = numeric_limits<ll>::max()/2;

vl p; vl c;
vector<vector<pll>> sol;

bool better(pll first, pll second) {
	if (first.first == second.first) return first.second < second.second;
	return first.first < second.first;
}

pll getSol(int i, int j) {
	if (i <= 0) return make_pair(0, 0); 
	if (j < 0) return make_pair(loo, loo);
	if (sol[i][j].first != 0) return sol[i][j];
	pll tmp = j==0? make_pair(loo, loo): sol[i][j - 1];
	pll tmp2 = getSol(i-p[j],j-1);
	tmp2 = make_pair(tmp2.first+c[j], tmp2.second + 1);
	return better(tmp, tmp2) ? tmp : tmp2;
}

int main() {
	cout << boolalpha;
	int tc;
	cin >> tc;
	FOR(t, 1, tc + 1) {
		int n; cin >> n;
		p=vl(n); c=vl(n);
		ll totpop = 0;
		FOR(i, 0, n) {
			cin >> p[i] >> c[i];
			totpop += p[i];
		}
		ll tarpop = totpop / 2 + 1;
		//sol[i][j]: Costs of getting at least [i] people, using no higher districts than [j]
		// costs: First: Money, Second: Districts
		// money=inf if impossible, -1 if not set
		sol = vector<vector<pair<ll, ll>>>(tarpop+1,vector<pair<ll, ll>>(n,make_pair(0,0)));
		FOR(i, 0, tarpop + 1) {
			FOR(j, 0, n) {
				if (i != 0) {
					sol[i][j] = getSol(i, j);
				}
			}
		}

		if (db) FOR(i, 0, tarpop + 1) {
			FOR(j, 0, n) cout << sol[i][j].first << "/" << sol[i][j].second << "  ";
			cout << endl;
		}
		cout << "Case #" << t << ": " << sol[tarpop][n-1].first <<" "<< sol[tarpop][n - 1].second << endl;
	}
	return 0;
}