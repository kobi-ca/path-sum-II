#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <queue>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
namespace {
    struct TreeNode final {
        int val{};
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode>  right;
        TreeNode()  = default;
        explicit TreeNode(int x) : val(x) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
        friend std::ostream& operator<< (std::ostream& os, const TreeNode& tn) {
            os << tn.val;
            return os;
        }
    };

    class Solution {
    public:
        // Final results to return
        std::vector<std::vector<int>> v;

        /**
         * each stack has the state of the subtree and it carries the current vector
         * so when we wind down, we will see the std::vector<int> of this stack, and we will see
         * sumSoFar up to this node.
         * when we are in a leaf, we hit the if sum == target and if this is true, we add the current
         * path to the list of paths
         */
        void pathSumRecursive(TreeNode* node, const int targetSum, int sumSoFar, std::vector<int> current) {
            sumSoFar += node->val;
            current.push_back(node->val);

            if (node->left) {
                pathSumRecursive(node->left.get(), targetSum, sumSoFar, current);
            }
            if (node->right) {
                pathSumRecursive(node->right.get(), targetSum, sumSoFar, current);
            }
            if (sumSoFar == targetSum) {
                v.push_back(current);
            }
        }

        std::vector<std::vector<int>> pathSum(TreeNode* root, const int targetSum) {
            std::vector<int> current;
            pathSumRecursive(root, targetSum, 0, {});
            return v;
        }

    };

    void println() { std::clog << '\n'; }

    /**
     * it is guaranteed that we have a root and then pairs
     * We use shared_ptr to move things around easily and have the ability to delete.
     * we start with root. push it to queue.
     * we loop as long as we have something in queue and something in the array/init list.
     * we pick up the next in queue and pick up the next pair in the init list.
     * By definition, the pair are the childs of this node.
     * so we concatenate it if the childs are not nullptrs.
     * If they are not nullptrs, we push them to the queue since their child
     * will be next from the init list and we need to deal with them soon.
     * at each iteration we advance the iter pointer in 2 locations because it is pair each time.
     * and we pop the one the we visited from the queue.
     */
    auto make_tree2(std::initializer_list<std::optional<int>> l) {
        auto iter = l.begin(); // root - assume root is there
        auto iter_unwrap = *iter;
        auto node = std::make_shared<TreeNode>(*iter_unwrap);
        auto root = node;
        std::queue<std::shared_ptr<TreeNode>> q;
        q.push(node);
        auto iter_opt = std::next(iter);
        while (!q.empty() && iter_opt != l.end()) {
            node = q.front();
            auto left_iter = iter_opt;
            auto right_iter = std::next(iter_opt);
            if (auto opt = *left_iter; opt) {
                node->left = std::make_shared<TreeNode>(*opt);
            }
            if (auto opt = *right_iter; opt) {
                node->right = std::make_shared<TreeNode>(*opt);
            }
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
            std::advance(iter_opt, 2);
            q.pop();
        }
        return root;
    }

}

int main() {
    auto root = make_tree2({5, 4, 8, 11, std::nullopt, 13, 4, 7, 2, std::nullopt, std::nullopt, 5, 1});
    constexpr auto targetSum = 22;
    Solution s;
    auto vec = s.pathSum(root.get(), targetSum);
    for(const auto& outer : vec) {
        for(auto inner : outer) {
            std::clog << inner << ',';
        }
        println();
    }
    return 0;
}
