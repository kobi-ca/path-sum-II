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
        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode>  right;
        TreeNode()  = default;
        explicit TreeNode(int x) : val(x) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
        friend std::ostream& operator<< (std::ostream& os, const TreeNode& tn) {
            os << tn.val;
            return os;
        }
    };

    using uptr = std::unique_ptr<TreeNode>;

    class Solution {
    public:
        std::vector <std::vector<int>> pathSum(std::unique_ptr<TreeNode> root, int targetSum) {
            return {};
        }
    };

    uptr get_node(const auto opt) {
        if (opt) {
            auto node = std::make_unique<TreeNode>(*opt);
            std::clog << *opt << '\n';
            return std::move(node);
        } else {
            std::clog << "nullptr" << '\n';
            return nullptr;
        }
    }
    using vec_of_tn_pairs = std::vector<std::pair<uptr, uptr>>;
    vec_of_tn_pairs make_vector(std::initializer_list<std::optional<int>> l) {
        vec_of_tn_pairs vec_of_pairs;
        const auto beg = std::prev(rend(l));
        for(auto iter = rbegin(l) ; iter != rend(l);) {
            std::pair<uptr, uptr> p;
            {
                const auto opt = *iter;
                auto n = get_node(opt);
                if (iter == beg) {
                    std::clog << "found begin\n";
                    p.first = std::move(n);
                    vec_of_pairs.push_back(std::move(p));
                    break;
                } else {
                    p.second = std::move(n);
                }
            }
            {
                const auto opt = *(++iter);
                p.first = get_node(opt);
            }
            vec_of_pairs.push_back(std::move(p));
            ++iter;
        }
        return vec_of_pairs;
    }

    void print_item(const uptr& item) {
        if (item) {
            std::clog << *item;
        } else {
            std::clog << "null";
        }
    }

    void println() { std::clog << '\n'; }
    void printdelim( const char c = ',') { std::clog << c; }

    uptr construct_tree(vec_of_tn_pairs& vec) {
        std::clog << "\nconstruct tree\n";
        if (vec.empty()) {
            return {};
        }
        // first one is root which ->second can be ignored
        auto& [node, _] = vec[0];
        std::clog << node->val << '\n';
        std::queue<uptr> queue;
        for (auto&& iter = std::next(vec.begin()); iter != vec.end(); ++iter) {
            auto&& [item1, item2] = *iter;
            std::clog << "took: "; print_item(item1); printdelim() ; print_item(item2); println();

            if (!queue.empty()) {
                std::clog << "handling q\n";
                auto item = std::move(queue.front());
                std::clog << "item from q" << item->val << '\n';
                if (item1) {
                    item->left = std::move(item1);
                    std::clog << "pushing to q " << item1->val << '\n';
                    queue.push(std::move(item1));
                }
                if (item2) {
                    item->right = std::move(item2);
                    std::clog << "pushing to q " << item1->val << '\n';
                    queue.push(std::move(item2));
                }
                queue.pop();
                if (!queue.empty()) {
                    continue;
                }
            }

            std::clog << "after queue check\n";
            if (item1) {
                node->left = std::move(item1);
                queue.push(std::move(item1));
            }
            if (item2) {
                node->right = std::move(item2);
                queue.push(std::move(item2));
            }
        }
        return {};
    }

    void make_tree2(std::initializer_list<std::optional<int>> l) {
        auto iter = l.begin(); // root - assume root is there
        auto iter_unwrap = *iter;
        auto node = std::make_shared<TreeNode>(*iter_unwrap);
        std::queue<std::shared_ptr<TreeNode>> q;
        for(auto iter_opt = std::next(iter); iter_opt != l.end();) {
            if (auto opt = *iter_opt; opt) {
                std::clog << *opt << ' ';
            } else {
                std::clog << "nullptr" << ' ';
            }
            std::advance(iter_opt, 1);
            if (auto opt = *iter_opt; opt) {
                std::clog << *opt << '\n';
            } else {
                std::clog << "nullptr" << '\n';
            }
            std::advance(iter_opt, 1);
        }
    }

}

int main() {
//    auto tree = make_vector({5, 4, 8, 11, std::nullopt, 13, 4, 7, 2, std::nullopt, std::nullopt, 5, 1});
//    std::reverse(tree.begin(), tree.end());
//    std::clog << "\nprinting tree:\n";
//    for (const auto& [item1, item2] : tree) {
//        print_item(item1);
//        std::clog << ',';
//        print_item(item2);
//        std::clog << '\n';
//    }
//    const auto root = construct_tree(tree);

    make_tree2({5, 4, 8, 11, std::nullopt, 13, 4, 7, 2, std::nullopt, std::nullopt, 5, 1});
    return 0;
}
