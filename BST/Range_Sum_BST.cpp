//Letcode 938. Range Sum of BST
/*Given the root node of a binary search tree and two integers low and high, return the sum of values of all nodes with a value in the inclusive range [low, high].
Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
Output: 32
Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.

Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
Output: 23
Explanation: Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.

*/

//C++17 – lightweight, modernised recursion
int rangeSumBST(TreeNode *root, int low, int high)
{
    if (!root) return 0;                         // nullptr is constexpr (since C++11)

    int sum = 0;
    if (root->val >= low && root->val <= high)   // pay only for nodes in range
        sum += root->val;

    if (root->val > low)                         // skip entire left or right sub-tree
        sum += rangeSumBST(root->left, low, high);

    if (root->val < high)
        sum += rangeSumBST(root->right, low, high);

    return sum;                                  // tail recursion, optimised by all major compilers
}


//C++20 – ranges & views (eager traversal, lazy filtering)

#include <ranges>
#include <numeric>      // std::accumulate

int rangeSumBST(TreeNode *root, int low, int high)
{
    // Standard depth-first traversal that just collects values.
    std::vector<int> in_order;
    auto dfs = [&](auto &&self, TreeNode *node) -> void {
        if (!node) return;
        self(self, node->left);
        in_order.push_back(node->val);
        self(self, node->right);
    };
    dfs(dfs, root);

    // Lazy filter view + accumulate
    auto in_range = in_order
                  | std::views::filter([&](int v){ return low <= v && v <= high; });

    return std::accumulate(begin(in_range), end(in_range), 0);
}
/*
What’s new in C++20?

std::ranges / std::views::filter – build a view that filters on-the-fly, no copies.

Immediately-invoked recursive lambda (dfs) with a template parameter (auto &&self) instead of std::function, eliminating heap allocations.

The rest of the algorithm stays unchanged, but the pipeline style makes intent obvious.
*/

//C++23 – coroutines + fold_left (fully lazy)
//  C++23
#include <generator>    // std::generator
#include <ranges>       // views, fold_left

// Lazily yield an in-order sequence of values
std::generator<int> inorder(TreeNode *node)
{
    if (!node) co_return;

    for (int v : inorder(node->left))  co_yield v;
    co_yield node->val;
    for (int v : inorder(node->right)) co_yield v;
}

int rangeSumBST(TreeNode *root, int low, int high)
{
    auto view = inorder(root)
              | std::views::filter([=](int v){ return low <= v && v <= high; });

    // C++23 fold_left works directly on a view
    return std::ranges::fold_left(view, 0, std::plus<>{});
}
/*
| Feature                      | Why it matters here                                                                   |
| ---------------------------- | ------------------------------------------------------------------------------------- |
| **`std::generator`** (P2502) | Coroutine that *lazily* visits each node, so no intermediate container is ever built. |
| **`std::ranges::fold_left`** | Reduces a range without the verbosity of `std::accumulate` (works directly on views). |
| **`views::filter`**          | Same as C++20, but now the whole pipeline stays lazy end-to-end.                      |*/
