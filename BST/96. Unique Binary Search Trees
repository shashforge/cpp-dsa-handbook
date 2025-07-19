/*

Given an integer n, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.
Input: n = 3
Output: 5
Example 2:

Input: n = 1
Output: 1


/////
Catalan
The first few values are

n : 0 1 2 3 4 5 6 7
f : 1 1 2 5 14 42 132 429
*/
//basic soln Time Complexity: O(2n) 
//Auxiliary Space: O(n)
int findCatalan(int n) {
    
    // Base case
    if (n <= 1)
        return 1;

    // catalan(n) is sum of
    // catalan(i)*catalan(n-i-1)
    int res = 0;
    for (int i = 0; i < n; i++)
        res += findCatalan(i) * findCatalan(n - i - 1);

    return res;
}
 //Bottom-up DP O(n²) time, O(n) space (C++17)
int numTrees(int n)
{
    std::vector<long long> dp(n + 1, 0);  // dp[k] = #BSTs on k keys
    dp[0] = dp[1] = 1;

    for (int nodes = 2; nodes <= n; ++nodes)
        for (int root = 1; root <= nodes; ++root)
            dp[nodes] += dp[root - 1] * dp[nodes - root];

    return static_cast<int>(dp[n]);
}
//Direct Catalan formula in O(n) time, O(1) extra space
long long numTrees(int n)          // beware 32-bit overflow
{
    long long c = 1;               // C_0
    for (int k = 0; k < n; ++k)
        c = c * 2 * (2*k + 1) / (k + 2);   // C_{k+1} from C_k
    return c;
}
