#include <unordered_map>
#include <stack>
#include <vector>
using namespace std;

class FreqStack {
private:
    unordered_map<int, int> freq;
    unordered_map<int, stack<int>> group;
    int maxfreq = 0;

public:
    FreqStack() {}
    void push(int val) {
        int f = ++freq[val];
        group[f].push(val);
        if (f > maxfreq) maxfreq = f;
    }

    int pop() {
        int val = group[maxfreq].top();
        group[maxfreq].pop();
        --freq[val];
        if (group[maxfreq].empty()) {
            --maxfreq;
        }
        return val;
    }
};
