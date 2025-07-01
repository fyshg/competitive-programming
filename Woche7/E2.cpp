#include <bits/stdc++.h>
using namespace std; 
typedef long long ll; 
vector<pair<ll,ll>> A; 
vector<pair<ll, ll>> B; 
// [carA][carB][Direction] A == 0, B == 1; 
#define INF  1000000000000000
// tim + 10 if at same time ..
//else start2 + duration 2 .. 
struct res{
	pair<ll, ll> switch_d; 
	pair<ll, ll> stay_d; 
};

vector<vector<vector<res>>> mem; 


pair<ll, ll> same_direction(ll start1, int car, char typ, ll duration1) { 
	if (start1 == INF) return make_pair(INF, 0); 
	ll start2 = (typ == 'A' ? A[car].first : B[car].first); 
	ll duration2 = (typ == 'A' ? A[car].second : B[car].second); 
	auto start = max(start1 + 10, start2); 
	return make_pair(start, max(start1 + duration1 + 10  - start, duration2)) ;	 
}

res fun(int carA, int carB, int dir){
	//cout << "fun (" << carA << ", " << carB << ", "  << dir << ") " << endl;
	if (carA < 0 || carB < 0 || (carA == carB && carA == 0)) return res{make_pair(INF, 0), make_pair(INF, 0)};
	if (( carB == 0 && dir == 1) || (carA == 0 && dir == 0)) return res{make_pair(INF, 0), make_pair(INF, 0)};
	if (mem[carA][carB][dir].switch_d.first < INF) return mem[carA][carB][dir];

	pair<ll, ll> result = make_pair(INF, 0); 
	if (dir == 0 && carB > 0) {
		result = fun(carA-1, carB, 1).switch_d; //Verschiedene Richtung
		if (A[carA].first < result.first + result.second) result.first += result.second; 
		else result.first = A[carA].first; 
		result.second = A[carA].second;  
	}	
	else if (dir == 1 && carA > 0) {
		result = fun(carA, carB-1, 0).switch_d; 
		if (B[carB].first < result.first + result.second) result.first += result.second; 
		else result.first = B[carB].first; 
		result.second = B[carB].second;   
	}
	
	//cout << "Calling wait time with " << carA << " " << carB << " " << dir << endl; 
	pair<ll, ll> result2  = make_pair(INF, 0);  
	if (dir == 0 && carA > 0) {
		auto test = fun(carA-1, carB, 0);
		auto a = same_direction(test.switch_d.first, carA, 'A', test.switch_d.second); 
		auto b = same_direction(test.stay_d.first, carA, 'A', test.stay_d.second); 

		if (a.first + a.second < b.first + b.second) result2 = a; 
		else result2 = b; 
		
	} else  if (dir == 1 && carB > 0) {
		auto test = fun(carA, carB-1, 1);
		auto a =  same_direction(test.switch_d.first, carB, 'B', test.switch_d.second);
		auto b = same_direction(test.stay_d.first, carB, 'B', test.stay_d.second); 
		if (a.first + a.second < b.first + b.second) result2 = a; 
		else result2 = b; 
			

	}


	res ret; 
	if (result.first + result.second < result2.first + result2.second) ret = {result, result2}; 
	else ret = {result2, result}; 
	mem[carA][carB][dir] =  ret; 
	//cout << "mem[" << carA << ", " <<  carB << ", " << dir <<"] =  "  << ret.switch_d.first  << " : " << ret.switch_d.second << " - " << ret.stay_d.first  << " : " << ret.stay_d.second<< endl;
	//cout << result.first << " : " << result.second << " | " << result2.first << " : " << result2.second << endl;
	return ret; 
}



int main() {
	int t; cin >> t; 
	for (int g = 0; g < t; g++) {
		int n; 
		cin >> n; 
		A = vector<pair<ll,ll>>(1, make_pair(0, 0)); 
		B = vector<pair<ll, ll>>(1, make_pair(0,0)); 
 
		for (int i = 0; i < n; i++) {
			char c; 
			ll s, d; 
			cin >> c >> s>> d; 
			if (c == 'A')  A.push_back(make_pair(s,d)); 
			else B.push_back(make_pair(s,d)); 
		}

		mem = vector<vector<vector<res>>> (A.size(), vector<vector<res>>(B.size() , vector<res>(2, res{make_pair(INF, 0), make_pair(INF, 0)})));
		if (A.size() > 1) mem[1][0][0] = res{A[1], A[1]};
		if (B.size() > 1)  mem[0][1][1] = res{B[1], B[1]};
		//if (A.size() > 1) cout << "mem[1, 0, 0] =  "  << A[1].first  << " : " << A[1].second<< endl;
		//if (B.size() > 1) cout << "mem[0, 1, 1] =  "  << B[1].first  << " : " << B[1].second<< endl;
		auto one = fun(A.size()-1, B.size()-1, 0);
		auto two = fun(A.size()-1, B.size()-1, 1); 
		

		cout << "Case #" <<  g+1 << ": " << min(one.switch_d.first + one.switch_d.second, two.switch_d.first + two.switch_d.second) << endl; 
	}


}