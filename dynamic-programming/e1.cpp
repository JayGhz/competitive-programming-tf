#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fast ios::sync_with_stdio(false); cin.tie(nullptr);

int n;
string s;

vector<bool> visited;
vector<bool> is_valid;

inline bool is_zero(int i, int j) {
    if (i == j) return s[i] == '1';
    return s[j] == '0';
}

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int dfs(int i, int j) {
    if (i < 0 || j < 0 || i >= n || j >= n || !is_valid[i * n + j] || visited[i * n + j]) return 0;
    
    visited[i * n + j] = true;
    int res = 1;

    for (int d = 0; d < 4; ++d) {
        int ni = i + dx[d];
        int nj = j + dy[d];
        res += dfs(ni, nj);
    }

    return res;
}

void solve() {
    cin >> n >> s;
    visited.assign(n * n, false);
    is_valid.assign(n * n, false);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (is_zero(i, j)) is_valid[i * n + j] = true;
        }
    }

    int max_size = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (is_valid[i * n + j] && !visited[i * n + j]) {
                int size = dfs(i, j);
                max_size = max(max_size, size);
            }
        }
    }

    cout << max_size << '\n';
}

int32_t main() {
    fast;
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
