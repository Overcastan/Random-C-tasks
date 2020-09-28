#include <iostream>
#include <vector>



unsigned int Tree_func(unsigned int a, unsigned int b)
{
    return a - b;
}

class SegmentTree
{
private:
    std::vector<unsigned  long long> tree;
    unsigned int n;
    void build(unsigned int v, unsigned int left, unsigned int right, const std::vector<unsigned long long> &init)
    {
        if(left == right)
        {
            tree[v] = init[left];
        }
        else
        {
            build(2 * v + 1, left, (left + right) / 2, init);
            build(2 * v + 2, (left + right) / 2 + 1, right, init);
            //tree[v] = Tree_func(tree[2 * v + 1], tree[2 * v + 2]);
        }
    }
    unsigned int query(unsigned int v, unsigned int left, unsigned int right, unsigned int q_left, unsigned int q_right)
    {
        if(right <= q_left || q_right <= left)
        {
            return 0;
        }
        else if(q_left <= left && right <= q_right)
        {
            return tree[v];
        }
        else
        {
            return Tree_func(query(2*v + 1, left, (left + right)/2, q_left, q_right),
                             query(2*v + 2, (left + right)/2, right, q_left, q_right));
        }
    }
    void edit(unsigned int v, unsigned int left, unsigned int right, unsigned int idx, unsigned int value)
    {
        if(left == right - 1)
        {
            tree[v] = value;
        }
        else
        {
            if(idx < (left + right)/2)
            {
                edit(2*v + 1, left, (left + right)/2, idx, value);
            }
            else
            {
                edit(2*v + 2, (left + right)/2, right, idx, value);
            }
            tree[v] = Tree_func(tree[2*v + 1], tree[2*v + 2]);
        }
    }

    void update(int v, int t_left, int t_right, int left, int right, int add)
    {
        if (left > right)
        {
            return;
        }
        if (left == t_left && t_right == right)
        {
            tree[v] += add;
        }
        else
        {
            int t_middle = (t_left + t_right) / 2;
            update(v * 2 + 1, t_left, t_middle, left, std::min(right, t_middle), add);
            update(v * 2 + 2, t_middle + 1, t_right, std::max(left, t_middle + 1), right, add);
        }
    }
    unsigned long long get_value(int v, int t_left, int t_right, int pos)
    {
        if (t_left == t_right)
        {
            return tree[v];
        }
        if (pos <= (t_left + t_right) / 2)
        {
            return tree[v] + get_value(v * 2 + 1, t_left, (t_left + t_right) / 2, pos);
        }
        else
        {
            return tree[v] + get_value(v * 2 + 2, (t_left + t_right) / 2 + 1, t_right, pos);
        }
    }

public:
    SegmentTree(std::vector<unsigned long long> &init): tree(init.size() * 4), n(init.size())
    {
        build(0, 0, n - 1, init);
    }
    unsigned int query(unsigned int l, unsigned int r)
    {
        return query(0, 0, n, l, r + 1);
    }
    void edit(unsigned int idx, unsigned int value)
    {
        edit(0, 0, n, idx, value);
    }
    void update(unsigned int left, unsigned int right, unsigned int add)
    {
        update(0, 0, n - 1, left - 1, right - 1, add);
    }
    unsigned long long get_value(unsigned int idx)
    {
        return get_value(0, 0, n - 1, idx - 1);
    }
};


int main()
{
    int numOfElem;
    std::cin >> numOfElem;
    std::vector<unsigned long long> array_data(numOfElem, 0);
    for (int i = 0; i < numOfElem; ++i)
    {
        std::cin >> array_data[i];
    }
    SegmentTree segmentTree(array_data);
    unsigned int k, l, r, add;
    std::cin >> k;
    for (int i = 0; i < k; ++i)
    {
        char command;
        std::cin >> command;

        if (command == 'a')
        {
            std::cin >> l >> r >> add;
            segmentTree.update(l, r, add);
        }
        else
        {
            unsigned int num;
            std::cin >> num;
            std::cout << segmentTree.get_value(num) << std::endl;
        }
    }
    return 0;
}
