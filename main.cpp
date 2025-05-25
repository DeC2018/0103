#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <sstream>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (root == nullptr)
      return {};

    vector<vector<int>> ans;
    deque<TreeNode*> q{{root}};
    bool isLeftToRight = true;

    while (!q.empty()) {
      vector<int> currLevel;
      for (int sz = q.size(); sz > 0; --sz)
        if (isLeftToRight) {
          TreeNode* node = q.front();
          q.pop_front();
          currLevel.push_back(node->val);
          if (node->left)
            q.push_back(node->left);
          if (node->right)
            q.push_back(node->right);
        } else {
          TreeNode* node = q.back();
          q.pop_back();
          currLevel.push_back(node->val);
          if (node->right)
            q.push_front(node->right);
          if (node->left)
            q.push_front(node->left);
        }
      ans.push_back(currLevel);
      isLeftToRight = !isLeftToRight;
    }

    return ans;
  }
};

// Helper to build tree from level-order vector
TreeNode* buildTree(const vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") return nullptr;
    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* curr = q.front(); q.pop();
        if (i < nodes.size() && nodes[i] != "null") {
            curr->left = new TreeNode(stoi(nodes[i]));
            q.push(curr->left);
        }
        ++i;
        if (i < nodes.size() && nodes[i] != "null") {
            curr->right = new TreeNode(stoi(nodes[i]));
            q.push(curr->right);
        }
        ++i;
    }
    return root;
}

// Helper to parse input string like "[3,9,20,null,null,15,7]" to vector<string>
vector<string> parseInput(const string& s) {
    vector<string> res;
    int n = s.size();
    int i = 0;
    while (i < n && (s[i] == ' ' || s[i] == '[')) ++i;
    string curr;
    for (; i < n; ++i) {
        if (s[i] == ',' || s[i] == ']') {
            if (!curr.empty()) {
                res.push_back(curr);
                curr.clear();
            }
        } else if (s[i] != ' ') {
            curr += s[i];
        }
    }
    if (!curr.empty()) res.push_back(curr);
    return res;
}

// Helper to print output in required format
void printOutput(const vector<vector<int>>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < v[i].size(); ++j) {
            cout << v[i][j];
            if (j + 1 < v[i].size()) cout << ",";
        }
        cout << "]";
        if (i + 1 < v.size()) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    vector<string> inputs = {
        "[3,9,20,null,null,15,7]",
        "[1]",
        "[]"
    };
    for (const string& input : inputs) {
        cout << "Input: root = " << input << endl;
        vector<string> nodes = parseInput(input);
        TreeNode* root = buildTree(nodes);
        Solution sol;
        vector<vector<int>> res = sol.zigzagLevelOrder(root);
        cout << "Output: ";
        printOutput(res);
    }
    return 0;
}
