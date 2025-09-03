/*Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Note that you must do this in-place without making a copy of the array.

 

Example 1:

Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
Example 2:

Input: nums = [0]
Output: [0]
 

Constraints:

1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1
 

Follow up: Could you minimize the total number of operations done?
*///We can do the copy & zero-fill in one loop by swapping each non-zero into place when slow ≠ fast:

void moveZeroes(std::vector<int>& nums) {
    for (int slow = 0, fast = 0; fast < static_cast<int>(nums.size()); ++fast) {
        if (nums[fast] != 0) {
            std::swap(nums[slow], nums[fast]);
            ++slow;
        }
    }
}

//C++17 (range-for & auto)
void moveZeroes(std::vector<int>& nums) {
    size_t slow = 0;
    for (auto& v : nums)
        if (v != 0) nums[slow++] = v;
    std::fill(nums.begin() + slow, nums.end(), 0);
}
//C++20 (ranges-based but stable & in-place)
//C++20’s algorithms don’t ship a stable in-place partition, so we still roll our own but with ranges helpers and if-with-init:
#include <ranges>

void moveZeroes(std::vector<int>& nums) {
    for (std::size_t slow = 0, fast = 0; fast < nums.size(); ++fast)
        if (nums[fast] != 0)
            if (auto &a = nums[slow], &b = nums[fast]; slow++, a = std::exchange(b, a), false) {}
    // No need for tail-fill: swap version already places zeros at end
}
