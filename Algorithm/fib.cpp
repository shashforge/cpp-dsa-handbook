#include <iostream>
#include <stdexcept>
#include <format>       // C++20/23 formatting library

/**
 * Compute the n-th Fibonacci number.
 *
 * C++23 features used:
 *  - constexpr with loops (C++20)
 *  - if consteval (C++23) to split compile vs runtime logic
 *  - [[likely]] attribute on the fast path
 *  - [[nodiscard]] to catch ignored return values
 *  - std::format for cleaner I/O
 */
[[nodiscard]] constexpr int fib(int n) {
    if (n < 0) {
        throw std::invalid_argument("n must be non-negative");
    }

    // At compile time: use straightforward recursion
    if consteval {
        return (n <= 1) ? n : fib(n - 1) + fib(n - 2);
    }
    // At runtime: use O(n) bottom-up loop for speed
    if (n <= 1) [[likely]] {
        return n;
    }
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int next = a + b;
        a = b;
        b = next;
    }
    return b;
}

int main() {
    std::cout << "Enter a non-negative integer n: ";

    int n;
    if (!(std::cin >> n)) {
        std::cerr << "Error: invalid input. Please enter an integer.\n";
        return 1;
    }

    try {
        // Example of compile-time eval:
        static_assert(fib(10) == 55, "Compile-time check");

        int result = fib(n);
        // std::format is part of C++20/23
        std::cout << std::format("Fib({}) = {}\n", n, result);
    } catch (const std::invalid_argument& e) {
        std::cerr << std::format("Error: {}\n", e.what());
        return 1;
    }

    return 0;
}
