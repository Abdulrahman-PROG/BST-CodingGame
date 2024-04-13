#include <bits/stdc++.h>
#define e "\n"
#define ll long long
#define FAST ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};



class BST {
private:
    Node* root;
    int width, height, n;
    vector<pair<int, int>> bombs;
    vector<pair<int, int>> goals;

    Node* insert(Node* node, int value, int x, int y) {
        if (node == nullptr) {
            if (isSafe(x, y)) {
                return new Node(value);
            }
            else {
                return nullptr;
            }
        }
        if (value < node->value) {
            node->left = insert(node->left, value, x - 1, y + 1);
        }
        else {
            node->right = insert(node->right, value, x + 1, y + 1);
        }
        return node;
    }

    // not a bomb or out of bounds ?
    bool isSafe(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height) return false;
        for (auto& bomb : bombs) {
            if (bomb.first == x && bomb.second == y) return false;
        }
        return true;
    }

    // all goals are reached ?
    bool checkGoals(Node* node, int x, int y) {
        if (node == nullptr) return true;
        for (auto& goal : goals) {
            if (goal.first == x && goal.second == y) {
                goals.erase(remove(goals.begin(), goals.end(), goal), goals.end());
            }
        }
        return checkGoals(node->left, x - 1, y + 1) && checkGoals(node->right, x + 1, y + 1);
    }

public:
    BST(int w, int h, int num, vector<pair<int, int>> b, vector<pair<int, int>> g)
        : root(nullptr), width(w), height(h), n(num), bombs(b), goals(g) {}

    void buildTree() {
        for (int i = 1; i <= n; ++i) {
            root = insert(root, i, (width - 1) / 2, 0);
            if (root == nullptr) {
                cout << "Lost,,,Bomb hit or out of bounds" << e;
                return;
            }
            if (goals.empty()) {
                cout << "Won,,,All goals reached" << e;
                return;
            }
        }
        if (!checkGoals(root, (width - 1) / 2, 0)) {
            cout << "Lost,,,Not all goals reached" << e;
        }
        else {
            cout << "Won,,,All goals reached" << e;
        }
    }
};

int main() {
    FAST;
    int width, height, n, bombsCount, goalsCount;
    cin >> width >> height >> n >> bombsCount >> goalsCount;
    vector<pair<int, int>> bombs(bombsCount), goals(goalsCount);
    for (int i = 0; i < bombsCount; ++i) {
        cin >> bombs[i].first >> bombs[i].second;
    }
    for (int i = 0; i < goalsCount; ++i) {
        cin >> goals[i].first >> goals[i].second;
    }
    BST tree(width, height, n, bombs, goals);
    tree.buildTree();
    return 0;
}
