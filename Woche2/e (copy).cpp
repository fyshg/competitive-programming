#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <iterator>
#define MAXN 20000
using namespace std;

int hates[MAXN];
int pa[MAXN];
int rk[MAXN];
int ufind(int i) {
	if(pa[i] != i) pa[i] = ufind(pa[i]);
	return pa[i];
}

int uunion(int a,int b) {
a = ufind(a); b = ufind(b);
if(a == b) return 0;
if(rk[a] > rk[b])
pa[b] =a;
else{
pa[a] = b;
}
rk[a]= rk[a]+ rk[b];
rk[b]= rk[a];
return 1;
}

int main() {
	int t;
	cin >> t; 
	for (int j = 0; j < t; j++) {
		map<int, set<int>> hates; 
		int n, m; 
		cin >> n >> m;
		for (int i =0; i < n; ++i) {
			pa[i+1]= i+1;
			rk[i+1]=1;
			hates[i+1] = 0; 
		}
		for (int i = 0; i < m; ++i){

			char c; 
			int c1,c2;
			cin >> c >> c1 >> c2;
			if (c=='F') {
				uunion(c1,c2);
				
			} else {
				if (hates[c1] != 0) {
				uunion(hates[c1], c2); 
				} 
				hates[c1] = c2; 
				hates[c2] = c1; 
			}
		}

		
		// if 2 in the same find hate someone other, they form an alliance... 



		cout << " 	Size of leas alliance " << rk[ufind(1)] << endl; 
		cout << " 	Half size: " << (float) n/2 << endl; 

		cout << "Case #" << j+1 << ": "<< ( rk[ufind(1)] > ((float) n / 2)  ? "yes" : "no") << endl; 
	}
}