#include <bits/stdc++.h>
typedef long long ll; 
using namespace std; 

struct carpet {
	int height, width, square; 
};
int floor [1000][1000] = {}; 
int H, W;  
vector<carpet> pile; 


void placecarpet(int x, int  y, carpet carp, int inc) {
	for (int i = x; i < carp.width; i++) {
		for (int j = y; j < carp.height; j++) {
			floor[i][j] += inc; 
		}
	}

}

void is_valid() {
	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++) {
			if (floor[i][j] > 1) return false; 
		}
	}
	return true; 
}

bool generate() {

	if (!is_valid()) return false; 

	if (is_valid() && pile.empty()) return true; 

	carp c = pile.pop_back(); 
	for (int x = 0; x < W - carp.width; x++){
		for (int y = 0; y < H - carp.height) {
			placecarpet(x,y,carpet, 1); 
			bool b = placecarpet(); 
			if (b) return true;
			placecarpet(x,y,carpet, -1); 

		}
	}
	pile.push_back(carp); 
	return false; 
}


int main() {
	cin >> H >> w; 
	int c; 
	cin >> c; 
	int totalground = 0;
	for (int i = 0; i < c; i++) {
		int h, w, c; 
		cin >> c >> w >> h; 
		int s = w *h; 
		for (int j = 0; j < c; j++ ) {
			carpet car = {}; 
			car.height = h; 
			car.width = w; 
			car.square = s; 
			stack.push_back(car);
			totalground += s; 
		}
		sort(pile.begin(),pile.end(), [] (const carpet c1, const carpet c2){
			return c2.square < c1.square; 
		});

		if (totalground != H*W) {
			cout << "no" << endl; 
		} else {
			cout << (generate() ? "yes" : "no") << endl;
		}
	}

}