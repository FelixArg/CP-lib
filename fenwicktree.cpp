template <class T> struct fenwick_tree {

public:
    fenwick_tree() : _n(0) {}
    fenwick_tree(int n) : _n(n), data(n) {}

    void add(int pos, T val) {
        for (; pos < _n; pos = (pos | (pos + 1)))
            data[pos] += val;
    }

    T sum(int l, int r) {
        assert(l <= r && r < _n);
        if (l <= 0)
            return sum(r);
        return sum(r) - sum(l - 1);
    }

private:
    int _n;
    std::vector<T> data;

    T sum(int pos) {
        T res = 0;
        for (; pos >= 0; pos = (pos & (pos + 1)) - 1)
            res += data[pos];
        return res;
    }
};