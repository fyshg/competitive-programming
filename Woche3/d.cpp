#include <iostream>
#include <vector>
using namespace std; 
typedef long long ll; 

struct segment_tree {
	segment_tree *left, *right;
	int from, to;
	ll value, update;
	segment_tree(int from, int to)
	: from(from), to(to), left(NULL), right(NULL), value(0), update(0) { }
};
segment_tree* build(const vector<ll> &arr, int l, int r) {
	if (l > r) return NULL;
	segment_tree *res = new segment_tree(l, r);
	if (l == r) {; 
		res->value = arr[l];
	} else {
		int m = (l + r) / 2;
		res->left = build(arr, l, m);
		res->right = build(arr, m + 1, r);
		if (res->left != NULL) res->value = res->left->value;
		if (res->right != NULL) res->value = max(res->right->value, res->value);
	}
	return res;
}


//gets maximum of a range and distributes changes
ll query(segment_tree *tree, int l, int r, ll upd) {
	//cout << " query called with: " << tree->from << " " << tree->to << " update:" << upd << " tree value: " << tree->value << endl; 
	if (tree == NULL) return 0;

	if (upd > 0) {
		tree->update = upd;
		tree->value = upd; 
	}

	if (tree->to < l) return 0;
	if (r < tree->from) return 0;
	

	if (l <= tree->from && tree->to <= r) return max(tree->value,  tree->update);
	

	tree->value = max(tree->update, tree->value); 
	ll up = tree->update; 
	tree->update = 0;

	return max(query(tree->left, l, r, up), query(tree->right, l, r, up));
}
//update range to val; 
ll update(segment_tree *tree, int l, int r, ll val, ll upd) {

	if (tree == NULL) return 0; 

	if (upd > 0){ 
		tree->update = upd;  
		tree->value = upd; 
	}

	if (tree->to < l || tree->from > r ) return tree->value; 
	
	

	if (l <= tree->from && tree->to <= r) {
		//cout << "setting value of range " << tree->from << " " << tree->to << "  to : " << val << endl; 
		tree->update = val;
		tree->value = val; 
		return val;  
	}
 

	if ((tree->from <= r && tree->to >r) || (tree->to >= l && tree-> from < l)){ 
	
		ll up = tree->update; 
		tree->update = 0; 

		tree->value = max(update(tree->left, l, r, val, up), update(tree->right, l, r, val, up)); 
		return tree->value; 
	}

	return 0;
}



int main() {
	int t; 
	cin >> t; 
	for (int j = 0; j < t; ++j){
		ll n, k; 
		cin >> n >> k; 
		vector<ll> bowls(n, 0);
		segment_tree* tree = build(bowls,0,n-1); 
		cout << "Case #" << j+1 << ":"; 
		for (int i = 0; i < k ; i++) {
			ll w, h, p; 
			cin >> w >> h >> p; 

			ll max = query(tree, p, p+w -1, 0);
			//cout << " max is " <<  max << endl; 
			update(tree, p, p+w - 1, max + h, 0);

			/*
			for ( h = 0; h < n; h++) {
				cout << " " << query(tree, h, h, 0); 
			}
			cout << endl; 
			*/

			cout << (i == k ? "" : " ") << query(tree, 0, n -1, 0) ;
		}
		cout << endl;
	}
}