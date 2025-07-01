

#include <bits/stdc++.h>
using namespace std; 
typedef vector<int> vi; 
typedef pair<int, int> pii;
#define  FOR(i,a,n) for(int i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
typedef long long ll;  
const long double EPS = 1e-17;
const long long factor = 1e8; 

typedef long double coord;
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

	pt operator*(long double p) {
		return pt(this->x * p, this->y * p);
	}

	void print() const {
		cout << this->x << " : " << this->y;  
	}

};



long double twoarea(vector<pt>& poly) {
	int n = poly.size();
	coord ret = 0;
	FOR(i,0,n)
	ret += (poly[(i+1)%n].x-poly[i].x)*
	(poly[(i+1)%n].y+poly[i].y);
	return abs(ret);
}

long double test(vector<pt>& poly, long double t) {
	vector<pt> newpoly; 
	long double s = (1/t);
	int n = poly.size(); 
	if (t = 2) {
		FOR(i,0,n){
			newpoly.push_back( poly[i] + ( poly[(i+1)%n] - poly[i] ) * s); 
		}
	} else {
		FOR(i,0,n) {
			newpoly.push_back( poly[i] + ( poly[(i+1)%n] - poly[i] ) * s); 
			newpoly.push_back( poly[(i+1)%n] + ( poly[i] -  poly[(i+1)%n] ) * s); 
		}
	}
	return twoarea(newpoly)*factor  ; 
}

int main() {
	long double a; 
	int n; 
	while ( cin >> a >> n ) {
		vector<pt> poly; 
		FOR(i,0,n) {
			long double x,y; 
			cin >> x >> y; 
			poly.push_back(pt(x,y)); 
		}	

		long double area =  (twoarea(poly) * (a* factor)) ; 
		long double lo = 2.0; 
		long double hi = 1e10; 
		while (lo + 1 < hi) {
			long long mid = lo + (hi - lo) / 2;
			cout << "mid: " << mid << " area: " << area << " f: " << test(poly, mid) << endl; 
 			if (test(poly, mid)  > area) {
				hi = mid;
			} else {
				lo = mid;
			}

		}
		cout << std::setprecision(1000) << lo << endl; 
	}
}