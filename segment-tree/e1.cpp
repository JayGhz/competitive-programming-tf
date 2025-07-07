#include <iostream>
#include <vector>
#include <string>

using namespace std;

class NumArray {
    vector<int> tree;
    int n;

    void build(vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
        } else {
            int mid = (start + end) / 2;
            build(nums, 2 * node, start, mid);
            build(nums, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    void updateTree(int node, int start, int end, int index, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (index <= mid) {
                updateTree(2 * node, start, mid, index, val);
            } else {
                updateTree(2 * node + 1, mid + 1, end, index, val);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        int left = query(2 * node, start, mid, l, r);
        int right = query(2 * node + 1, mid + 1, end, l, r);
        return left + right;
    }

public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n);
        build(nums, 1, 0, n - 1);
    }

    void update(int index, int val) {
        updateTree(1, 0, n - 1, index, val);
    }

    int sumRange(int left, int right) {
        return query(1, 0, n - 1, left, right);
    }
};

int main() {
    int numOps;
    cout << "Ingrese el numero de operaciones: ";
    cin >> numOps;

    vector<string> commands(numOps);
    vector<vector<int>> inputs(numOps);

    cout << "Ingrese los comandos (NumArray, sumRange, update):\n";
    for (int i = 0; i < numOps; ++i) {
        cout << "Comando #" << i << ": ";
        cin >> commands[i];

        int k;
        if (commands[i] == "NumArray") {
            cout << "Cantidad de elementos del arreglo: ";
            cin >> k;
        } else if (commands[i] == "sumRange") {
            k = 2;
        } else if (commands[i] == "update") {
            k = 2;
        }

        cout << "Ingrese " << k << " valores:\n";
        vector<int> temp(k);
        for (int j = 0; j < k; ++j) {
            cin >> temp[j];
        }
        inputs[i] = temp;
    }

    cout << "\nOutput:\n[";
    NumArray* obj = nullptr;
    for (int i = 0; i < numOps; ++i) {
        if (commands[i] == "NumArray") {
            obj = new NumArray(inputs[i]);
            cout << "null";
        } else if (commands[i] == "sumRange") {
            int res = obj->sumRange(inputs[i][0], inputs[i][1]);
            cout << ", " << res;
        } else if (commands[i] == "update") {
            obj->update(inputs[i][0], inputs[i][1]);
            cout << ", null";
        }
    }
    cout << "]" << endl;

    delete obj;
    return 0;
}
