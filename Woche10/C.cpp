#include <bits/stdc++.h>
using namespace std; 
typedef vector<int> vi; 
typedef pair<int, int> pii;
#define  FOR(i,a,n) for(int i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
typedef long long ll;  
const double eps = 1e-7;

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
 		cout << this->x << " : " << this->y;  
 	}

};
// 1=ccw, 0=straight, -1=cw
int ccw(pt p0, pt p1, pt p2) {
coord d1 =(p1.x-p0.x)*(p2.y-p0.y);
coord d2 =(p2.x-p0.x)*(p1.y-p0.y);
return (d1-d2>eps)-(d2-d1>eps);
}

// 0 = no, 1= on-end-point, 2=strict
int isPointOnSegment(pt p, pt a0, pt a1) {
if(ccw(a0,a1,p)) return 0;
coord cx = (p.x-a0.x)*(p.x-a1.x);
coord cy = (p.y-a0.y)*(p.y-a1.y);
if(cx > eps || cy > eps) return 0;
if(cx < -eps || cy < -eps) return 2;
return 1;
}



// 0 = none, 1=strict, 2=on-end-point
int isSegmentIntersect(pt a0, pt a1, pt b0, pt b1) {
	int c1=ccw(a0,a1,b0);
	int c2=ccw(a0,a1,b1);
	int c3=ccw(b0,b1,a0);
	int c4=ccw(b0,b1,a1);
	if(c1*c2>0 || c3*c4>0) return 0;
	if(!c1 && !c2 && !c3 && !c4) {
		c1=isPointOnSegment(a0,b0,b1);
		c2=isPointOnSegment(a1,b0,b1);
		c3=isPointOnSegment(b0,a0,a1);
		c4=isPointOnSegment(b1,a0,a1);
		if(c1 && c2 && c3 && c4)
			return 1+(a0.x!=a1.x || a0.y!=a1.y);
		if (c1 + c2 + c3 + c4 == 0) return 0;
		return 3 - max({c1,c2,c3,c4});
	}
	return 1+(!c1 || !c2 || !c3 || !c4);
}



int main() {
	int t; 
	cin >> t; 
	FOR(g,0,t) {
		int n; 
		cin >> n; 
		vector<pt> poly; 
		FOR(i,0,n) {
			double x, y; 
			cin >> x >> y; 
			poly.push_back(pt(x,y)); 
		}
		int total = 0; 
		FOR(i,0,n){
			pair<pt,pt> segment = make_pair( poly[i] -  ((poly[(i+1)%n] - poly[i]) *1000), poly[i] + ((poly[(i+1)%n] - poly[i]) * 1000));  
			bool can_stand = true; 
			FOR(j,0,n) {
				pair<pt, pt> segment2 = make_pair(poly[j], poly[(j+1) %n]); 
				if (i == j) continue;  	
				else if ( (i+1) % n == j ) { //benachbarte Kanten. .. 
					if ( ccw(poly[i], poly[(i+1)%n], poly[(i+2)%n])  == 0 ) can_stand = false; 
				} else if ((i-1+n) %n == j ) {
					if ( ccw(poly[(i-1+ n)%n], poly[i], poly[(i+1)%n])  == 0 ) can_stand = false; 
				}else if (isSegmentIntersect(segment.first, segment.second, segment2.first, segment2.second) || isPointOnSegment(segment.first, segment.second, poly[j])) { 
					can_stand = false; 
				}
			}

			total += can_stand; 

		}
		cout << "Case #" << g+1 << ": " << total << endl; 

	}
}