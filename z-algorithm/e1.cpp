#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string shortPalindrome(string s) {
   string rev_s = s;
   reverse(rev_s.begin(), rev_s.end());
   string combined = s + "#" + rev_s;

   vector<int> z(combined.size(), 0);
   for (int i = 1; i < combined.size(); ++i) {
       int j = z[i - 1];
       while (j > 0 && combined[i] != combined[j])
           j = z[j - 1];
       if (combined[i] == combined[j])
           ++j;
       z[i] = j;
   }
   int prefix_len = z.back();
   return rev_s.substr(0, rev_s.size() - prefix_len) + s;
}

int main() {
   string s;
   cin >> s;
   cout << shortPalindrome(s) << endl;
   return 0;
}
