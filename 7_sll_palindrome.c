#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char data;
    struct node *next;
} Node;

Node *createNode(char data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node *addEnd(Node *head, char data)
{
    Node *new_node = createNode(data);

    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = new_node;
    return head;
}

int isPalindrome(Node *head)
{
    Node *fast = head;
    Node *slow = head;

    // find middle (slow)
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next;
        fast = fast->next;
        slow = slow->next;
    }

    // reverse second half
    Node *prev = NULL;
    while (slow != NULL)
    {
        Node *tmp = slow->next;
        slow->next = prev;
        prev = slow;
        slow = tmp;
    }

    Node *left = head;
    Node *right = prev; // Slow is at null
    while (right != NULL)
    {
        if (left->data != right->data)
        {
            return 0;
        }

        left = left->next;
        right = right->next;
    }

    return 1;
}

int main(void)
{
    Node *head = createNode('a');
    addEnd(head, 'b');
    addEnd(head, 'a');
    addEnd(head, 'a');
    printf("%d", isPalindrome(head));
    return 0;
}