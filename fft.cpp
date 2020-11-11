const int mod = 998244353;
const int root = 646;
const int root_1 = 208611436;
const int root_pw = 1 << 20;

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

void fft(vector<int>& a, bool invert) {
    int n = (int)a.size();

    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = int(wlen * 1ll * wlen % mod);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; ++j) {
                int u = a[i + j], v = int(a[i + j + len / 2] * 1ll * w % mod);
                a[i + j] = u + v < mod ? u + v : u + v - mod;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
                w = int(w * 1ll * wlen % mod);
            }
        }
    }
    if (invert) {
        int nrev = bpow(n, mod - 2);
        for (int i = 0; i < n; ++i)
            a[i] = int(a[i] * 1ll * nrev % mod);
    }
}

void poly_mul(vector<int>& a, vector<int> b) {
    if (min(a.size(), b.size()) < 32) {
        vector<int> c = a;
        a.assign(a.size() + b.size() - 1, 0);
        for (int i = 0; i < c.size(); ++i) {
            for (int j = 0; j < b.size(); ++j) {
                a[i + j] = add(a[i + j], mul(c[i], b[j]));
            }
        }
        return;
    }
    int s = a.size() + b.size();
    int r = 1;
    while (r < s) r *= 2;
    a.resize(r);
    b.resize(r);
    fft(a, false);
    fft(b, false);
    for (int j = 0; j < r; j++) {
        a[j] = mul(a[j], b[j]);
    }
    fft(a, true);
}

vector<int> polypow(vector<int> x, int p) {
    vector<int> res = { 1 };
    while (p) {
        if (p & 1)
            poly_mul(res, x);

        p >>= 1;

        if (p)
            poly_mul(x, x);
    }
    return res;
}