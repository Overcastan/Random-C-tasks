#include <iostream>
#include <vector>
#include <algorithm>

unsigned int Tree_func(unsigned int a, unsigned int b){
    return a + b;
}

class SegmentTree{
private:
    std::vector<unsigned  int> tree;
    unsigned  int n;
    void build(unsigned int v, unsigned int l, unsigned int r, const std::vector<unsigned  int> &init){
        if(l == r - 1){
            tree[v] = init[l];
        } else{
            build(2*v + 1, l, (l + r)/2, init);
            build(2*v + 2, (l + r)/2, r, init);
            tree[v] = Tree_func(tree[2*v + 1], tree[2*v + 2]);
        }
    }
    unsigned int query(unsigned int v, unsigned int l, unsigned int r, unsigned int ql, unsigned int qr){
        if(r <= ql || qr <= l){
            return 0;
        } else if(ql <= l && r <= qr){
            return tree[v];
        } else{
            return Tree_func(query(2*v + 1, l, (l + r)/2, ql, qr), query(2*v + 2, (l + r)/2, r, ql, qr));
        }
    }
    void edit(unsigned int v, unsigned int l, unsigned int r, unsigned int idx, unsigned int value){
        if(l == r - 1){
            tree[v] = value;
        } else{
            if(idx < (l + r)/2){
                edit(2*v + 1, l, (l + r)/2, idx, value);
            } else{
                edit(2*v + 2, (l + r)/2, r, idx, value);
            }
            tree[v] = Tree_func(tree[2*v + 1], tree[2*v + 2]);
        }
    }

public:
    SegmentTree(std::vector<unsigned int> &init): tree(init.size() * 4), n(init.size()){
        build(0, 0, n, init);
    }
    unsigned int query(unsigned int l, unsigned int r){
        return query(0, 0, n, l, r + 1);
    }
    void edit(unsigned int idx, unsigned int value){
        edit(0, 0, n, idx, value);
    }
};

unsigned int nextRand(unsigned int a, unsigned  int b, unsigned  int &cur);

int main() {
    unsigned  int cur = 0; // беззнаковое 32-битное число
    std::vector<unsigned int> init (1 << 24);
    SegmentTree Tree(init);
    unsigned int m, q;
    std::cin >> m >> q;
    unsigned  int a, b;
    std::cin >> a >> b;
    for (unsigned int i = 0; i < m; ++i){
        unsigned int add = nextRand(a, b, cur); // число, которое нужно прибавить
        unsigned int l = nextRand(a, b, cur);
        unsigned int r = nextRand(a, b, cur);
        if (l > r) std::swap(l, r); // получили отрезок [l..r]
        for(unsigned int j = l; j < r + 1; ++j){
            Tree.edit(j, add);
        }
    }
    unsigned  int result = 0;
    for(unsigned int i = 0; i < q; ++i){
        unsigned int l = nextRand(a, b, cur);
        unsigned int r = nextRand(a, b, cur);
        if (l > r) std::swap(l, r); // получили отрезок [l..r]
        result += Tree.query(l, r);
    }
    std::cout << result;
    return 0;
}
unsigned  int nextRand(unsigned  int a, unsigned  int b, unsigned  int &cur) {
    cur = cur * a + b; // вычисляется с переполнениями
    return cur >> 8; // число от 0 до 224-1.
}

