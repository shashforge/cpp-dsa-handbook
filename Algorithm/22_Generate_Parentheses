/*Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

Example 1:
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]
*/


#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> result;
        backtrack("", 0, 0, n, result);
        return result;
    }

private:
    // backtrack(current_string, open_count, close_count, total_pairs, result_list)
    void backtrack(const std::string& current, int open, int close, int n, std::vector<std::string>& result) {
        //  Base case: if current string is complete
        if (current.length() == n * 2) {
            result.push_back(current);
            return;
        }

        // Can we add '('?
        if (open < n) {
            backtrack(current + "(", open + 1, close, n, result);
        }

        //  Can we add ')'?
        if (close < open) {
            backtrack(current + ")", open, close + 1, n, result);
        }
    }
};
// Time Complexity: O(2ⁿ) in worst case
// Space: O(n) recursion depth per path (no extra memoization)


//Dynamic Programming 

#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::vector<std::string>> dp(n + 1);
        dp[0] = {""}; // base case

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                for (const std::string& p : dp[j]) {
                    for (const std::string& q : dp[i - 1 - j]) {
                        dp[i].push_back("(" + p + ")" + q);
                    }
                }
            }
        }

        return dp[n];
    }
};
/*What’s happening?
We are building from smaller solutions.

Example for n = 3:
i=3:
  j=0: "(" + "" + ")" + dp[2]
  j=1: "(" + dp[1] + ")" + dp[1]
  j=2: "(" + dp[2] + ")" + ""

 Time Complexity: Catalan Number = O(4ⁿ / √n)
 Space Complexity: O(Catalan(n)) (storing all strings)
*/
