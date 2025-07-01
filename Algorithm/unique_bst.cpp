#include <iostream>
#include <vector>
#include <stdexcept>

/**
 * DP-based Catalan:
 *   C[0]=1, and for n>=1:
 *   C[n] = sum_{i=0..n-1} C[i]*C[n-1-i]
 * Time: O(n^2), Space: O(n)
 */
unsigned long long numUniqueBST_DP(int n) {
    if (n < 0) throw std::invalid_argument("n must be non-negative");
    std::vector<unsigned long long> C(n+1);
    C[0] = 1;
    for (int j = 1; j <= n; ++j) {
        unsigned long long sum = 0;
        for (int i = 0; i < j; ++i) {
            sum += C[i] * C[j-1-i];
        }
        C[j] = sum;
    }
    return C[n];
}

/**
 * Combinatorial Catalan:
 *   C_n = (1/(n+1)) * binomial(2n, n)
 * Compute binomial(2n,n) via multiplicative scheme to avoid overflow early.
 * Time: O(n), Space: O(1)
 */
unsigned long long numUniqueBST_Comb(int n) {
    if (n < 0) throw std::invalid_argument("n must be non-negative");
    // Compute binomial(2n, n) as product_{k=1..n} (n+k)/k
    long double res = 1.0L;
    for (int k = 1; k <= n; ++k) {
        res = res * (n + k) / k;
    }
    // divide by (n+1)
    res /= (n + 1);
    return static_cast<unsigned long long>(res + 0.5L);
}

int main() {
    std::cout << "Enter n (number of keys): ";
    int n;
    if (!(std::cin >> n) || n < 0) {
        std::cerr << "Invalid input. Please enter a non-negative integer.\n";
        return 1;
    }

    auto viaDP   = numUniqueBST_DP(n);
    auto viaComb = numUniqueBST_Comb(n);

    std::cout
        << "Number of unique BSTs with " << n << " keys:\n"
        << "  DP recurrence:          " << viaDP  << "\n"
        << "  Combinatorial formula:  " << viaComb << "\n";

    return 0;
}
