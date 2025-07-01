#include <iostream>
#include <vector>
typedef long long ll;
using namespace std; 

struct segment_tree {
	segment_tree *left, *right;
	int from, to, value;
	segment_tree(int from, int to)
	: from(from), to(to), left(NULL), right(NULL), value(1) { }
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
		if (res->left != NULL) res->value *= res->left->value;
		if (res->right != NULL) res->value *= res->right->value;
	}
	return res;
}
int query(segment_tree *tree, int l, int r) {
	if (tree == NULL) return 1;
	if (l <= tree->from && tree->to <= r) return tree->value;
	if (tree->to < l) return 1;
	if (r < tree->from) return 1;
	return query(tree->left, l, r) * query(tree->right, l, r);
}
int update(segment_tree *tree, int i, int val) {
	if (tree == NULL) return 1;
	if (tree->to < i) return tree->value;
	if (i < tree->from) return tree->value;
	if (tree->from == tree->to && tree->from == i) {
		tree->value = val;
	} else {
		tree->value = update(tree->left, i, val) * update(tree->right, i, val);
	}
	return tree->value;
}



int main(){
	ll N, K;
	while (cin >> N >> K){


		vector<ll> bowls(N,0);


		for(int i = 0; i<N; i++){
			ll a; 
			cin >> a; 
			bowls[i] = (a > 0 ? 1 : ( a < 0 ? -1 : 0  )); 

		}

		segment_tree* tree = build(bowls, 0, N);

		for (int i = 0; i < K; i++){
			char c;
			ll a, b; 
			cin >> c >> a >> b;
			if (c == 'C') {
				update(tree, a - 1,  (b > 0 ? 1 : ( b < 0 ? -1 : 0  )));
			} else {
				ll result = query(tree, a-1,b-1);
				cout << ( result > 0 ? "+" : (result < 0 ?  "-" : "0"));
			}

		}
		cout << endl;

	}
}