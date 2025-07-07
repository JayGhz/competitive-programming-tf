#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_map<int, unordered_set<char>> rows;
        unordered_map<int, unordered_set<char>> cols;
        unordered_map<int, unordered_set<char>> boxes;

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char num = board[i][j];
                if (num == '.') continue;
                int boxId = (i / 3) * 3 + (j / 3);
    if (rows[i].count(num) || cols[j].count(num) || boxes[boxId].count(num)) {
                    return false;
                }

                rows[i].insert(num);
                cols[j].insert(num);
                boxes[boxId].insert(num);
            }
        }
        return true;
    }
};
