#include <iostream>
#include <vector>

unsigned int a, b; // даны во входных данных
unsigned int cur = 0; // беззнаковое 32-битное число
unsigned int nextRand() {
    cur = cur * a + b; // вычисляется с переполнениями
    return cur >> 8; // число от 0 до 2^24-1.
}

void segmentAdd(std::vector<unsigned int>& arrayOfNum, std::vector<unsigned int>& arrayOfSums,
                int queriesAdd, unsigned int& n)
{
    unsigned int l, r;
    for (unsigned int i = 0; i < queriesAdd; ++i)
    {
        unsigned int add = nextRand();
        l = nextRand();
        r = nextRand();
        if (l > r)
        {
            std::swap(l, r);
            arrayOfNum[l] += add;
            if (r + 1 < n)
            {
                arrayOfNum[r + 1] -= add;
            }
        }
    }
    unsigned int delta = arrayOfNum[0];
    arrayOfSums[0] = arrayOfNum[0];
    for (int i = 1; i < n; ++i)
    {
        delta += arrayOfNum[i];
        arrayOfSums[i] = arrayOfSums[i - 1] + delta;
    }
}

void sumOfQueries(std::vector<unsigned int>& arrayOfSums, int queriesSum, unsigned int& answer)
{
    unsigned int l, r;
    for (int i = 0; i < queriesSum; ++i)
    {
        l = nextRand();
        r = nextRand();
        if (l > r)
        {
            std::swap(l, r);
        }
        if (l != 0)
        {
            answer += arrayOfSums[r] - arrayOfSums[l - 1];
        }
        else
        {
            answer += arrayOfSums[r];
        }
    }
}

int main()
{
    unsigned int queriesAdd, queriesSum;
    std::cin >> queriesAdd >> queriesSum;
    std::cin >> a >> b;
    unsigned int n = (1 << 24);
    std::vector<unsigned int> arrayOfNum(n, 0);
    std::vector<unsigned int> arrayOfSums(n, 0);
    segmentAdd(arrayOfNum, arrayOfSums, queriesAdd, n);
    unsigned int answer = 0;
    sumOfQueries(arrayOfSums, queriesSum, answer);
    std::cout << answer << std::endl;
    return 0;
}