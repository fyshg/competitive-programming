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
		return pt(x-p.x,y-p.y);
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

};

double len(pt p) { return sqrt(double(p*p)); }

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

// 0=outside, 1=edge, 2=inside
int isInside(pt p, vector<pt>& poly) {
	int numAbove = 0;
	int numIntersects = 0;
	FOR(i,0,poly.size()) {
		pt p0 = poly[i];
		pt p1 = poly[(i+1)%poly.size()];
		if(isPointOnSegment(p,p0,p1)) return 1;
		if(p0.y-p.y<=eps && p1.y-p.y<=eps) continue;
		if(p0.y-p.y>eps && p1.y-p.y>eps) continue;
		pt d=p-p0;
		pt d1=p1-p0;
		if(d1.y < 0) d1.y*=-1, d.y*=-1;
		if(d.y*d1.x > d.x*d1.y) {
			if((p0.y-p.y) * (p1.y-p.y) < 0) numIntersects++;
			else numAbove++;
		}
	}
	return (((numIntersects+(numAbove%2))%2) != 0 ? 2 : 0);
}

int main() {
	int t; 
	cin >> t; 
	FOR(g,0,t) {
		int xi, yi, n; 
		cin >> xi >> yi >> n; 
		pt impact(xi,yi); 

		map<pt, pt> order; 
		FOR(i,0,n) {
			int x1, x2, y1, y2; 
			cin >> x1 >> y1 >> x2 >> y2; 
			order[pt(x1,y1)] = pt(x2,y2); 
		}
		pt start = order.begin()->first;
		vector<pt> border; 
		border.push_back(start); 
		pt current = order[start]; 
		while (current != start) border.push_back(current), current = order[current]; 
		//border.push_back(start);
		//for (auto a: border)  cout << a.x << " : " << a.y << endl;
		cout << "Case #" << g+1 << ": "<< (isInside(impact, border) == 2 ? "jackpot" : "too bad") << endl;

	}
}