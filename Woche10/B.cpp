#include <bits/stdc++.h>
using namespace std; 
typedef vector<int> vi; 
typedef pair<int, int> pii;
#define  FOR(i,a,n) for(int i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
#define  FORD(i,a,b)     for(int i=(b);i>=(a);i--)
typedef long long ll;  
const double eps = 1e-10;

typedef double coord;
struct pt{
	coord x,y;
	pt():x(0),y(0){};
	pt(coord _x,coord _y):x(_x),y(_y){};
	pt operator+(const pt& p) {
		return pt(x+p.x,y+p.y);
	}
	pt operator-(const pt& p) {
		return pt(this->x-p.x,this->y-p.y);
	}
	coord operator*(const pt& p) {
		return x*p.x+y*p.y;
	}
	bool operator==(const pt& p2) const {
		return this->x == p2.x && this->y == p2.y; 
	}	
	bool operator!=(const pt& p2) const {
		return !( *this == p2); 
	}
	bool operator<(const pt& p2) const {
		if(this->x < p2.x) return true;
		if(this->x > p2.x) return false;
		if(this->y < p2.y) return true;
		if(this->y > p2.y) return false;
		return false; 
	}

	pt operator*(double p) {
		return pt(this->x * p, this->y * p);
	}

	void print() const {
		cout << this->x << " " << this->y << endl;  
	}
};
// 1=ccw, 0=straight, -1=cw
int ccw(pt p0, pt p1, pt p2) {
	coord d1 =(p1.x-p0.x)*(p2.y-p0.y);
	coord d2 =(p2.x-p0.x)*(p1.y-p0.y);
	return (d1-d2>eps)-(d2-d1>eps);
}

vector<pt> convexhull(vector<pt> poly) {
	int n = poly.size();
	int k = 0;
	vector<pt> h(2*n);
	sort(poly.begin(), poly.end());
	FOR(i,0,n) {
		while (k > 1 && ccw(h[k-2], h[k-1], poly[i]) <= 0) k--;
		h[k++] = poly[i];
	}
	int t=k;
	FORD(i,0,n-1) {
		while (k>t && ccw(h[k-2], h[k-1], poly[i]) <= 0) k--;
		h[k++] = poly[i];
	}
	h.resize(k>1 ? k-1 : k);
	return h;
}

int main() {
	int t; 
	cin >> t; 
	FOR(g, 0,t) {
		int n; 
		cin >> n;
		vector<pt> points;  
		FOR(i,0,n) {
			double x,y,z,v; 
			cin >> x >> y >> z >> v; 
			points.push_back(pt(x,y)); 
		}

		vector<pt> result = convexhull(points); 
		sort(result.begin(), result.end());
		cout << "Case #" << g+1 << ": " << endl; 
		cout << result.size() << endl; 
		FORIT(i, result) i->print(); 
	}

}