#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fast ios::sync_with_stdio(false); cin.tie(nullptr);

struct Pattern {
    int len;
    string str;
    int id;

    bool operator<(const Pattern& o) const {
        if (len != o.len) return len > o.len;
        if (str != o.str) return str < o.str;
        return id < o.id;
    }
};

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    set<int> ids;
};

TrieNode* root = new TrieNode();

unordered_map<int, string> id_to_str;
map<int, Pattern> id_to_pattern;
set<Pattern> global_patterns;
string t;

void insert(int id, const string& s) {
    id_to_str[id] = s;
    Pattern p{(int)s.size(), s, id};
    id_to_pattern[id] = p;
    global_patterns.insert(p);

    TrieNode* node = root;
    for (char c : s) {
        if (!node->children.count(c))
            node->children[c] = new TrieNode();
        node = node->children[c];
        node->ids.insert(id);
    }
}

void remove(int id) {
    if (!id_to_str.count(id)) return;
    string& s = id_to_str[id];
    TrieNode* node = root;
    for (char c : s) {
        if (!node->children.count(c)) return;
        node = node->children[c];
        node->ids.erase(id);
    }
    Pattern p = id_to_pattern[id];
    global_patterns.erase(p);
    id_to_pattern.erase(id);
    id_to_str.erase(id);
}

int get_best() {
    if (t.empty()) {
        if (global_patterns.empty()) return -1;
        return global_patterns.begin()->id;
    }

    TrieNode* node = root;
    for (char c : t) {
        if (!node->children.count(c)) return -1;
        node = node->children[c];
    }

    int best_id = -1;
    Pattern best_pattern{0, "", LLONG_MAX};
    for (int id : node->ids) {
        auto it = id_to_pattern.find(id);
        if (it == id_to_pattern.end()) continue;
        if (best_pattern < it->second) continue;
        best_pattern = it->second;
        best_id = id;
    }

    return best_id;
}

void solve() {
    string cmd;
    cin >> cmd;
    if (cmd == "add") {
        int id;
        string s;
        cin >> id >> s;
        insert(id, s);
    } else if (cmd == "delete") {
        int id;
        cin >> id;
        remove(id);
    } else if (cmd == "append") {
        string s;
        cin >> s;
        t += s;
    } else if (cmd == "backspace") {
        int c;
        cin >> c;
        t = (int)t.size() <= c ? "" : t.substr(0, t.size() - c);
    }
    cout << get_best() << '\n';
}

int32_t main() {
    fast;
    int n;
    cin >> n;
    while (n--) solve();
    return 0;
}
