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
//        std::queue<TreeNode*> q;
//        std::vector<std::vector<int>> v;
//        void pathSumRecursive(std::vector<int> & currentPath, const int sumSoFar, const int targetSum) {
//            if (!q.empty()) {
//                auto node = q.front();
//                curre
//            }
//        }
//
//        std::vector<std::vector<int>> pathSum(TreeNode* root, const int targetSum) {
//            int sumSoFar = root->val;
//            if (root->left) q.push(root->left.get());
//            if (root->right) q.push(root->right.get());
//            std::vector<int> activePath;
//            activePath.push_back(root->val);
//            pathSumRecursive(activePath, sumSoFar, targetSum);
//            return v;
//        }

//        std::vector<std::vector<int>> pathSum(TreeNode* root, const int targetSum) {
//            std::queue<TreeNode*> q;
//            std::vector<std::vector<int>> v;
//            std::vector<
//            q.push(root);
//            int sumSoFar = 0;
//            while(!q.empty()) {
//                auto node = q.front();
//                sumSoFar = node->val;
//                if (node->left) q.push(node->left.get());
//                if (node->right) q.push(node->right.get());
//                q.pop();
//            }
//            return v;
//        }

        std::vector<std::vector<int>> v;

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
    void printdelim( const char c = ',') { std::clog << c; }

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
