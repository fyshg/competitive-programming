#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std; 
typedef long long ll; 

int main() {
	ll N; 

	cin >> N; 

	vector<pair<string, double>> firsts; 
	vector<pair<string, double>> seconds; 

	for (int i = 0; i< N; i++){
		string guy; 
		double first, second; 
		cin >> guy >> first >> second;
		firsts.push_back(pair(guy, first)); 
		seconds.push_back(pair(guy, second)); 
	}


	sort(firsts.begin(), firsts.end(), [] (const pair<string, double> &l, const pair<string, double> &r){
			return l.second < r.second; 
		
	});
	sort(seconds.begin(), seconds.end(), [] (const pair<string, double> &l, const pair<string, double> &r){
			return l.second < r.second; 
		
	});

	double result = 1000; 
	vector<string> names; 
	for (int i = 0; i < 4; i++) {
		double run = 0; 
		vector<string> tnames; 

		string runner = firsts[i].first;
		tnames.push_back(runner);
		run += firsts[i].second; 

		//choose 3 best second runners 
		int j = 0; 
		int offset = 0; 
		while ( j < 3 ) {
			//cout << " 2nd runner: " << seconds[i+j].first  << " first runner: "  << seconds[i+j].first << endl; 
			if (seconds[offset+j].first == runner){
				offset += 1; 
			} else {
				tnames.push_back(seconds[offset+j].first);
				run += seconds[offset+j].second;
				j++;
			}

		}

		if (run < result ) {
			result = run; 
			names = tnames; 
		}

	}

	cout << result << endl;

	for (auto name : names) {
		cout << name << endl; 
	}
}