#include <iostream>

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
int a1 = a; 
int b1 = b; 
a = ufind(a); b = ufind(b);
if(a == b) return 0;	
//cout << "union(" << a1 << ", " << b1 << ") " << endl;



if(rk[a] > rk[b])
pa[b] =a;
else{
pa[a] = b;
}
rk[a]= rk[a]+ rk[b];
rk[b]= rk[a];

if (hates[a] == 0 && hates[a1] != 0 ) {hates[a] = ufind(hates[a1]); }
if (hates[b] == 0 && hates[b1] != 0 ) {hates[b] = ufind(hates[b1]); }
if (hates[a] != 0 && hates[b] != 0 && hates[b] != hates[a]){
	uunion(hates[a], hates[b]);

}

return 1;
}

int main() {
	int t;
	cin >> t; 
	for (int j = 0; j < t; j++) {
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
				c1 = ufind(c1);
				c2 = ufind(c2);

				if (hates[c1] != 0) {
					uunion(hates[c1], c2); 
				} 
				if (hates[c2] != 0){
					uunion(hates[c2], c1);
				}

				hates[c1] = c2; 
				hates[c2] = c1; 
			}
		}

		//cout << " 	Size of leas alliance " << rk[ufind(1)] << endl; 
		//cout << " 	Half size: " << (float) n/2 << endl; 

		cout << "Case #" << j+1 << ": "<< ( rk[ufind(1)] > ((float) n / 2)  ? "yes" : "no") << endl; 
	}
}