/*Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
 

Example 1:

Input: s = "()"

Output: true

Example 2:

Input: s = "()[]{}"

Output: true

Example 3:

Input: s = "(]"

Output: false

Example 4:

Input: s = "([])"

Output: true

 */

#include <string>
#include <stack>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isValid(const string& s) {
        // map each closing bracket to its matching opening bracket
        static const unordered_map<char,char> match = {
            {')','('}, {']','['}, {'}','{'}
        };

        stack<char> st;
        for (char c : s) {
            if (match.count(c)) {
                // c is a closing bracket
                if (st.empty() || st.top() != match.at(c))
                    return false;
                st.pop();
            } else {
                // c is an opening bracket (or invalid char)
                st.push(c);
            }
        }
        // all opens must be matched
        return st.empty();
    }
};
