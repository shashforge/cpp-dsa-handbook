// src/fib_last2.cpp

#include <iostream>
#include <string>
#include <string_view>
#include <ranges>      // C++20 ranges (for views)
#include <algorithm>   // ← add this so std::ranges::all_of compiles
#include <format>      // C++20 formatting
#include <iomanip>     // std::setw, std::setfill

//─── constants ────────────────────────────────────────────────────────────────
constexpr int MOD            = 100;   // C++17 inline constexpr
constexpr int PISANO_PERIOD  = 300;   // period of Fib(n) mod 100

//─── reduce huge N (as string) mod PISANO_PERIOD ──────────────────────────────
long long modString(std::string_view sv) {
    long long r = 0;
    // C++20 ranges: filter only digit characters
    for (char c : sv | std::views::filter([](char c){ return std::isdigit(c); })) {
        r = (r * 10 + (c - '0')) % PISANO_PERIOD;
    }
    return r;
}

//─── compute last two digits of F(N) ──────────────────────────────────────────
[[nodiscard]] int lastTwoDigitsFib(std::string_view n_str) {
    long long n = modString(n_str);
    if (n <= 1) [[unlikely]]    // C++20 branch hint
        return static_cast<int>(n);

    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int nxt = a + b;
        if (nxt >= MOD) nxt %= MOD;
        a = b;
        b = nxt;
    }
    return b;
}

int main() {
    std::string n_str;
    std::cout << "Enter a non-negative integer n: ";
    if (!(std::cin >> n_str)
     || !std::ranges::all_of(n_str, [](char c){ return std::isdigit(c); })) {
        std::cerr << "Invalid input. Please enter digits only.\n";
        return 1;
    }

    int result = lastTwoDigitsFib(n_str);
    // C++20 std::format with width specifier {:02}
    std::cout << std::format(
        "Last two digits of F({}) = {:02}\n",
        n_str, result
    );
    return 0;
}
