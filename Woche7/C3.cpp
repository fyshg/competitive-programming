#include <bits/stdc++.h>
using namespace std; 


vector<float> results; 
int dominant; 
vector<short int> basecase; 
vector<short int> sorted; 
int maxi; 
int n; 
map<vector<short int>, double> mem; 
int counter = 0; 

// array<array<array<array<array<float, 50>,50>,50>,50>,50> test;  
//auto test = new float[50][50][50][50][50]();

float memfind( vector<short int> dist) {
	if (!mem.count(dist)) return 0.0; 
	return mem[dist]; 
}

bool reachable(vector<short int> dist, int bucket ) {
	auto copy = basecase; 
	short int elem = basecase[bucket];
	copy.erase(copy.begin() + bucket); 
	sort(copy.begin(), copy.end(), [](auto a, auto b) {
		return a < b; 
	}); 
	copy.push_back(elem);
	for(int i = 0; i < copy.size(); i++) {
		if (copy[i] > dist[i]) return false; 
	}
	return true; 

}
void rec(vector<short int> dist, int n) { 
	float p = 0; 
	for (int i = 0; i < dist.size(); i++) {
		vector<short int> copy = dist; 
		copy[i]--; 
		p += ((float) (dist[i]-1) / (float) (n-1)) * memfind(copy); 
	} 
	mem[dist] =  p; 
	return; 
}
int fak(int i ) {
	if ( i <= 1) return 1; 
	return i * fak(i-1); 
}
double occurrence(vector<short int> dist,int bucket) {

	auto copy = dist; 
	copy.erase(copy.begin() + copy.size() -1); 
	

	auto mini = basecase; 
	mini.erase(mini.begin() + bucket); 

	if ( *(min_element(copy.begin(), copy.end())) > *(max_element(mini.begin(), mini.end())) ) return fak(copy.size()); 

	sort(mini.begin(), mini.end(), [](auto a, auto b ) {
		return a < b; 
	});
	double possibilities = 0; 

	bool eq = false; 
	for (int i = 0; i < mini.size(); i++) {
		if (mini[i] == copy[i]) eq = true; 
		else {
			eq = false; 
			break; 
		}
	}
	if(eq ) return 1;

	vector<float> adjusted;
	for(int i = 1; i < copy.size()+1; i++) {
		adjusted.push_back( copy[i]+  ( copy[i] > mini[i] ? (((double) i) * 0.1) : 0.0)); 
	}

	 do {
	 	//cout << " ad: ";
         	//for(auto a: adjusted) cout << a << " ";
         	//	cout << endl;
	 	
         for (int i = 0; i < copy.size(); i++) {

         	
         	if (adjusted[i] < mini[i]) break; 
         	else if (i == copy.size() - 1 && adjusted[i] >= mini[i]) possibilities++;
         }
   	 } while(next_permutation(adjusted.begin(), adjusted.end()));
   	 cout << "OCC: " << possibilities << endl;
	return possibilities; 
}

void backtrack(vector<short int> dist, short int balls, int boxes, int spendballs, int totalballs) {
	//cout << dist[1] << " " << balls << " " << dist[0] << endl;
	if (boxes == 1 && dist[1] >= balls + dist[0]) {
		dist[0]+= balls;
		spendballs += balls;  
		
		rec(dist, spendballs);
		

		if (totalballs == maxi - dominant) {
			for (int bucket = 0; bucket < n; bucket++){
				if (reachable(dist, bucket)) {
					for(auto a : dist) cout << a << " "; 
					cout << endl;
					
					// Wie viele Möglichkeiten, die Konfiguration am Bucket ist . .. ? 
					short int maxelem = *(max_element(dist.begin(), dist.end())); 
					int count = 0; 
					for (int i = 0; i < dist.size(); i++) {
						if (dist[i] == maxelem) count++; 
					}
					cout << " bucket " << bucket << "gets added : ";
					cout << memfind(dist) * ((double) 1 / (double) count) << endl;
					results[bucket]+= occurrence(dist,   bucket)* memfind(dist) * ((float) 1 / (float) count);

				}

			}
		}


		spendballs -= balls; 
		dist[0]-=balls; 
		return; 
	}


	if(boxes == 1) return; 
	//cout << boxes << " " << balls << " " << n << " distboxes " << dist[boxes] << endl;
	int maxii = balls;
	if ( boxes  <  n ) maxii = min((dist[boxes] - dist[boxes-1]), (int)balls); 
        //cout << " boxes: " << boxes <<  " maxi: " << maxii << endl;
	for (int i = 0; i <= maxii; i++) {
		dist[boxes-1] +=  i; 
		boxes--; 
		spendballs += i; 
		backtrack(dist, balls - i, boxes, spendballs, totalballs); 
		spendballs -= i; 
		boxes++; 
		dist[boxes-1] -= i; 
	}


	return; 

}

int main() {
	int t; 
	cin >> t; 
	for( int g = 0; g < t; g++) {

		maxi = 0; 
		cin >> n >> maxi; 
		basecase = vector<short int>(n); 

		dominant = 0; 
		mem = map<vector<short int>, double>(); 
		results = vector<float>(n,0);
		for(int i = 0; i < n; i++) {
			int var; 
			cin >> var; 
			basecase[i] = var; 
			dominant += var; 
		}
		
		sorted = basecase; 
		sort(sorted.begin(), sorted.end(), [] (auto a , auto b) {
			return  a < b; 
		});
		mem[sorted] = 1.0; 

		for (int i = dominant +1; i <=maxi; i++) {
			//cout << " balls: " << (i - dominant) << endl; 
			backtrack(sorted, i - dominant, n, dominant, i- dominant); 
		}
		
		

		cout << "Case #" << g+1 << ": " << endl;
		int i = 1; 
		for (auto a: results) {
			cout << fixed; 
			a = round(a * 10000.0) / 100.0;
			cout << "pub " << setprecision(2) << i << ": " << a << " %"<< endl;
			i++; 
		}

	}
	cout << counter << endl;
}

