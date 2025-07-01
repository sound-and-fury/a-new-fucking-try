#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct QueueNode
{
    TreeNode* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct
{
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* createQueue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isQueueEmpty(Queue* q)
{
    return q->front == NULL;
}

int queueSize(Queue* q)
{
    int size = 0;
    QueueNode* temp = q->front;
    while (temp)
    {
        size++;
        temp = temp->next;
    }
    return size;
}
void enqueue(Queue* q, TreeNode* node)
{
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = node;
    newNode->next = NULL;
    if (q->rear)
    {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    if (!q->front)
    {
        q->front = newNode   ;
    }
}

TreeNode* dequeue(Queue* q)
{
    if (!q->front)
    {
        return NULL;
    }
    QueueNode* temp = q->front;
    TreeNode* node = temp->treeNode;
    q->front = q->front->next;
    if (!q->front)
    {
        q->rear = NULL;
    }
    free(temp);
    return node;
}

TreeNode* createTree()
{
    char data;
    scanf(" %c", &data);
    if (data == '#')
    {
        return NULL;
    }
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = createTree();
    node->right = createTree();
    return node;
}

int maxWidth(TreeNode* root)
{
    if (!root) return 0;
    Queue* q = createQueue();
    enqueue(q, root);
    int maxW = 0;
    while (!isQueueEmpty(q))
        {
        int levelSize = queueSize(q);
        int count = levelSize;
        while (count > 0)
        {
            TreeNode* node = dequeue(q);
            if (node->left) enqueue(q, node->left);
            if (node->right) enqueue(q, node->right);
            count--;
        }
        if (levelSize > maxW)
        {
            maxW = levelSize;
        }
    }
    return maxW;
}

int main()
{
    TreeNode* root = createTree();
    printf("%d\n", maxWidth(root));
    return 0;
}
