#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fast ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const long long INF = 4e18;

void solve() {
    int n;
    cin >> n;

    vector<vector<long long>> h(n, vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> h[i][j];
        }
    }

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<long long> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    vector<vector<long long>> dp_x(n, vector<long long>(2, INF));
    dp_x[0][0] = 0;
    dp_x[0][1] = a[0];

    for (int k = 1; k < n; ++k) {
        set<pair<int, int>> forbidden_x_transitions;

        for (int j = 0; j < n; ++j) {
            if (h[k-1][j] == h[k][j]) {
                forbidden_x_transitions.insert({0, 0});
                forbidden_x_transitions.insert({1, 1});
            } else if (h[k-1][j] == h[k][j] + 1) {
                forbidden_x_transitions.insert({0, 1});
            } else if (h[k-1][j] == h[k][j] - 1) {
                forbidden_x_transitions.insert({1, 0});
            }
        }

        if (dp_x[k-1][0] != INF && forbidden_x_transitions.find({0, 0}) == forbidden_x_transitions.end()) {
            dp_x[k][0] = min(dp_x[k][0], dp_x[k-1][0]);
        }
        if (dp_x[k-1][1] != INF && forbidden_x_transitions.find({1, 0}) == forbidden_x_transitions.end()) {
            dp_x[k][0] = min(dp_x[k][0], dp_x[k-1][1]);
        }

        if (dp_x[k-1][0] != INF && forbidden_x_transitions.find({0, 1}) == forbidden_x_transitions.end()) {
            dp_x[k][1] = min(dp_x[k][1], dp_x[k-1][0] + a[k]);
        }
        if (dp_x[k-1][1] != INF && forbidden_x_transitions.find({1, 1}) == forbidden_x_transitions.end()) {
            dp_x[k][1] = min(dp_x[k][1], dp_x[k-1][1] + a[k]);
        }
    }

    long long min_cost_x = min(dp_x[n-1][0], dp_x[n-1][1]);

    vector<vector<long long>> dp_y(n, vector<long long>(2, INF));
    dp_y[0][0] = 0;
    dp_y[0][1] = b[0];

    for (int k = 1; k < n; ++k) {
        set<pair<int, int>> forbidden_y_transitions;

        for (int i = 0; i < n; ++i) {
            if (h[i][k-1] == h[i][k]) {
                forbidden_y_transitions.insert({0, 0});
                forbidden_y_transitions.insert({1, 1});
            } else if (h[i][k-1] == h[i][k] + 1) {
                forbidden_y_transitions.insert({0, 1});
            } else if (h[i][k-1] == h[i][k] - 1) {
                forbidden_y_transitions.insert({1, 0});
            }
        }

        if (dp_y[k-1][0] != INF && forbidden_y_transitions.find({0, 0}) == forbidden_y_transitions.end()) {
            dp_y[k][0] = min(dp_y[k][0], dp_y[k-1][0]);
        }
        if (dp_y[k-1][1] != INF && forbidden_y_transitions.find({1, 0}) == forbidden_y_transitions.end()) {
            dp_y[k][0] = min(dp_y[k][0], dp_y[k-1][1]);
        }

        if (dp_y[k-1][0] != INF && forbidden_y_transitions.find({0, 1}) == forbidden_y_transitions.end()) {
            dp_y[k][1] = min(dp_y[k][1], dp_y[k-1][0] + b[k]);
        }
        if (dp_y[k-1][1] != INF && forbidden_y_transitions.find({1, 1}) == forbidden_y_transitions.end()) {
            dp_y[k][1] = min(dp_y[k][1], dp_y[k-1][1] + b[k]);
        }
    }

    long long min_cost_y = min(dp_y[n-1][0], dp_y[n-1][1]);

    if (min_cost_x == INF || min_cost_y == INF) {
        cout << -1 << endl;
    } else {
        cout << min_cost_x + min_cost_y << endl;
    }
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}