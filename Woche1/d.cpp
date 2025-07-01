#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std; 

int main() {
	int N; 
	cin >> N; 
	for( int i = 0; i < N; i++ ){
		int n; 
		cin >> n; 

		vector<int> lastTiles; 

		int ring = 0;   //start in ring zero 
		int elements = 0; 
		bool found = false; 
		int result;
		map<int, int> occurences; 
		occurences[0] = 1000000;
		while (!found) {
			int size = ring == 0 ? 1 : ring * 6; 
			vector<int> thisTiles(size);
			/*
			cout << "lastTiles: " ; 
			for (auto zz : lastTiles ){
				cout << zz << ", " ; 
			}
			cout << endl; 
			*/
			for (int elem = 0; elem < size; elem++){

				


				//calculate values of neighbours
				vector<int> neighbours(0); 

				if (elem!= 0){  
					neighbours.push_back(thisTiles[elem-1]);
				}

				//Nachbarn im inneren Ring. Entweder 1 oder 2 
				

				if (ring == 1 ) {
					neighbours.push_back(lastTiles[0]);
				} else if (ring != 0) {

					if (  elem % ring == ring -1 )  { // ecke müsste passen 
						int cornerNo = elem / ring ; 
						neighbours.push_back(lastTiles[ ((ring -1) * cornerNo)  + (ring - 2) ]);
					} else {  //Fall 2 Nachbarn im Inneren Ring

						int withoutCornerIndex = elem - (elem / ring); 
						neighbours.push_back(lastTiles[withoutCornerIndex]);
						neighbours.push_back(lastTiles[(withoutCornerIndex -1 + lastTiles.size()) % lastTiles.size()]); // dumm anscheinend

					}


				} 


				if (elem == size -1 && ring != 0) {   //Spezialfall letztes Tile im ring
					neighbours.push_back(thisTiles[0]);
				}
				/*
				cout << " element: " << elem << endl; 
				


				cout << endl ;
				cout << " neighbours: "; 
				for (auto zz : neighbours) {
					cout << zz << ", " ;
				}
				cout << endl; 
				*/
				int value; 

				int candidate = 0; 
				for (int j = 1; j < 6; j++) {
					if (find(neighbours.begin(), neighbours.end(), j) == neighbours.end() && occurences[j] < occurences[candidate] ) {
						candidate = j; 
					}

				}

				value = candidate; 
				
				//if tile is searched tile break and output found = true; 
				elements++; 
				occurences[value]++; 
				thisTiles[elem]= value; 

				//cout << " value: " << value << " elements: " << elements << " ring size " <<  thisTiles.size() << endl; 
				//cout << "  ### value ### " << value << endl; 
 				if (elements == n) {
					result = value; 
					found = true; 
					break; 
				}




			}
			ring++;
			lastTiles = thisTiles; 



		}



		cout << "Case #" <<i+1 << ": " <<  result << endl; 




	} 
}