/*Given a string s, return the longest palindromic substring in s.

Example 1:
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.
Example 2:
Input: s = "cbbd"
Output: "bb"
 Constraints:

1 <= s.length <= 1000
s consist of only digits and English letters.
-------
Indexes:   0  1  2  3  4
Chars:     b  a  b  a  d
1️⃣ Initialize dp[i][i] = true:
All diagonals (length 1 substrings) are palindromes.

T F F F F
F T F F F
F F T F F
F F F T F
F F F F T
2️⃣ Length-2 substrings:
Check pairs: s[i] == s[i+1]

"ba" → no
"ab" → no
"ba" → no
"ad" → no

No update — all false on off-diagonal

3️⃣ Length ≥ 3 substrings:
For i=0, j=2: "bab" → s[0]==s[2] and dp[1][1]=true → mark dp[0][2]=true

For i=1, j=3: "aba" → s[1]==s[3] and dp[2][2]=true → mark dp[1][3]=true

T F T F F
F T F T F
F F T F F
F F F T F
F F F F T
Now start=0, maxLen=3 or start=1, maxLen=3

Final result: "bab" or "aba" ✅
*/
//Matrix Explanation
#include <vector>
#include <string>

class Solution {
public:
    std::string longestPalindrome(const std::string& s) {
        int n = s.length();
        if (n <= 1) return s;

        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
        int maxLen = 1;
        int start = 0;

        // Step 1: Every char is a palindrome
        for (int i = 0; i < n; ++i)
            dp[i][i] = true;

        // Step 2: Check length 2 substrings
        for (int i = 0; i < n - 1; ++i) {
            if (s[i] == s[i + 1]) {
                dp[i][i + 1] = true;
                start = i;
                maxLen = 2;
            }
        }

        // Step 3: Length 3 and more
        for (int len = 3; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j] && dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                    start = i;
                    maxLen = len;
                }
            }
        }

        return s.substr(start, maxLen);
    }
};

////////////////////////Follow-up Questions (with Detailed Solutions)
//Q1: Can You Optimize Space from O(n²) to O(1)?
//Yes! Using Expand Around Center, which uses no extra matrix.

class Solution {
public:
    std::string longestPalindrome(const std::string& s) {
        if (s.empty()) return "";
        int start = 0, end = 0;

        for (int i = 0; i < s.size(); ++i) {
            int len1 = expand(s, i, i);     // odd-length
            int len2 = expand(s, i, i + 1); // even-length
            int len = std::max(len1, len2);

            if (len > end - start) {
                start = i - (len - 1) / 2;
                end = i + len / 2;
            }
        }

        return s.substr(start, end - start + 1);
    }

private:
    int expand(const std::string& s, int l, int r) {
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            --l;
            ++r;
        }
        return r - l - 1;
    }
};

⏳ Time: O(n²)
💾 Space: O(1) ✅
// Debug Mode with Live Tracing
#include <iostream>
#include <string>

class Solution {
public:
    std::string longestPalindrome(const std::string& s) {
        if (s.empty()) return "";
        int start = 0, end = 0;

        for (int i = 0; i < s.size(); ++i) {
            int len1 = expand(s, i, i);
            int len2 = expand(s, i, i + 1);
            int len = std::max(len1, len2);

            if (len > end - start) {
                start = i - (len - 1) / 2;
                end = i + len / 2;
                std::cout << "Updated longest: " << s.substr(start, end - start + 1)
                          << " (i=" << i << ", len=" << len << ")\n";
            }
        }

        return s.substr(start, end - start + 1);
    }

private:
    int expand(const std::string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            std::cout << "Expanding: s[" << left << "] = " << s[left]
                      << ", s[" << right << "] = " << s[right] << "\n";
            --left;
            ++right;
        }
        return right - left - 1;
    }
};


/* 3. Manacher's Algorithm (O(n))
 Idea:
Transform input with # between chars: "abc" → #a#b#c#
Use palindrome mirror property to avoid redundant expansion
Track center and rightmost boundary*/
#include <string>
#include <vector>

class Solution {
public:
    std::string longestPalindrome(const std::string& s) {
        if (s.empty()) return "";

        // Step 1: Transform string
        std::string t = "^";
        for (char c : s) {
            t += "#" + std::string(1, c);
        }
        t += "#$";

        int n = t.size();
        std::vector<int> P(n, 0);
        int center = 0, right = 0;

        for (int i = 1; i < n - 1; ++i) {
            int mirror = 2 * center - i;

            if (i < right)
                P[i] = std::min(right - i, P[mirror]);

            while (t[i + (1 + P[i])] == t[i - (1 + P[i])])
                ++P[i];

            if (i + P[i] > right) {
                center = i;
                right = i + P[i];
            }
        }

        // Step 3: Find max length and position
        int maxLen = 0, centerIndex = 0;
        for (int i = 1; i < n - 1; ++i) {
            if (P[i] > maxLen) {
                maxLen = P[i];
                centerIndex = i;
            }
        }

        int start = (centerIndex - maxLen) / 2;
        return s.substr(start, maxLen);
    }
};
// Time: O(n)
//Space: O(n)
