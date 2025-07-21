/*53. Maximum Subarray
Given an integer array nums, find the subarray with the largest sum, and return its sum.

 

Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
Example 2:

Input: nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.
Example 3:

Input: nums = [5,4,-1,7,8]
Output: 23
Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
*/

//C++17 Version
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        int current_sum = nums[0];
        int max_sum = nums[0];

        for (size_t i = 1; i < nums.size(); ++i) {
            current_sum = std::max(nums[i], current_sum + nums[i]);
            max_sum = std::max(max_sum, current_sum);
        }

        return max_sum;
    }
};


//C++20 Version
#include <vector>
#include <algorithm>
#include <ranges>

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        int current_sum = nums[0];
        int max_sum = nums[0];

        for (auto num : std::ranges::subrange(nums.begin() + 1, nums.end())) {
            current_sum = std::max(num, current_sum + num);
            max_sum = std::max(max_sum, current_sum);
        }

        return max_sum;
    }
};
/// C++20 Features:
✅ std::ranges::subrange: Allows elegant iteration over subparts of the vector.

✅ Range-based loop with views — improves readability and intent clarity.

//C++23 Version


#include <vector>
#include <algorithm>
#include <ranges>
#include <print> // C++23

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        int current_sum = nums[0];
        int max_sum = nums[0];

        for (int num : std::ranges::subrange(nums.begin() + 1, nums.end())) {
            current_sum = std::max(num, current_sum + num);
            max_sum = std::max(max_sum, current_sum);
        }

        std::println("Max sum found: {}", max_sum); // Debug print in C++23

        return max_sum;
    }
};

/*C++23 Features:
✅ std::println: Safer, formatted output like Python's print().

✅ Continued use of ranges::subrange.

-----------------------------------------------------
🤔 Follow-Up Interview Questions
Can you return the actual subarray instead of just the sum?
Explanation:
Track start and end indices of the maximum subarray using auxiliary variables.*/
#include <vector>
#include <algorithm>
#include <tuple>

std::tuple<int, int, int> maxSubArrayWithIndices(const std::vector<int>& nums) {
    int current_sum = nums[0], max_sum = nums[0];
    int start = 0, end = 0, temp_start = 0;

    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] > current_sum + nums[i]) {
            current_sum = nums[i];
            temp_start = i;
        } else {
            current_sum += nums[i];
        }

        if (current_sum > max_sum) {
            max_sum = current_sum;
            start = temp_start;
            end = i;
        }
    }
    return {max_sum, start, end}; // returns sum, start index, end index
}

/*2. All Numbers Are Negative
Explanation:
Kadane’s still works — it selects the largest (least negative) number.*/

//. Handle Streaming Data (Online Algorithm)
//Explanation:or streaming, we process one number at a time — Kadane’s is inherently online.
class OnlineKadane {
    int current_sum;
    int max_sum;

public:
    OnlineKadane() : current_sum(INT_MIN), max_sum(INT_MIN) {}

    void process(int num) {
        if (current_sum < 0)
            current_sum = num;
        else
            current_sum += num;

        max_sum = std::max(max_sum, current_sum);
    }

    int getMax() const { return max_sum; }
};



