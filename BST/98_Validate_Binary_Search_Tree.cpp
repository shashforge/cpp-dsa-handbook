/*Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
*/

//  C++17
bool isBST(TreeNode *node,
           std::optional<int> lo = std::nullopt,
           std::optional<int> hi = std::nullopt)
{
    if (!node) return true;

    if ( (lo && node->val <= *lo) || (hi && node->val >= *hi) )
        return false;                         // violates the invariant

    return  isBST(node->left , lo,            std::optional<int>{node->val}) &&
            isBST(node->right, std::optional<int>{node->val}, hi);
}

//  C++20
#include <ranges>

bool isBST(TreeNode *root)
{
    // collect in-order traversal
    std::vector<int> inorder;
    auto dfs = [&](auto &&self, TreeNode *n) -> void {
        if (!n) return;
        self(self, n->left);
        inorder.push_back(n->val);
        self(self, n->right);
    };
    dfs(dfs, root);

    // view that compares each pair; short-circuits on first failure
    auto strictly_increasing =
        std::views::iota(size_t{1}, inorder.size()) |
        std::views::all_of([&](size_t i){ return inorder[i-1] < inorder[i]; });

    return strictly_increasing;
}

//  C++23
#include <generator>
#include <ranges>

std::generator<int> inorder(TreeNode *n)
{
    if (!n) co_return;
    for (int v : inorder(n->left))  co_yield v;
    co_yield n->val;
    for (int v : inorder(n->right)) co_yield v;
}

bool isBST(TreeNode *root)
{
    int               prev;           // uninitialised on purpose
    bool              first = true;

    for (int v : inorder(root)) {     // lazy stream of keys
        if (!first && v <= prev) return false;
        prev  = v;
        first = false;
    }
    return true;
}


//isBST in O(1) space (C++17 and later)
bool isBST(TreeNode *root)
{
    TreeNode *curr = root;
    long long prev_val = LLONG_MIN;   // sentinel below any int
    bool first = true;                // skip the sentinel for the first node

    while (curr)
    {
        if (curr->left == nullptr) {
            // Visit node
            if (!first && curr->val <= prev_val) return false;
            first = false; prev_val = curr->val;

            curr = curr->right;
        } else {
            // Find predecessor
            TreeNode *pred = curr->left;
            while (pred->right && pred->right != curr)
                pred = pred->right;

            if (pred->right == nullptr) {
                pred->right = curr;          // create thread
                curr = curr->left;
            } else {
                pred->right = nullptr;       // remove thread

                // Visit node
                if (curr->val <= prev_val) return false;
                prev_val = curr->val;

                curr = curr->right;
            }
        }
    }
    return true;
}

