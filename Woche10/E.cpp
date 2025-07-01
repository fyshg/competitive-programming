#include <bits/stdc++.h>
using namespace std; 
typedef vector<int> vi; 
typedef pair<int, int> pii;
#define  FOR(i,a,n) for(int i = a; i < n; ++i )
#define  FORIT(i,iterable) for(auto i = iterable.begin(); i != iterable.end(); i++)
#define  FORD(i,a,b)     for(int i=(b);i>=(a);i--)
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
		cout << this->x << " " << this->y << endl;  
	}
	double dist(const pt& p2) {
		return sqrt((pow(p2.x - x, 2) + pow(p2.y - y , 2)  )); 
	}
};

vector<pt> quadi;
vector<pt> triangle; 
bool ret = false; 

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

bool isComplete(){
	vector<pt> quad = quadi; 
	pt p1 = quad.back(); quad.pop_back(); 
	//find first line segment. 
	double dist1 = p1.dist(quad[2]); 
	double dist2 = p1.dist(quad[1]); 
	pt p2; 
	if (dist1 < dist2){ p2 = quad.back(); quad.pop_back(); }
	else { 
		p2 = quad[1];
		quad.erase(quad.begin()+1); 
	}  

	double dist3 = p2.dist(quad[1]); 
	double dist4 = p2.dist(quad[0]); 
	pt p3; 
	if (dist3 < dist4){ p3 = quad.back(); quad.pop_back();} 
	else {
		p3 = quad[0];
		quad.erase(quad.begin()); 
	}
	pt p4 = quad.back();  quad.pop_back(); 
	//dist
	if( abs(p1.dist(p2) - p3.dist(p4)) > eps || abs(p2.dist(p3) - p4.dist(p1)) > eps) return false; 
	//p1.print(); p2.print(); p3.print(); p4.print(); 
	if(abs((p2-p1) * (p3-p2)) > eps || abs((p3-p2) * (p4-p3)) > eps || abs((p4-p3) * (p1 - p4)) > eps || abs((p1-p4)*(p2-p1)) > eps) return false; 
	//orthogonal .... 


	vector<pt> result = {p1,p2,p3,p4}; 
	bool ans = true; 
	FOR(i,0,4) FOR(j,0,3) ans = ans && (0 == isSegmentIntersect(result[i], result[(i+1)%4], triangle[j], triangle[(j+1)%3])); 

	//check if one form contains the other
	if (isInside(triangle[0], result) != 0) return false; 
	if (isInside(result[0], triangle) != 0)return false; 


	if(ans) {
		quadi = result; 
		return true; 
	}	
	return false; 



}

void backtrack(int i, const vector<pt>& points){
	
	if(quadi.size() > 4 || triangle.size() > 3 ) return; 

	if(quadi.size() == 4 && triangle.size() == 3) {
		//check intersection and set stuff
		ret = isComplete(); 
		//cout << ret << endl;
		return; 
	}

	if( i < 0) return; 

	quadi.push_back(points[i]); 
	backtrack(i-1, points); 
	if(ret) return; 
	quadi.pop_back(); 

	triangle.push_back(points[i]); 
	backtrack(i-1, points); 
	if(ret) return; 
	triangle.pop_back(); 

	backtrack(i-1, points); 

	return; 

}


int main() {
	int t; 
	cin >> t; 
	FOR(g,0,t){
		int n; 
		cin >> n; 
		vector<pt> points; 
		quadi = vector<pt>(); 
		triangle = vector<pt>(); 
		ret = false; 
		FOR(i,0,n) {
			double x, y; 
			cin >> x >> y; 
			points.push_back(pt(x,y)); 
		}
		sort(points.begin(), points.end()); 
		backtrack(n-1, points); 

		cout << "Case #" << g+1 << ": " << (ret ? "possible" : "impossible") << endl; 
		FORIT(i, quadi) i->print(); 
		FORIT(i, triangle) i->print(); 

	}
}