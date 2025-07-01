#include <bits/stdc++.h>
using namespace std; 


vector<float> results; 
int dominant; 
vector<char> basecase; 
int maxi; 

map<vector<char>, double> mem; 
//array<array<array<array<array<float, 50>,50>,50>,50>,50> test = {0};  
//float test[50][50][50][50][50];

//float memfind( vector<char>& dist) {
	//while(dist.size() < 5) dist.push_back(0); 
	//return test[dist[0]][dist[1]][dist[2]][dist[3]][dist[4]]; 
	//if (!mem.count(dist)) return 0.0; 
	//return mem[dist]; 
//}
/*
void amemset(vector<char>& dist, float value) {
	while(dist.size() < 5) dist.push_back(0); 
	test[dist[0]][dist[1]][dist[2]][dist[3]][dist[4]] = value; 
}
*/

void rec(vector<char>& dist, char n) { 
	float p = 0; 
	for (char i = 0; i < dist.size(); ++i) {	
			vector<char> copy = dist; 

			if (copy[i] <= basecase[i]) continue; 
			--copy[i];
			p += ((float) (dist[i]-1) / (float) (n-1)) * mem[copy]; 
		
			
		} 
		mem[dist] = p; 
		//amemset(dist, p); 
}
	
void backtrack(vector<char>& dist, char balls, char boxes, char spendballs) {
	if (boxes == 1) {
		dist[0]+= balls;
		spendballs += balls;  

		rec(dist, spendballs);
		//for (auto a: dist) cout << a << " "; 
		//cout << ": " << mem[dist] << " spenT: " << spendballs <<  endl; 

		if (spendballs == maxi ) {
 		char maxelem = *(max_element(dist.begin(), dist.end())); 
		char count = 0; 
		for (char i = 0; i < dist.size(); ++i) {
			if (dist[i] == maxelem) ++count; 
		}
		for(char i = 0; i < dist.size(); ++i) {
			if (dist[i] == maxelem) results[i]+= mem[dist] * ((float) 1 / (float) count); 
		} 

		}

		spendballs -= balls; 
		dist[0]-=balls; 
	return; 
	}
	for (char i = 0; i <= balls; ++i) {
		dist[boxes-1] +=  i; 
		--boxes; 
		spendballs += i; 
		backtrack(dist, balls - i, boxes, spendballs); 
		spendballs -= i; 
		++boxes; 
		dist[boxes-1] -= i; 
	}
	

	return; 

}



int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t; 
	cin >> t; 
	for( char g = 0; g < t; ++g) {
		int n; 
		maxi = 0; 
		cin >> n >> maxi; 
		basecase = vector<char>(n); 
		dominant = 0; 
		//test = new float[50][50][50][50][50]();
		mem = map<vector<char>, double>(); 
		results = vector<float>(n,0);
		for(char i = 0; i < n; i++) {
			int var; 
			cin >> var; 
			basecase[i] = var; 
			dominant += var; 
		}
		//amemset(basecase, 1.0); 
		mem[basecase] = 1.0;
		for (char i = dominant +1; i <=maxi; i++) {
			//cout << " balls: " << (i - dominant) << endl; 
			auto cop = basecase; 
			backtrack(cop, i - dominant, n, dominant); 
		}
		cout << "Case #" << g+1 << ": " << "\n";
		int i = 1; 
		for (auto a: results) {
			cout << fixed; 
			 a = round(a * 10000.0) / 100.0;
			cout << "pub " << setprecision(2) << i << ": " << a << " %"<< "\n";
			i++; 
		}

	}
}
