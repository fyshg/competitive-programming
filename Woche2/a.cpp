#include <iostream>

using namespace std; 
#define ll long long
#define MAXN 10000
#include <cstring>

int pa[MAXN];
int rk[MAXN];
bool married[MAXN];
int ufind(int i) {
	if(pa[i] != i) pa[i] = ufind(pa[i]);
	return pa[i];
}

int uunion(int a,int b) {
a = ufind(a); b = ufind(b);
if(a == b) return 0;
if(rk[a] > rk[b])
pa[b] =a;
else
pa[a] = b;
if(rk[a] == rk[b]) rk[b]++;
return 1;
}



int main() {

	int N; 
	cin >>N; 

	for (int i = 0; i<N; ++i){
		ll a,b,c;
		cin >> a >> b >> c ;

		int money[a] = {0};
		pa[a] = a; 
		for (int j = 1; j < a; j++) {
			cin >> money[j];
			married[a] = 0; 
			pa[j] = j;
		}
		for (int j = 0; j < b; j++) {
			int p1;
			int p2; 
			cin >> p1 >> p2 ;
			uunion(p1, p2);
		}

		for (int j = 0; j< c; j++) {
			int p1; 
			int p2; 
			cin >> p1 >> p2; 
			married[p1] = 1; 
			married[p2] = 1; 
			uunion(p1,p2);
		}
		ll max = -1; 


		for ( int j = 1; j < a+1; j++) {
			
			
			if  (ufind(j) != ufind(a) && married[j] == 0 && money[j] > max ) {
				max = money[j];
			}
		}
		cout << "Case #" << i+1 << ": " << (max == -1 ? "impossible": to_string(max)) << endl; 
		memset(married, 0, sizeof(married));
		memset(pa, 0, sizeof(pa));
		memset(rk, 0, sizeof(rk));


	}
}