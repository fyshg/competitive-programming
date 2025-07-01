#include <iostream>
#include <vector>

using namespace std;
typedef long long ll; 




struct segment_tree {
	segment_tree *left, *right;
	int from, to, value;
	bool isZero; 
	segment_tree(int from, int to)
	: from(from), to(to), left(NULL), right(NULL), value(0), isZero(false) { }
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

ll catchemall(segment_tree *tree, int l, int r, bool z) {
	//cout << " catch called with tree->from: " << tree->from << " r: " << tree->to << " and zeroing " << z << endl;
	if (tree == NULL) return 0;

	


	if (z){
		tree->value = 0; 
		tree->isZero = z; 
	}

	if (tree->to < l) return 0;
	if (r < tree->from) return 0;



	if (l <= tree->from && tree->to <= r) { 
		//cout << " set range l: " << tree->from << " r: " << tree->to << " to zero "<< endl;
		tree->isZero = true; 
		ll copy = tree->value; 
		tree->value = 0; 
		return copy;
	}
	

	bool zero = tree->isZero;
	tree->isZero = false;  
	ll ret = catchemall(tree->left, l, r, zero ) + catchemall(tree->right, l, r, zero);
	tree->value -= ret;
	return ret; 
}

ll update(segment_tree *tree, int i, int val, bool z) { //call with 1 or -1; 
	if (tree == NULL) return 0;

	if (z){
		tree->value = 0; 
		tree->isZero = true; 
	}


	if (tree->to < i) return tree->value;
	if (i < tree->from) return tree->value;

	if (tree->from == tree->to && tree->from == i) {
		if (tree->value + val >= 0) 	tree->value += val;
		tree->isZero = false; 
	} else {
		bool zero = tree->isZero; 
		tree->isZero = false;
		tree->value = update(tree->left, i, val, zero) + update(tree->right, i, val, zero);
	}
	return tree->value;
}
ll query(segment_tree *tree, int l, int r, bool z) {
	//cout << " query called with: " << tree->from << " " << tree->to << " update:" << upd << " tree value: " << tree->value << endl; 
	if (tree == NULL) return 0;

	if (z){
		tree->value = 0; 
		tree->isZero = z; 
	}

	if (tree->to < l) return 0;
	if (r < tree->from) return 0;
	

	if (l <= tree->from && tree->to <= r) return tree->value;
	

	
	bool zero = tree->isZero;
	tree->isZero =  false;
	

	return query(tree->left, l, r, zero) + query(tree->right, l, r, zero);
}


int main(){
	int t; 
	cin >> t; 
	for (int j = 0; j < t; j++) {
		ll n,k; 
		cin >> n >> k; 
		vector<ll> bowls(n,0);
		segment_tree* tree = build(bowls, 0, n-1); 
		ll result = 0; 
		for (int i = 0; i < k; i++) {
			char O; 
			cin >> O;
			if (O == 's') {
				ll a; 
				cin >> a; 
				update(tree, a-1, 1, false); 
			} else if ( O == 'd') {
				ll a; 
				cin >> a; 
				update(tree, a-1, -1, false);

			} else if (O == 'c') {
				int l, r; 
				cin >> l >> r; 
				result += catchemall(tree, l-1, r-1, false);

			}

			/*
			for( int h = 0; h < n; h++) {
				cout << query(tree, h, h, false) << " " ;
			}
			cout << endl;
			*/
		}
		delete tree; 
		cout << "Case #" <<j+1 << ": " << result << endl;
	}
}