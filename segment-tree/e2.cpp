#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class SegmentTree {
    vector<int> arbol;
    int size;

public:
    SegmentTree(int n) {
        size = n;
        arbol.resize(4 * n, 0);
    }

    void update(int nodo, int l, int r, int pos, int val) {
        if (l == r) {
            arbol[nodo] += val;
        } else {
            int mid = (l + r) / 2;
            if (pos <= mid)
                update(2 * nodo, l, mid, pos, val);
            else
                update(2 * nodo + 1, mid + 1, r, pos, val);
            arbol[nodo] = arbol[2 * nodo] + arbol[2 * nodo + 1];
        }
    }

    int query(int nodo, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return arbol[nodo];
        int mid = (l + r) / 2;
        return query(2 * nodo, l, mid, ql, qr) +
               query(2 * nodo + 1, mid + 1, r, ql, qr);
    }

    void add(int pos) {
        update(1, 0, size - 1, pos, 1);
    }

    int Menor(int pos) {
        if (pos == 0) return 0;
        return query(1, 0, size - 1, 0, pos - 1);
    }

    int Mayor(int pos) {
        if (pos == size - 1) return 0;
        return query(1, 0, size - 1, pos + 1, size - 1);
    }
};

class Solution {
public:
    int ArrayOrdenado(vector<int>& instructions) {
        const int MOD = 1e9 + 7;

        vector<int> sorted = instructions;
        sort(sorted.begin(), sorted.end());
        map<int, int> compressed;
        int idx = 0;
        for (int num : sorted) {
            if (compressed.count(num) == 0) {
                compressed[num] = idx++;
            }
        }

        SegmentTree segTree(idx);
        long long cost = 0;

        for (int num : instructions) {
            int pos = compressed[num];
            int menos = segTree.Menor(pos);
            int mas = segTree.Mayor(pos);
            cost = (cost + min(menos, mas)) % MOD;
            segTree.add(pos);
        }
        return cost;
    }
};

int main() {
    Solution sol;

    int n;
    cout << "Ingrese la cantidad de elementos: ";
    cin >> n;

    vector<int> instructions(n);
    cout << "Ingrese los elementos del arreglo:";
    for (int i = 0; i < n; ++i) {
        cin >> instructions[i];
    }

    int result = sol.ArrayOrdenado(instructions);
    cout << "Costo total: " << result << endl;
    return 0;
}
