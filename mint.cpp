const int mod = 1e9 + 7; //998244353
const int sz = 5e5 + 1;

int fact[sz];
int inv_fact[sz];

int add(int a, int b) {
	return ((ll)a + b + mod) % mod;
}

int mul(int a, int b) {
	return ((ll)a * b) % mod;
}

int bpow(int x, int p) {
	if (p == 0)
		return 1;
	if (p % 2)
		return mul(x, bpow(x, p - 1));
	else {
		int b = bpow(x, p / 2);
		return mul(b, b);
	}
}

int inv(int x) {
	return bpow(x, mod - 2);
}

void calc_fact() {
	fact[0] = inv_fact[0] = 1;
	for (int i = 1; i < sz; i++) {
		fact[i] = mul(fact[i - 1], i);
		inv_fact[i] = inv(fact[i]);
	}
}

int cnk(int n, int k) {
	if (k > n)
		return 0;
	return mul(fact[n], mul(inv_fact[k], inv_fact[n - k]));
}