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
 	double distance(const pt& p2) const {
 		return sqrt(pow(this->x - p2.x, 2) + pow(this->y - p2.y, 2)); 
 	}
 	pt operator*(double p) {
 		return pt(this->x * p, this->y * p);
 	}

};

struct circle{
	pt p; 
	double radius; 

	circle():p(0,0), radius(0) {};
	circle(pt t, double r) : p(t), radius(r) {};

	pair<pt, pt> intersection (circle& other) const {
		double R = this->p.distance(other.p); 
		pt pmid = (other.p + this->p)*0.5  + (other.p - this->p) * ( (pow(this->radius, 2) - pow(other.radius, 2)) / (2* pow(R,2)) ) ;
		pt p2 = pt(other.p.y - this->p.y, this->p.x - other.p.x )  *  (0.5*sqrt( (2 * ((pow(this->radius, 2) + pow(other.radius, 2))/(pow(R,2)))) - ((pow( pow(this->radius, 2) - pow(other.radius, 2), 2)) / (pow(R,4))) - 1)) ; 
		return make_pair(pmid +p2, pmid - p2);
	}

	pt intersection (pt p, pt v) {
		
	}
};

int main() {

	circle c1( pt(0,0), 2); 
	circle c2( pt(10,3), 20); 
	cout << c1.intersection(c2).first.x << " " << c1.intersection(c2).first.y << endl;
	cout << c1.intersection(c2).second.x << " " << c1.intersection(c2).second.y << endl;

	int n, p, x, y, r; 
	while ( cin >> n >> p >> x >> y >> r ) {
		circle platform(pt(0,0), p); 
		circle inner(pt(1,1))
	}
}

