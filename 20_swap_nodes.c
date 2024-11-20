#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

Node *createNode(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node *insertEnd(Node *head, int data)
{
    Node *new_node = createNode(data);

    if (head == NULL)
    {
        return new_node;
    }

    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = new_node;
    return head;
}

void display(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

Node *swapNodes(Node *head)
{
    Node *dummy = createNode(0);
    dummy->next = head;
    Node *prev = dummy;
    Node *curr = head;

    while (curr != NULL && curr->next != NULL)
    {
        // save ptr
        Node *nextPair = curr->next->next;
        Node *second = curr->next;

        // Reverse curr pair
        second->next = curr;
        curr->next = nextPair;
        prev->next = second;

        prev = curr;
        curr = nextPair;
    }

    return dummy->next;
}

int main(void)
{
    Node *head = NULL;
    head = insertEnd(head, 1);
    head = insertEnd(head, 2);
    head = insertEnd(head, 3);
    head = insertEnd(head, 4);
    display(head);

    head = swapNodes(head);
    display(head);
    return 0;
}