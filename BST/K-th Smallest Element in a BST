/*230 Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) of all the values of the nodes in the tree.
Input: root = [3,1,4,null,2], k = 1
Output: 1

Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3
*/

// C++17 — simple recursive counter  O(H) space
int kthSmallest(TreeNode *root, int k)
{
    int answer = -1;                   // placeholder
    std::function<void(TreeNode*)> dfs = [&](TreeNode *node)
    {
        if (!node || k == 0) return;

        dfs(node->left);

        if (--k == 0) {                // visit node
            answer = node->val;
            return;
        }
        dfs(node->right);
    };
    dfs(root);
    return answer;
}


//C++20 — ranges pipeline  O(N) space
#include <ranges>

int kthSmallest(TreeNode *root, int k)
{
    std::vector<int> inorder;          // collect keys
    auto dfs = [&](auto &&self, TreeNode *n) -> void {
        if (!n) return;
        self(self, n->left);
        inorder.push_back(n->val);
        self(self, n->right);
    };
    dfs(dfs, root);

    return inorder
         | std::views::take(k)         // first k keys
         | std::views::common          // get iterator pair
         | std::views::all             // turn into range
         | std::ranges::to<std::vector>()    // materialise
         .back();                      // last of the k elements
}

//C++23 — coroutine generator  O(H) space, stops early
#include <generator>

std::generator<int> inorder(TreeNode *n)
{
    if (!n) co_return;
    for (int v : inorder(n->left))  co_yield v;
    co_yield n->val;
    for (int v : inorder(n->right)) co_yield v;
}

int kthSmallest(TreeNode *root, int k)
{
    for (int v : inorder(root))
        if (--k == 0) return v;
    throw std::out_of_range("k larger than tree size");
}


//C++17 Morris traversal — O(1) extra space
int kthSmallest(TreeNode *root, int k)
{
    TreeNode *curr = root;
    while (curr)
    {
        if (!curr->left) {                     // Case 1: no left child
            if (--k == 0) return curr->val;
            curr = curr->right;
        } else {                               // Case 2: has left child
            TreeNode *pred = curr->left;
            while (pred->right && pred->right != curr)
                pred = pred->right;

            if (!pred->right) {                // create thread
                pred->right = curr;
                curr = curr->left;
            } else {                           // thread exists ⇒ subtree done
                pred->right = nullptr;         // restore
                if (--k == 0) return curr->val;
                curr = curr->right;
            }
        }
    }
    throw std::out_of_range("k larger than tree size");
}

