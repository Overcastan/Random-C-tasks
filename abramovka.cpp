#include <iostream>
#include <vector>

using namespace std;

void buildTree(vector<int>& a, vector<long long>& tree) {
    int k = 0;
    for (; (1 << k) < a.size(); k++);
    tree.assign(((1 << (k + 1)) - 1), 0);

    for (int i = 0; i < a.size(); i++) {
        tree[i + tree.size() / 2] = a[i];
    }

    return;
}

void update(int L, int R, vector<long long>& tree, int add) {
    L += (tree.size() / 2 - 1);
    R += (tree.size() / 2 - 1);

    while (L <= R) {
        if (L % 2 == 0) {
            tree[L] += add;
            ++L;
        }
        if (R % 2 == 1) {
            tree[R] += add;
            --R;
        }
        if (L > R) {
            break;
        }

        L = (L - 1) / 2;
        R = (R - 1) / 2;
    }

    return;
}

long long get(int index, vector<long long>& tree, vector<int>& a) {
    long long ans = 0;
    int i = index + tree.size() / 2;

    while (i != 0) {
        ans += tree[i];
        i = (i - 1) / 2;
    }

    ans += tree[0];
    return ans;
}

int main() {
    int num;
    cin >> num;
    vector<int> array(num);
    for (int i = 0; i < num; ++i) {
        cin >> array[i];
    }
    int query;
    cin >> query;

    vector<long long> segmentTree;
    buildTree(array, segmentTree);

    for (int i = 0; i < query; ++i) {
        char command;
        cin >> command;

        if (command == 'g') {
            int index;
            cin >> index;
            cout << get(index - 1, segmentTree, array) << "\n";
        } else {
            if (command == 'a') {
                int l, r, add;
                cin >> l >> r >> add;
                update(l, r, segmentTree, add);
            }
        }
    }

    return 0;
}