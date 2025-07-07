string longPrefix(string s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;

    for (int i = 1; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    int maxLen = 0;
    for (int i = 1; i < n; ++i) {
        if (z[i] == n - i) {
            maxLen = z[i];
            break; 
        }
    }

    return s.substr(0, maxLen);
}

int main() {
    string s;
    cin >> s;
    cout << longPrefix(s) << endl;
    return 0;
}
