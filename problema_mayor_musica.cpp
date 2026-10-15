#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct Song {
    int votos;
    int id;

    bool operator<(const Song& other) const {
        if (votos != other.votos) {
            return votos > other.votos;
        }
        return id < other.id; 
    }

    bool operator>(const Song& other) const {
        if (votos != other.votos) {
            return votos < other.votos;
        }
        return id > other.id;
    }

    bool operator==(const Song& other) const {
        return votos == other.votos && id == other.id;
    }
};

template<typename data_type>
struct AVL {
    struct TreeNode {
        int height;
        data_type data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(data_type data = data_type(), int height = 0, TreeNode* left = nullptr, TreeNode* right = nullptr)
            : data(data), height(height), left(left), right(right) {}
    };

    TreeNode* root;

    AVL() { root = nullptr; }

    void update(TreeNode* u) {
        u->height = 1 + max(h(u->left), h(u->right));
    }

    int h(TreeNode* u) { return u == nullptr ? -1 : u->height; }

    int FB(TreeNode* u) { return h(u->left) - h(u->right); }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    TreeNode* max_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    TreeNode* min_element() { return min_element(root); }
    TreeNode* max_element() { return max_element(root); }

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
        if (u == nullptr) return new TreeNode(value, 0);
        if (value < u->data) {
            u->left = insert(u->left, value);
        } else {
            u->right = insert(u->right, value);
        }
        return rebalance(u);
    }

    void insert(data_type value) { root = insert(root, value); }

    TreeNode* erase(TreeNode* u, data_type value) {
        if (u == nullptr) return nullptr;

        if (value < u->data) {
            u->left = erase(u->left, value);
        } else if (value > u->data) {
            u->right = erase(u->right, value);
        } else {
            // Nodo encontrado
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
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    if (!(cin >> q)) return 0;

    map<int, int> votos;
    AVL<Song> avl;

    while (q--) {
        int tipo;
        cin >> tipo;

        if (tipo == 1) {
            int x;
            cin >> x;
            int v_actual = votos[x];
            if (v_actual > 0) {
                avl.erase({v_actual, x}); 
            }
            votos[x]++;
            avl.insert({votos[x], x}); 
        }
        else if (tipo == 2) {
            int x;
            cin >> x;
            int v_actual = votos[x];
            avl.erase({v_actual, x});
            votos[x]--;
            if (votos[x] > 0) {
                avl.insert({votos[x], x});
            }
        }
        else if (tipo == 3) {
            auto ganador = avl.min_element()->data;
            cout << ganador.id << " " << ganador.votos << "\n";
        }
    }

    return 0;
}
