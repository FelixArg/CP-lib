struct dsu {
public:
    dsu() : _n(0) {}
    dsu(int n) : _n(n), sz(n, 1), parent(n) { std::iota(parent.begin(), parent.end(), 0); }

    void merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = find(a), y = find(b);
        if (x == y) return;
        if (sz[x] < sz[y]) std::swap(x, y);
        sz[x] += sz[y];
        parent[y] = parent[x];
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return find(a) == find(b);
    }

    int find(int a) {
        assert(0 <= a && a < _n);
        if (parent[a] == a) return a;
        return parent[a] = find(parent[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return sz[a];
    }

private:
    int _n;
    std::vector<int> parent;
    std::vector<int> sz;
};