/*A peak element is an element that is strictly greater than its neighbors.

Given a 0-indexed integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.

You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is always considered to be strictly greater than a neighbor that is outside the array.

You must write an algorithm that runs in O(log n) time.

 

Example 1:

Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.
Example 2:

Input: nums = [1,2,1,3,5,6,4]
Output: 5
Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.

 Binary Search (O(log n)) 🚀
We can do better using binary search. Here's the cool idea:
Pick the middle element.
Check if it is a peak:
If yes, return its index.
If not, go towards the bigger neighbor.
Because if nums[mid] < nums[mid+1], then a peak must exist on the right.
Else go left.
This works because in any "uphill", there is always a peak at the top or end.

Example
Let's say: nums = [1, 2, 1, 3, 5, 6, 4]
Start with mid = 3 → nums[3] = 3
Is 3 > 1 and 3 > 5? ❌
Since nums[3] < nums[4], go right
Now search in [5, 6, 4]
Eventually you’ll reach 6, which is a peak!
*/
class Solution {
public:
    int findPeakElement(std::vector<int>& nums) {
        return findPeak(nums, 0, nums.size() - 1);
    }

    int findPeak(const std::vector<int>& arr, int lo, int hi) {
        if (lo == hi) return lo;

        int mid = lo + (hi - lo) / 2;

        if (arr[mid] > arr[mid + 1]) {
            return findPeak(arr, lo, mid);       // peak is on the left (including mid)
        } else {
            return findPeak(arr, mid + 1, hi);    // peak is on the right
        }
    }
};
