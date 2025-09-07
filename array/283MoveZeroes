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
 

Follow up: Could you minimize the total number of operations done?*/



// C++17 — clean & optimal

#include <vector>

std::vector<int> applyOperations(std::vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i + 1 < n; ++i) {
        if (nums[i] == nums[i + 1]) {        // rule 1
            nums[i] <<= 1;                   // multiply by 2
            nums[i + 1] = 0;
        }
    }
    int slow = 0;                            // stable move-zeroes
    for (int fast = 0; fast < n; ++fast)
        if (nums[fast] != 0) nums[slow++] = nums[fast];
    std::fill(nums.begin() + slow, nums.end(), 0);
    return nums;
}

///Best” Variant (single pass, fewer writes)
#include <vector>
using std::vector;

vector<int> applyOperations(vector<int>& nums) {
    int n = nums.size();
    int write = 0;

    for (int i = 0; i < n; ++i) {
        if (i + 1 < n && nums[i] == nums[i + 1]) {   // combine
            nums[i] <<= 1;
            nums[i + 1] = 0;
        }
        if (nums[i] != 0) std::swap(nums[write++], nums[i]);
    }
    return nums;
}
/*
| #  | Typical Question                                          | Fast Answer                                                                                                                                                                  | Deep-Dive Talking Points                                                                                                                        |
| -- | --------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------- |
| 1  | **Can you prove it’s stable?**                            | We always write the next surviving non-zero at the earliest free slot *while scanning left-to-right* – order is preserved.                                                   | Formalize induction: at step `k` the first `k` non-zeros appear in original order; step `k+1` writes the next.                                  |
| 2  | **Worst-case number of writes?**                          | ≤ `n`.                                                                                                                                                                       | Each element is written at most once in the overwrite variant, twice (swap) in the minimal-writes variant. Lower bound is `#nonZero` – optimal. |
| 3  | **Handle 64-bit overflow?**                               | Cast to `int64_t` before doubling.                                                                                                                                           | Or guard with `if (nums[i] > INT_MAX/2)`, return error/overflow flag.                                                                           |
| 4  | **Stream of numbers too large for RAM (Google)?**         | Maintain a sliding window of two items to detect duplicates, emit output stream & count zeros, then append that many zeros at the very end of the file/pipe.                 | Single pass, O(1) RAM; needs two-phase output or buffered write.                                                                                |
| 5  | **Parallel version (NVIDIA)?**                            | Phase 1: element-wise combine duplicates in parallel (needs careful boundary handling per block). Phase 2: prefix-sum to compute final positions of non-zeros, then scatter. | On GPU use warp-level primitives; total O(n) work, $O(\log n)$ depth.                                                                           |
| 6  | **What if zeros must stay in order too?**                 | Impossible after rule 1 mutates values; the spec explicitly allows rearranging zeros.                                                                                        | Show counter-example to prove non-feasibility.                                                                                                  |
| 7  | **Return only the number of trailing zeros** (Meta)?      | After algorithm: `zeros = n – lastNonZeroIndex – 1`.                                                                                                                         | Or count zeros during compaction for O(1) extra.                                                                                                |
| 8  | **Memory-constrained device (Apple)?**                    | Prefer the single-swap solution (lower peak temporary writes, no second fill loop).                                                                                          | Discuss cache friendliness on ARM.                                                                                                              |
| 9  | **Generalise: instead of `× 2`, apply function `f(x)`**   | Treat `f` as a black-box; complexity unchanged.                                                                                                                              | But if `f` is non-idempotent or may output zero, stabilise behaviour with spec.                                                                 |
| 10 | **Follow-up: multiple consecutive equals (e.g. 2-2-2-2)** | Specification is pairwise left-to-right; “2 2 2 2” → “4 0 2 0” then compaction → “4 2 0 0”.                                                                                  | Show manual trace, emphasise that the algorithm already does this.                                                                              |

*/

