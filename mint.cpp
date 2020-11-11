const int mod = 1e9 + 7; //998244353
const int sz = 5e5 + 1;

int fact[sz];
int inv_fact[sz];

int mul(int a, int b) {
    return (ll)a * b % mod;
}

int add(int a, int b) {
    int res = (ll)a + b;
    if (res < 0)
        res += mod;
    else if (res > mod)
        res -= mod;
    return res;
}

int bpow(int x, int p) {
    int res = 1;
    while (p) {
        if (p & 1)
            res = mul(res, x);

        p >>= 1;

        if (p)
            x = mul(x, x);
    }
    return res;
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