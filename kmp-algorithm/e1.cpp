class Solution {
public:
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
                if (len != 0) {
                    len = lps[len - 1];
                }
                else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }

    bool kmpContiene(string texto, string patron) {
        int n = texto.length();
        int m = patron.length();
        vector<int> lps = calcularLPS(patron);

        int i = 0, j = 0;
        while (i < n) {
            if (texto[i] == patron[j]) {
                i++;
                j++;
            }
            if (j == m) {
                return true;
            }
            else if (i < n && texto[i] != patron[j]) {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i++;
            }
        }
        return false;
    }
    int repeatedStringMatch(string a, string b) {
        string repeated = "";
        int count = 0;
        while (repeated.length() < b.length()) {
            repeated += a;
            count++;
        }
        if (kmpContiene(repeated, b)) return count;
        repeated += a;
        count++;
        if (kmpContiene(repeated, b)) return count;
        return -1;
    }
};
