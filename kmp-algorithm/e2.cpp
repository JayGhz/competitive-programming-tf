class Solution {
public:
    const int MOD = 1e9 + 7;
    string s1, s2, evil;
    vector<int> lps;
    int dp[501][51][2][2];

    
    vector<int> calcularLPS(string patron) {
        int n = patron.length();
        vector<int> lps(n, 0);
        int len = 0;
        int i = 1;

        while (i < n) {
            if (patron[i] == patron[len]) {
                len++;
                lps[i] = len;
                i++;
            }
            else {
                if (len != 0)
                    len = lps[len - 1];
                else
                    i++;
            }
        }
        return lps;
    }

    int dfs(int pos, int evilMatched, bool tightLow, bool tightHigh) {
        if (evilMatched == evil.size()) return 0;
        if (pos == s1.size()) return 1;

        if (dp[pos][evilMatched][tightLow][tightHigh] != -1)
            return dp[pos][evilMatched][tightLow][tightHigh];

        char from = tightLow ? s1[pos] : 'a';
        char to = tightHigh ? s2[pos] : 'z';

        int ans = 0;
        for (char c = from; c <= to; ++c) {
            int k = evilMatched;
            while (k > 0 && evil[k] != c)
                k = lps[k - 1];
            if (evil[k] == c) k++;

            bool nextTightLow = tightLow && (c == s1[pos]);
            bool nextTightHigh = tightHigh && (c == s2[pos]);

            ans = (ans + dfs(pos + 1, k, nextTightLow, nextTightHigh)) % MOD;
        }

        return dp[pos][evilMatched][tightLow][tightHigh] = ans;
    }

    int findGoodStrings(int n, string s1_in, string s2_in, string evil_in) {
        s1 = s1_in;
        s2 = s2_in;
        evil = evil_in;
        lps = calcularLPS(evil);
        memset(dp, -1, sizeof(dp));
        return dfs(0, 0, true, true);
    }
};
