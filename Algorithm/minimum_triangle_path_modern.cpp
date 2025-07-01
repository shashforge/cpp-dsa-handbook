#include <iostream>
#include <vector>
#include <algorithm>    // std::minmax
#include <span>         // C++20: std::span
#include <format>       // C++20: std::format

using Row      = std::vector<int>;
using Triangle = std::vector<Row>;

/**
 * Compute the minimum path sum from top to bottom of a triangle.
 *
 * Utilizes:
 *  - C++17: [[nodiscard]], structured bindings, std::minmax
 *  - C++20: std::span, std::format
 */
[[nodiscard]] int minimumTotal(std::span<const Row> triangle) {
    size_t n = triangle.size();
    if (n == 0) return 0;

    std::vector<int> dp(triangle.back());

    for (int i = int(n) - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            auto [mn, mx] = std::minmax(dp[j], dp[j+1]);
            dp[j] = triangle[i][j] + mn;
        }
    }
    return dp[0];
}

int main() {
    std::vector<std::vector<int> > triangle{{2},
                               {3, 9},
                               {1, 6, 7}};

    int result = minimumTotal(triangle);
    std::cout << std::format("Minimum path sum: {}\n", result);
    return 0;
}
