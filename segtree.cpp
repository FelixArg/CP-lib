// Simple sum + upd
template <class T>
struct SegTree {
	struct node {
		node* left;
		node* right;
		T val;
		node() {
			left = right = nullptr;
			val = 0;
		}
	};

	node* root;

	SegTree() {
		root = nullptr;
	}

	void build(int l, int r, vector<T>& a, node*& v) {
		if (!v)
			v = new node;
		if (l == r) {
			v->val = a[l];
			return;
		}
		int m = (l + r) / 2;
		build(l, m, a, v->left);
		build(m + 1, r, a, v->right);
		v->val = v->left->val + v->right->val;
	}

	void upd(int l, int r, int pos, T val, node*& v) {
		if (l == r) {
			v->val = val;
			return;
		}
		int m = (l + r) / 2;
		if (pos <= m)
			upd(l, m, pos, val, v->left);
		else
			upd(m + 1, r, pos, val, v->right);
		v->val = v->left->val + v->right->val;
	}

	T sum(int l, int r, int ql, int qr, node*& v) {
		if (ql > qr)
			return 0;
		if (ql == l && qr == r)
			return v->val;
		int m = (l + r) / 2;
		return sum(l, m, ql, min(qr, m), v->left) +
			sum(m + 1, r, max(ql, m + 1), qr, v->right);
	}
};

// Range sum + Range upate(add)
template <class T>
struct SegTree {
	struct node {
		node* left;
		node* right;
		T mx;
		T add;
		node() {
			left = right = nullptr;
			mx = 0;
			add = 0;
		}
	};

	node* root;

	SegTree() {
		root = nullptr;
	}

	void push(node*& v) {
		v->left->add += v->add;
		v->right->add += v->add;
		v->mx += v->add;
		v->add = 0;
	}

	void build(int l, int r, vector<T>& a, node*& v) {
		if (!v)
			v = new node;
		if (l == r) {
			v->mx = a[l];
			return;
		}
		int m = (l + r) / 2;
		build(l, m, a, v->left);
		build(m + 1, r, a, v->right);
		v->mx = max(v->left->mx, v->right->mx);
	}

	ll get_max(int l, int r, int ql, int qr, node*& v) {
		assert(v != nullptr);
		if (ql > qr)
			return 0;
		if (ql == l && qr == r)
			return v->mx + v->add;
		int m = (l + r) / 2;
		push(v);
		return max(get_max(l, m, ql, min(qr, m), v->left),
			get_max(m + 1, r, max(ql, m + 1), qr, v->right));
	}

	void upd(int l, int r, int ql, int qr, T val, node*& v) {
		assert(v != nullptr);
		if (ql > qr)
			return;
		if (ql == l && qr == r) {
			v->add += val;
			return;
		}
		int m = (l + r) / 2;
		push(v);
		upd(l, m, ql, min(m, qr), val, v->left);
		upd(m + 1, r, max(ql, m + 1), qr, val, v->right);
		v->mx = max(v->left->mx + v->left->add, v->right->mx + v->right->add);
	}
};

//Range update + min
template <class T>
struct SegTree {
	struct node {
		node* left;
		node* right;
		T mx;
		T add;
		node() {
			left = right = nullptr;
			mx = 1e18;
			add = 1e18;
		}
	};

	node* root;

	SegTree() {
		root = nullptr;
	}

	void push(node*& v) {
		v->left->add = min(v->left->add, v->add);
		v->right->add = min(v->right->add, v->add);
	}

	void build(int l, int r, vector<T>& a, node*& v) {
		if (!v)
			v = new node;
		if (l == r) {
			v->mx = a[l];
			return;
		}
		int m = (l + r) / 2;
		build(l, m, a, v->left);
		build(m + 1, r, a, v->right);
		v->mx = min(v->left->mx, v->right->mx);
	}

	ll get_min(int l, int r, int ql, int qr, node*& v) {
		assert(v != nullptr);
		if (ql > qr)
			return 1e18;
		if (ql == l && qr == r)
			return min(v->mx, v->add);
		int m = (l + r) / 2;
		push(v);
		return min(get_min(l, m, ql, min(qr, m), v->left),
			get_min(m + 1, r, max(ql, m + 1), qr, v->right));
	}

	void upd(int l, int r, int ql, int qr, T val, node*& v) {
		assert(v != nullptr);
		if (ql > qr)
			return;
		if (ql == l && qr == r) {
			v->add = min(v->add, val);
			return;
		}
		int m = (l + r) / 2;
		push(v);
		upd(l, m, ql, min(m, qr), val, v->left);
		upd(m + 1, r, max(ql, m + 1), qr, val, v->right);
		v->mx = min(min(v->left->mx, v->left->add), min(v->right->mx, v->right->add));
	}
};