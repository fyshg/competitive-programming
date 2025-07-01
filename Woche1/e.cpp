#include <map>
#include <string>
#include <iostream>
#include <cmath>

using namespace std; 

int main() {
	int N;
	cin >>N;
	
	for(int i = 0; i< N; i++){
		string tree; 
		cin >> tree; 
		int depth = 0; 
		bool parsenum = false; 
		string num="";
		map<double, int> occurences;
		for(size_t j =0; j< tree.size(); ++j ){

			if(tree[j] == '['){
				depth +=1;
			} else if (tree[j] == ']') {
				depth--;
			}
			
			if (tree[j] != ',' && tree[j]!= '[' && tree[j]!= ']'){
				num+=tree[j];
				num = true; 
			} else if (parsenum) {
				//ende der Zahl 
				double number = stod(num);
				occurences[(number * pow(2,depth))]++;
				parsenum = false; 
				num="";

			}
		}
	}




}