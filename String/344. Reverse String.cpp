/*
Write a function that reverses a string. The input string is given as an array of characters s.

You must do this by modifying the input array in-place with O(1) extra memory.

Example 1:

Input: s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]
Example 2:

Input: s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
  */
//Using Two Pointers - O(n) Time and O(1) Space
//(two-pointer swap)
class Solution {
public:
    void reverseString(vector<char>& s) {
        int i = 0, j = s.size() - 1;
        while (i < j) {
            swap(s[i++], s[j--]);
        }
    }
};

//C++20 (with std::ranges::reverse)

#include <ranges>
class Solution {
public:
    void reverseString(vector<char>& s) {
        std::ranges::reverse(s);
    }
};
