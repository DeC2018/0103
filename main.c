#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 1000

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Helper function to create a new tree node
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper to parse input string like "[3,9,20,null,null,15,7]" to array
int parseInput(const char* s, char arr[][16], int* n) {
    int i = 0, j = 0, k = 0;
    while (s[i] && (s[i] == ' ' || s[i] == '[')) ++i;
    while (s[i] && s[i] != ']') {
        if (s[i] == ',') {
            arr[k][j] = '\0';
            ++k; j = 0;
        } else if (s[i] != ' ') {
            arr[k][j++] = s[i];
        }
        ++i;
    }
    if (j > 0) {
        arr[k][j] = '\0';
        ++k;
    }
    *n = k;
    return k;
}

// Helper to build tree from level-order array
struct TreeNode* buildTree(char arr[][16], int n) {
    if (n == 0 || strcmp(arr[0], "null") == 0) return NULL;
    struct TreeNode** nodes = (struct TreeNode**)malloc(n * sizeof(struct TreeNode*));
    for (int i = 0; i < n; ++i) nodes[i] = NULL;
    struct TreeNode* root = newNode(atoi(arr[0]));
    nodes[0] = root;
    int pos = 1;
    for (int i = 0; i < n && pos < n; ++i) {
        if (!nodes[i]) continue;
        if (pos < n && strcmp(arr[pos], "null") != 0) {
            nodes[i]->left = newNode(atoi(arr[pos]));
            nodes[pos] = nodes[i]->left;
        }
        ++pos;
        if (pos < n && strcmp(arr[pos], "null") != 0) {
            nodes[i]->right = newNode(atoi(arr[pos]));
            nodes[pos] = nodes[i]->right;
        }
        ++pos;
    }
    free(nodes);
    return root;
}

// Zigzag level order traversal
int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    if (!root) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    int capacity = 1024;
    int** result = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));
    *returnSize = 0;
    int queueCapacity = 1024;
    struct TreeNode** queue = (struct TreeNode**)malloc(queueCapacity * sizeof(struct TreeNode*));
    int front = 0, rear = 0;
    queue[rear++] = root;
    int leftToRight = 1;
    while (front < rear) {
        int levelSize = rear - front;
        int* level = (int*)malloc(levelSize * sizeof(int));
        for (int i = 0; i < levelSize; ++i) {
            struct TreeNode* node = queue[front++];
            int index = leftToRight ? i : (levelSize - 1 - i);
            level[index] = node->val;
            if (node->left) {
                if (rear >= queueCapacity) {
                    queueCapacity *= 2;
                    queue = (struct TreeNode**)realloc(queue, queueCapacity * sizeof(struct TreeNode*));
                }
                queue[rear++] = node->left;
            }
            if (node->right) {
                if (rear >= queueCapacity) {
                    queueCapacity *= 2;
                    queue = (struct TreeNode**)realloc(queue, queueCapacity * sizeof(struct TreeNode*));
                }
                queue[rear++] = node->right;
            }
        }
        result[*returnSize] = level;
        (*returnColumnSizes)[*returnSize] = levelSize;
        (*returnSize)++;
        if (*returnSize >= capacity) {
            capacity *= 2;
            result = (int**)realloc(result, capacity * sizeof(int*));
            *returnColumnSizes = (int*)realloc(*returnColumnSizes, capacity * sizeof(int));
        }
        leftToRight = !leftToRight;
    }
    free(queue);
    return result;
}

// Helper to print output in required format
void printOutput(int** v, int returnSize, int* returnColumnSizes) {
    printf("[");
    for (int i = 0; i < returnSize; ++i) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; ++j) {
            printf("%d", v[i][j]);
            if (j + 1 < returnColumnSizes[i]) printf(",");
        }
        printf("]");
        if (i + 1 < returnSize) printf(",");
    }
    printf("]\n");
}

// Free the tree
void freeTree(struct TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    const char* inputs[] = {
        "[3,9,20,null,null,15,7]",
        "[1]",
        "[]"
    };
    int numInputs = sizeof(inputs) / sizeof(inputs[0]);
    for (int t = 0; t < numInputs; ++t) {
        printf("Input: root = %s\n", inputs[t]);
        char arr[MAX_NODES][16];
        int n = 0;
        parseInput(inputs[t], arr, &n);
        struct TreeNode* root = buildTree(arr, n);
        int returnSize = 0;
        int* returnColumnSizes = NULL;
        int** res = zigzagLevelOrder(root, &returnSize, &returnColumnSizes);
        printf("Output: ");
        printOutput(res, returnSize, returnColumnSizes);
        for (int i = 0; i < returnSize; ++i) free(res[i]);
        free(res);
        free(returnColumnSizes);
        freeTree(root);
    }
    return 0;
}
