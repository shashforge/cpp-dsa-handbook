You are given a 0-indexed array of positive integers w where w[i] describes the weight of the ith index.

You need to implement the function pickIndex(), which randomly picks an index in the range [0, w.length - 1] (inclusive) and returns it. The probability of picking an index i is w[i] / sum(w).

For example, if w = [1, 3], the probability of picking index 0 is 1 / (1 + 3) = 0.25 (i.e., 25%), and the probability of picking index 1 is 3 / (1 + 3) = 0.75 (i.e., 75%).
 

Example 1:

Input
["Solution","pickIndex"]
[[[1]],[]]
Output
[null,0]

Explanation
Solution solution = new Solution([1]);
solution.pickIndex(); // return 0. The only option is to return 0 since there is only one element in w.
Example 2:

Input
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
[[[1,3]],[],[],[],[],[]]
Output
[null,1,1,1,1,0]

Explanation
Solution solution = new Solution([1, 3]);
solution.pickIndex(); // return 1. It is returning the second element (index = 1) that has a probability of 3/4.
solution.pickIndex(); // return 1
solution.pickIndex(); // return 1
solution.pickIndex(); // return 1
solution.pickIndex(); // return 0. It is returning the first element (index = 0) that has a probability of 1/4.

Since this is a randomization problem, multiple answers are allowed.
All of the following outputs can be considered correct:
[null,1,1,1,1,0]
[null,1,1,1,1,1]
[null,1,1,1,0,0]
[null,1,1,1,0,1]
[null,1,0,1,0,0]
......


-----------------
Sure! Let’s break down **Leetcode 528: Random Pick with Weight** in a way a 14-year-old can easily understand.

---

### 🎯 **The Problem (Simple Version)**

Imagine you have a bunch of **tickets** in a box. But not all tickets are the same. Some numbers have **more tickets**, and some have **less**.
Let’s say:
```
weights = [1, 3]
```
* That means you have:
  * 1 ticket for number 0
  * 3 tickets for number 1
So in total, you have 4 tickets.
If you pick one **random ticket**, the chance of getting:
* number 0 is **1 out of 4** (25%)
* number 1 is **3 out of 4** (75%)
Your job is to:
* Write a class called `Solution`
* The class will take `weights` during setup
* It has a function called `pickIndex()` that returns a number (like 0 or 1)
* It should return **higher-weighted numbers more often**

---

### 🧠 **Key Idea (How to Make It Work)**
We need a smart way to randomly pick a number, but still follow the weights.
Let’s say:
```
weights = [1, 3, 2]
```
Means:
* 1 ticket for index 0
* 3 tickets for index 1
* 2 tickets for index 2
We turn it into something like this:
```
Prefix Sum: [1, 4, 6]
```
Here’s what it means:
* 0 is picked if random number is in \[1]
* 1 is picked if random number is in \[2, 3, 4]
* 2 is picked if random number is in \[5, 6]
Now we:
1. Generate a random number from 1 to 6
2. Find which range it falls in
3. Return that index!

That’s it! 🎉

---

### 🧪 Example Walkthrough

Let’s say:

```python
weights = [1, 3, 2]
```
Create prefix sum:
```
prefix = [1, 4, 6]
```
Generate a random number between 1 and 6 (say `r = 3`)
Now find the first prefix that is **≥ r**:
* 1 < 3 → skip index 0
* 4 ≥ 3 → pick index 1 ✅
So, we return `1`

---

---

### 🔍 Summary

* You build a "cumulative weight list" (prefix sum)
* Use random to pick a number in that total range
* Use binary search to find which index to return
*/

class Solution {
    vector<int> prefixSums;
public:
    Solution(vector<int> &w) {
        for (auto n : w)
            prefixSums.push_back(n + (prefixSums.empty() ? 
                0 : prefixSums.back()));
    }

    int pickIndex() {
        // generate a random number in the range of [0, 1]
        float randNum = (float) rand() / RAND_MAX;
        float target =  randNum * prefixSums.back();
        // run a linear search to find the target zone
        for (int i = 0; i < prefixSums.size(); ++i)
            if (target < prefixSums[i])
                return i;
        return prefixSums.size() - 1;
    }
};
/*
Complexity Analysis
Let N be the length of the input list.

Time Complexity
For the constructor function, the time complexity would be O(N), which is due to the construction of the prefix sums.
For the pickIndex() function, its time complexity would be O(N) as well, since we did a linear search on the prefix sums.
Space Complexity
For the constructor function, the space complexity would be O(N), which is again due to the construction of the prefix sums.
For the pickIndex() function, its space complexity would be O(1), since it uses constant memory. Note, here we consider the prefix sums that it operates on, as the input of the function.*/

//Approach 2: Prefix Sums with Binary Search

class Solution {
    vector<int> prefixSums;

public:
    Solution(vector<int> &w) {
        for (auto n : w)
            prefixSums.push_back(n + (prefixSums.empty() ? 
                0 : prefixSums.back()));
    }
    int pickIndex() {
        // generate a random number in the range of [0, 1]
        float randNum = (float) rand() / RAND_MAX;
        float target =  randNum * prefixSums.back();
        return lower_bound(begin(prefixSums), end(prefixSums), target) - begin(prefixSums);
    }
};

/*Complexity Analysis
Let N be the length of the input list.
Time Complexity
For the constructor function, the time complexity would be O(N), which is due to the construction of the prefix sums.
For the pickIndex() function, this time its time complexity would be O(logN), since we did a binary search on the prefix sums.
Space Complexity
For the constructor function, the space complexity remains O(N), which is again due to the construction of the prefix sums.
For the pickIndex() function, its space complexity would be O(1), since it uses constant memory. Note, here we consider the prefix sums that it operates on, as the input of the function.*/


