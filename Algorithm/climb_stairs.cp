// O(n) time, O(1) space
long long climbWays(int n) {
    if (n < 0) return 0;
    if (n <= 1) return 1;
    long long a = 1;   // ways[0]
    long long b = 1;   // ways[1]
    for (int i = 2; i <= n; ++i) {
        long long next = a + b;  // ways[i] = ways[i-1] + ways[i-2]
        a = b;
        b = next;
    }
    return b;  // ways[n]
}
