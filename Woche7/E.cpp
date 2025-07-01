#include <bits/stdc++.h>
using namespace std; 
typedef long long ll; 
vector<pair<ll,ll>> A; 
vector<pair<ll, ll>> B; 
vector<vector<vector<pair<ll, ll>>>> mem; // [carA][carB][Direction] A == 0, B == 1; 
#define INF  1000000000000000
// tim + 10 if at same time ..
//else start2 + duration 2 .. 
pair<ll, ll> same_direction(ll start1, int car, char typ, ll duration1) { 
	ll start2 = (typ == 'A' ? A[car].first : B[car].first); 
	ll duration2 = (typ == 'A' ? A[car].second : B[car].second); 
	auto start = max(start1 + 10, start2); 
	return make_pair(start, max(start1 + duration1 + 10  - start, duration2)) ;	 
}

pair<ll,ll> fun(int carA, int carB, int dir){
	//cout << " vefore mem[" << carA << ", " <<  carB << ", " << dir <<"]: "  << mem[carA][carB][dir] << endl;
	if (carA < 0 || carB < 0 || (carA == carB && carA == 0)) return make_pair(INF, 0);
	if (( carB == 0 && dir == 1) || (carA == 0 && dir == 0)) return make_pair(INF, 0);
	if (mem[carA][carB][dir].first < INF) return mem[carA][carB][dir];

	pair<ll, ll> result; 
	if (dir == 0) {
		result = fun(carA-1, carB, 1); //Verschiedene Richtung
		if (A[carA].first < result.first + result.second) result.first += result.second; 
		else result.first = A[carA].first; 
		result.second = A[carA].second;  
	}	
	else {
		result = fun(carA, carB-1, 0); 
		if (B[carB].first < result.first + result.second) result.first += result.second; 
		else result.first = B[carB].first; 
		result.second = B[carB].second;   
	}
	
	//cout << "Calling wait time with " << carA << " " << carB << " " << dir << endl; 
	pair<ll, ll> result2  = make_pair(INF, 0);  
	if (dir == 0 && carA > 0) {
		result2 = fun(carA-1, carB, 0);
		//cout << "Calling wait with mem[" << carA << ", " <<  carB << ", " << dir <<"]: "  << result2.first << " : " << result2.second << endl;
		result2 = same_direction(result2.first, carA, 'A', result2.second); //sollte sein... 	
	} else  if (carB > 0) {
		result2 = fun(carA, carB-1, 1); 
		//cout << "Calling wait with mem[" << carA << ", " <<  carB << ", " << dir <<"]: "  << result2.first << " : " << result2.second << endl;
		result2 = same_direction(result2.first, carB, 'B', result2.second); 
	}

	result = result.first + result.second < result2.first + result2.second  ? result: result2; 
	mem[carA][carB][dir] =  result; 
	cout << "mem[" << carA << ", " <<  carB << ", " << dir <<"] =  "  << result.first  << " : " << result.second<< endl;
	return result; 
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

		mem = vector<vector<vector<pair<ll,ll>>>> (A.size(), vector<vector<pair<ll, ll>>>(B.size() , vector<pair<ll,ll>>(2, make_pair(INF, 0))));
		if (A.size() > 1) mem[1][0][0] = A[1];
		if (B.size() > 1)  mem[0][1][1] = B[1];
		if (A.size() > 1) cout << "mem[1, 0, 0] =  "  << A[1].first  << " : " << A[1].second<< endl;
		if (B.size() > 1) cout << "mem[0, 1, 1] =  "  << B[1].first  << " : " << B[1].second<< endl;
		auto one = fun(A.size()-1, B.size()-1, 0);
		auto two = fun(A.size()-1, B.size()-1, 1); 
		

		cout << "Case #" <<  g+1 << ": " << min(one.first + one.second, two.first + two.second) << endl; 
	}


}