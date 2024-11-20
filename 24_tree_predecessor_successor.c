#include <stdio.h>
#include <stdlib.h>

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

int predecessor(Node *root, int data)
{
    Node *curr = root;
    Node *predecessor = NULL;

    while (curr != NULL)
    {
        if (curr->data < data)
        {
            predecessor = curr;
            curr = curr->right;
        }
        else if (curr->data > data)
        {
            curr = curr->left;
        }
        else
        {
            if (curr->left != NULL)
            {
                predecessor = curr->left;
                while (predecessor->right != NULL)
                {
                    predecessor = predecessor->right;
                }
                break;
            }
        }
    }

    if (predecessor == NULL)
    {
        printf("No predecessor found\n");
    }
    else
    {
        printf("%d\n", predecessor->data);
        return predecessor->data;
    }
}

int successor(Node *root, int data)
{
    Node *curr = root;
    Node *successor = NULL;

    while (curr != NULL)
    {
        if (curr->data > data)
        {
            successor = curr;
            curr = curr->left;
        }
        else if (curr->data < data)
        {
            curr = curr->right;
        }
        else
        {
            if (curr->right != NULL)
            {
                successor = curr->right;
                while (successor->left != NULL)
                {
                    successor = successor->left;
                }
                break;
            }
        }
    }

    if (successor == NULL)
    {
        printf("No successor found\n");
    }
    else
    {
        printf("%d\n", successor->data);
        return successor->data;
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
    predecessor(root, 10);
    successor(root, 10);
    return 0;
}