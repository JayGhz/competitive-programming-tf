class Solution {
public:
    int getSum(vector<int>& fw, int i) {
        int sum = 0;
        ++i;
        while (i > 0) {
            sum += fw[i];
            i -= i & -i;
        }
        return sum;
    }

    void updateFW(vector<int>& fw, int n, int i, int delta) {
        ++i;
        while (i <= n) {
            fw[i] += delta;
            i += i & -i;
        }
    }
    int numTeams(vector<int>& rating) {
        int n = rating.size();
        vector<int> sorted = rating;
        sort(sorted.begin(), sorted.end());
        map<int, int> compressed;
        int idx = 0;

        for (int x : sorted) {
            if (compressed.find(x) == compressed.end())
                compressed[x] = idx++;
        }

        int size = compressed.size();
        vector<int> left(size + 2, 0), right(size + 2, 0);
        vector<int> mapped(n);
        for (int i = 0; i < n; ++i) {
            mapped[i] = compressed[rating[i]];
            updateFW(right, size + 1, mapped[i], 1);
        }

        int result = 0;
        for (int i = 0; i < n; ++i) {
            int r = mapped[i];
            updateFW(right, size + 1, r, -1);

            int lLess = getSum(left, r - 1);
            int lGreater = i - getSum(left, r);
            int rLess = getSum(right, r - 1);
            int rGreater = (n - i - 1) - getSum(right, r);

            result += lLess * rGreater + lGreater * rLess;

            updateFW(left, size + 1, r, 1);
        }

        return result;
    }
};
