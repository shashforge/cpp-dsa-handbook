/*A string can be abbreviated by replacing any number of non-adjacent, non-empty substrings with their lengths. The lengths should not have leading zeros.

For example, a string such as "substitution" could be abbreviated as (but not limited to):

"s10n" ("s ubstitutio n")
"sub4u4" ("sub stit u tion")
"12" ("substitution")
"su3i1u2on" ("su bst i t u ti on")
"substitution" (no substrings replaced)
The following are not valid abbreviations:

"s55n" ("s ubsti tutio n", the replaced substrings are adjacent)
"s010n" (has leading zeros)
"s0ubstitution" (replaces an empty substring)
Given a string word and an abbreviation abbr, return whether the string matches the given abbreviation.

A substring is a contiguous non-empty sequence of characters within a string.

 

Example 1:

Input: word = "internationalization", abbr = "i12iz4n"
Output: true
Explanation: The word "internationalization" can be abbreviated as "i12iz4n" ("i nternational iz atio n").
Example 2:

Input: word = "apple", abbr = "a2e"
Output: false
Explanation: The word "apple" cannot be abbreviated as "a2e".
 */

#include <string>
#include <cctype>
using namespace std;

class Solution {
public:
    bool validWordAbbreviation(const string& word, const string& abbr) {
        int i = 0, j = 0;
        int n = word.size(), m = abbr.size();
        while (i < n && j < m) {
            if (isalpha(abbr[j])) {
                // letter must match
                if (word[i++] != abbr[j++]) 
                    return false;
            } else {
                // no leading zero allowed
                if (abbr[j] == '0') return false;
                int skip = 0;
                while (j < m && isdigit(abbr[j])) {
                    skip = skip * 10 + (abbr[j++] - '0');
                }
                i += skip;
            }
        }
        // both pointers must reach end
        return i == n && j == m;
    }
};

//Time Complexity: O(n + m), where n = word.length(), m = abbr.length()

//Space Complexity: O(1) (only a few integer counters)
