#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }

    return b;
}

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} Node;

Node *createNode(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node *insert(Node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }

    if (data > root->data)
    {
        root->right = insert(root->right, data);
    }

    return root;
}

int calculateHeight(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int left = calculateHeight(root->left);
    int right = calculateHeight(root->right);
    return max(left, right) + 1;
}

int height(Node *root, int data)
{
    if (root == NULL)
    {
        return -1; // Node not found
    }

    if (root->data == data)
    {
        return calculateHeight(root);
    }

    if (data < root->data)
    {
        return height(root->left, data);
    }
    else
    {
        return height(root->right, data);
    }
}

int main(void)
{

    Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 12);
    root = insert(root, 16);

    printf("Height of the node 10: %d\n", height(root, 10));
    printf("Height of the node 3: %d\n", height(root, 3));
    return 0;
}