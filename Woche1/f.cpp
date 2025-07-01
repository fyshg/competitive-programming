#include <map>
#include <string>
#include <iostream>
#include <cmath>

using namespace std; 

int main() {
	int N;
	cin >>N;
	string trash; 
	getline(cin, trash);
	
	for(int i = 0; i< N; i++){
		string tree; 
		getline(cin, tree); 
		int depth = 0; 
		bool parsenum = false; 
		string num="";
		map<double, int> occurences;
		int total = 0; 
		for(size_t j =0; j< tree.size(); ++j ){

			if (tree[j] != ',' && tree[j]!= '[' && tree[j]!= ']'){
				num+=tree[j];
				parsenum = true; 
			} else if (parsenum) {
				//ende der Zahl 
				double number = stod(num);
				occurences[(number * pow(2,depth))]++;
				parsenum = false; 
				num="";
				total++;

			}

			if(tree[j] == '['){
				depth++;
			} else if (tree[j] == ']') {
				depth--;
			}
			
			
		}

		int max = 0;
		for (auto& a: occurences) {
			if (a.second > max) max = a.second;

		}

		cout << "Case #" << i+1 << ": "<< total - max<< endl;
	}




}