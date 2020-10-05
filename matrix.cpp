class matrix {
public:
	vector<vector<ll>> m;
	int row;
	int column;

	matrix() {}

	matrix(int x, int y) {
		m.resize(x, vector<ll>(y, 0));
		row = x;
		column = y;
	}

	vector<ll>& operator [](int i) {
		return m[i];
	}

	matrix operator * (matrix m2) {
		matrix res = matrix(row, m2.column);
		for (int i = 0; i < row; i++)
			for (int j = 0; j < m2.column; j++)
				for (int k = 0; k < column; k++) {
					res[i][j] += (m[i][k] * m2[k][j]) % mod;
					res[i][j] %= mod;
				}
		return res;
	}

	static matrix one(int x, int y) {
		matrix res = matrix(x, y);
		for (int i = 0; i < min(x, y); i++)
			res[i][i] = 1;
		return res;
	}
};

matrix bpow(matrix x, ll p) {
	if (p == 0)
		return matrix::one(x.row, x.column);
	if (p % 2)
		return bpow(x, p - 1) * x;
	else {
		matrix b = bpow(x, p / 2);
		return b * b;
	}
}