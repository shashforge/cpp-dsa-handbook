/*42. Trapping Rain Water
https://leetcode.com/problems/trapping-rain-water/description/?envType=problem-list-v2&envId=dynamic-programming
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9
*/


#include <vector>
#include <algorithm>
#include <limits>

int trap(const std::vector<int>& height) {
    int n = static_cast<int>(height.size());
    if (n < 3) return 0;               // no walls, no water

    int l = 0, r = n - 1;
    int leftMax  = height[l];
    int rightMax = height[r];
    int water = 0;

    while (l < r) {
        if (leftMax <= rightMax) {
            // water depends on leftMax
            ++l;
            leftMax = std::max(leftMax, height[l]);
            water  += leftMax - height[l];
        } else {
            // water depends on rightMax
            --r;
            rightMax = std::max(rightMax, height[r]);
            water   += rightMax - height[r];
        }
    }
    return water;
}
