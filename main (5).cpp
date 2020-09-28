#include <iostream>
#include <vector>
#include <algorithm>

class SegmentTree {
    std::vector<int> tree;
    int n;
    void build(int v, int l, int r, const std::vector<int>& init) {
        if(l == r - 1)
            tree[v] = init[l];
        else {
            build(2 * v + 1, l, (r + l) / 2, init);
            build(2 * v + 2, (r + l) / 2, r, init);
            tree[v] = std::min(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }
    int query(int v, int l, int r, int ql, int qr) {
        if(r <= ql || qr <= l)
            return n;
        else if(ql <= l && r <= qr)
            return tree[v];
        else
            return std::min(query(2 * v + 1, l, (l + r) / 2, ql, qr), query(2 * v + 2, (l + r) / 2, r, ql, qr));
    }
    void edit(int v, int l, int r, int idx, int value) {
        if(l == r - 1)
            tree[v] = value;
        else {
            if (idx < (r + l) / 2)
                edit(2 * v + 1, l, (r + l) / 2, idx, value);
            else
                edit(2 * v + 2, (r + l) / 2, r, idx, value);
            tree[v] = std::min(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }
public:
    SegmentTree(const std::vector<int>& init): n(init.size()), tree(init.size() * 4, init.size()) {
        build(0, 0, n, init);
    }
    int query(int l) {
        return query(0, 0, n, l, n);
    }
    void edit(int idx, int value) {
        edit(0, 0, n, idx, value);
    }
};

int main() {
    int n;
    const int max = 1000000;
    std::cin >> n;
    std::vector<int> init(max);
    for(int i = 0; i < max; ++i)
        init[i] = i;
    SegmentTree st(init);
    for(int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        if(x < 0)
            st.edit(-x - 1, -x - 1);
        else {
            int room = st.query(--x);
            std::cout << room + 1 << '\n';
            st.edit(room, max);
        }
    }
    return 0;
}