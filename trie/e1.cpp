#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fast ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

struct Trie {
    struct Node {
        map<char, int> next;
        bool is_terminal = false;
    };
    vector<Node> tree;

    Trie() {
        tree.emplace_back();
    }

    void insert(const string& s) {
        int node = 0;
        for (char c : s) {
            if (!tree[node].next.count(c)) {
                tree[node].next[c] = tree.size();
                tree.emplace_back();
            }
            node = tree[node].next[c];
        }
        tree[node].is_terminal = true;
    }

    pair<bool, bool> dfs(int node = 0) {
        bool can_win = false, can_lose = false;

        if (tree[node].next.empty()) {
            return {false, true};
        }

        for (auto& [c, child] : tree[node].next) {
            auto [child_can_win, child_can_lose] = dfs(child);

            if (!child_can_win) can_win = true;
            if (!child_can_lose) can_lose = true;
        }

        return {can_win, can_lose};
    }
};

void solve() {
    int n, k;
    cin >> n >> k;

    Trie trie;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        trie.insert(s);
    }

    auto [can_win, can_lose] = trie.dfs();

    if (!can_win) {
        cout << "Second\n";
    } else if (can_lose) {
        cout << ((k % 2 == 1) ? "First\n" : "Second\n");
    } else {
        cout << "First\n";
    }
}

int32_t main() {
    fast;
    solve();
    return 0;
}
