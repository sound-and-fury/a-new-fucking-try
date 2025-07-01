#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct TreeNode {
    char val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;


#define MAX_NODES 1000
typedef struct {
    TreeNode* data[MAX_NODES];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, TreeNode* node) {
    if ((q->rear + 1) % MAX_NODES == q->front) {
        printf("Queue overflow\n");
        exit(1);
    }
    q->data[q->rear] = node;
    q->rear = (q->rear + 1) % MAX_NODES;
}

TreeNode* dequeue(Queue *q) {
    if (isEmpty(q)) {
        return NULL;
    }
    TreeNode* node = q->data[q->front];
    q->front = (q->front + 1) % MAX_NODES;
    return node;
}


char nodes[MAX_NODES];
int index = 0;


TreeNode* buildTree() {
    if (nodes[index] == '\0') return NULL;
    if (nodes[index] == '#') {
        index++;
        return NULL;
    }
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = nodes[index++];
    root->left = buildTree();
    root->right = buildTree();
    return root;
}


int maxWidth(TreeNode* root) {
    if (!root) return 0;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    int maxWidth = 0;

    while (!isEmpty(&q)) {
        int size = (q.rear - q.front + MAX_NODES) % MAX_NODES;
        if (size > maxWidth) maxWidth = size;
        for (int i = 0; i < size; i++) {
            TreeNode* node = dequeue(&q);
            if (node->left) enqueue(&q, node->left);
            if (node->right) enqueue(&q, node->right);
        }
    }
    return maxWidth;
}

int main() {

    scanf("%s", nodes);
    index = 0;
    TreeNode* root = buildTree();
    int width = maxWidth(root);
    printf("%d\n", width);
    return 0;
}
