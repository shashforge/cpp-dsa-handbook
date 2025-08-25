/*Given a string s of '(' , ')' and lowercase English characters.

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
 

Example 1:

Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
Example 2:

Input: s = "a)b(c)d"
Output: "ab(c)d"
Example 3:

Input: s = "))(("
Output: ""
Explanation: An empty string is also valid.

Two-Pass Marking (O(n) time, O(n) space)
First pass (left→right):
Maintain a counter balance = 0.
For each (, do balance++.
For each ), if balance == 0, it’s unmatched—mark it for removal; otherwise balance--.
Letters are always kept.
Second pass (right→left):
Now balance holds the number of unmatched ( remaining.
Scan from end to front; each time you see a ( and balance > 0, mark it for removal and balance--.
Reconstruct:

Build the output by concatenating only the characters not marked.
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int balance = 0;
        int n = s.size();
        vector<bool> keep(n, true);
        
        // 1st pass: mark invalid ')'
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                ++balance;
            } else if (s[i] == ')') {
                if (balance == 0) {
                    keep[i] = false;
                } else {
                    --balance;
                }
            }
        }
        // 2nd pass: mark excess '(' from the end
        for (int i = n - 1; i >= 0 && balance > 0; --i) {
            if (s[i] == '(') {
                keep[i] = false;
                --balance;
            }
        }
        // build result
        string result;
        result.reserve(n);
        for (int i = 0; i < n; ++i) {
            if (keep[i]) result.push_back(s[i]);
        }
        return result;
    }
};
//Time Complexity: O(n)

//Space Complexity: O(n) for the keep array + O(n) for the result
