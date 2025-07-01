// Worst case 
//k * log n
// solution implement range segment tree with range updating

#include<iostream>
#include<vector>
typedef long long ll;
using namespace std; 


struct segment_tree {
	segment_tree *left, *right;
	int from, to;
	ll value, upda;
	segment_tree(int from, int to)
	: left(NULL), right(NULL),from(from), to(to), value(0), upda(0) { }
};
segment_tree* build(const vector<ll> &arr, int l, int r) {
	if (l > r) return NULL;
	segment_tree *res = new segment_tree(l, r);
	if (l == r) {
		res->value = arr[l];
	} else {
		int m = (l + r) / 2;
		res->left = build(arr, l, m);
		res->right = build(arr, m + 1, r);
		if (res->left != NULL) res->value += res->left->value;
		if (res->right != NULL) res->value += res->right->value;
	}
	return res;
}


// propagate update values downwards
ll query(segment_tree *tree, int i, ll update) {
	
	if (tree == NULL) return 0;
	update += tree->upda;
	if (i == tree->from && i== tree->to ) {
		return tree->value + update;
		
	}
	if (tree->to < i) return 0;
	if (i < tree->from) return 0;

	return query(tree->left, i, update) + query(tree->right, i, update);
}



ll update(segment_tree *tree, int l, int r, ll val) {
	
	if (tree->to < l || tree->from > r ) return 0; 

	if (l <= tree->from && tree->to <= r) {
		tree->upda = tree->upda + val;
		return 0;  
	}
 
	if ((tree->from <= r && tree->to >r) || (tree->to >= l && tree-> from < l)){ ; 
		update(tree->left, l, r, val); 
		update(tree->right, l, r, val); 
		return 0; 
	}

	return 0;
}



int main() {
	int t; 
	cin >> t; 
	for (int j = 0; j < t; j++){

		ll n, k; 
		cin >> n >> k; 
		vector<ll> bowls(n, 0);
		segment_tree* tree = build(bowls, 0, n);

		ll result = 0; 
		for (int i = 0; i < k; i++){

			
			char a; 
			cin >> a;
			if ( a == 'i') {
				ll l, r, v; 
				cin >> l >> r >> v; 
				update(tree, l-1, r-1, v);
			} else {
				int v; 
				cin >> v; 
				result = (result + query(tree, v-1, 0)) % 1000000007 ; 
			}

		}
		cout << "Case #" << j+1 <<": "<< result << endl;

	}
}