#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) (x).begin(), (x).end()
#define fast ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

vector<int> bit;
int bit_size;

void init_bit(int n) {
    bit_size = n;
    bit.assign(n + 1, 0);
}

void update_bit(int idx, int delta) {
    for (; idx <= bit_size; idx += idx & -idx) {
        bit[idx] += delta;
    }
}

int query_bit(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum += bit[idx];
    }
    return sum;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> prefix_freq(n);
    map<int, int> current_counts;
    for (int i = 0; i < n; ++i) {
        current_counts[a[i]]++;
        prefix_freq[i] = current_counts[a[i]];
    }

    vector<int> suffix_freq(n);
    current_counts.clear();
    for (int i = n - 1; i >= 0; --i) {
        current_counts[a[i]]++;
        suffix_freq[i] = current_counts[a[i]];
    }

    init_bit(n); 

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += query_bit(n) - query_bit(suffix_freq[i]);
        update_bit(prefix_freq[i], 1);
    }

    cout << ans << "\n";
}

int32_t main() {
    fast;
    int t;
    solve();
    return 0;
}