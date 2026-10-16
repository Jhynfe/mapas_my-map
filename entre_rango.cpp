#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename data_type>
struct AVL {
    struct TreeNode {
        int height;
        int size;
        data_type data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(data_type data = data_type(), int height = 0, int size = 1, TreeNode* left = nullptr, TreeNode* right = nullptr)
            : data(data), height(height), size(size), left(left), right(right) {}
    };

    TreeNode* root;

    AVL() { root = nullptr; }

    int h(TreeNode* u) { return u == nullptr ? -1 : u->height; }
    int sz(TreeNode* u) { return u == nullptr ? 0 : u->size; }
    int FB(TreeNode* u) { return h(u->left) - h(u->right); }

    void update(TreeNode* u) {
        if (u != nullptr) {
            u->height = 1 + max(h(u->left), h(u->right));
            u->size = 1 + sz(u->left) + sz(u->right);
        }
    }

    TreeNode* rotate_left(TreeNode* u) {
        TreeNode* v = u->right;
        u->right = v->left;
        v->left = u;
        update(u);
        update(v);
        return v;
    }

    TreeNode* rotate_right(TreeNode* u) {
        TreeNode* v = u->left;
        u->left = v->right;
        v->right = u;
        update(u);
        update(v);
        return v;
    }

    TreeNode* rebalance(TreeNode* u) {
        update(u);
        if (FB(u) > 1) {
            if (FB(u->left) < 0) {
                u->left = rotate_left(u->left);
            }
            return rotate_right(u);
        }
        if (FB(u) < -1) {
            if (FB(u->right) > 0) {
                u->right = rotate_right(u->right);
            }
            return rotate_left(u);
        }
        return u;
    }

    TreeNode* insert(TreeNode* u, data_type value) {
        if (u == nullptr) return new TreeNode(value, 0, 1);
        if (value < u->data) {
            u->left = insert(u->left, value);
        } else {
            u->right = insert(u->right, value);
        }
        return rebalance(u);
    }

    void insert(data_type value) { root = insert(root, value); }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current->left != nullptr) current = current->left;
        return current;
    }

    TreeNode* erase(TreeNode* u, data_type value) {
        if (u == nullptr) return nullptr;
        if (value < u->data) {
            u->left = erase(u->left, value);
        } else if (value > u->data) {
            u->right = erase(u->right, value);
        } else {
            if (u->left == nullptr || u->right == nullptr) {
                TreeNode* temp = u->left ? u->left : u->right;
                if (temp == nullptr) {
                    temp = u;
                    u = nullptr;
                } else {
                    *u = *temp;
                }
                delete temp;
            } else {
                TreeNode* temp = min_element(u->right);
                u->data = temp->data;
                u->right = erase(u->right, temp->data);
            }
        }
        if (u == nullptr) return nullptr;
        return rebalance(u);
    }

    void erase(data_type value) { root = erase(root, value); }

    data_type find_kth(TreeNode* u, int k) {
        int left_sz = sz(u->left);
        if (k <= left_sz) {
            return find_kth(u->left, k);
        } else if (k == left_sz + 1) {
            return u->data;
        } else {
            return find_kth(u->right, k - left_sz - 1);
        }
    }

    data_type get_kth(int k) {
        return find_kth(root, k);
    }
    data_type get_kth_mayor(int k) {
        int n = sz(root);
        return find_kth(root, n - k + 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    if (!(cin >> q)) return 0;

    AVL<int> avl;

    while (q--) {
        int tipo, x;
        cin >> tipo >> x;
        if (tipo == 1) {
            avl.insert(x);
        } else if (tipo == 2) {
            avl.erase(x);
        } else if (tipo == 3) {
            cout << avl.get_kth(x) << '\n';
        }
    }
    return 0;
}
