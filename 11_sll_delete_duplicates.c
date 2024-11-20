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

Node *insertSorted(Node *head, int data)
{
    Node *new_node = createNode(data);

    if (head == NULL)
    {
        return new_node;
    }

    Node *curr = head;
    while (curr->next != NULL)
    {
        if (curr->next->data > data)
        {
            Node *temp = curr->next;
            curr->next = new_node;
            new_node->next = temp;
            return head;
        }

        curr = curr->next;
    }

    curr->next = new_node;
    return head;
}

void display(Node *head)
{
    Node *curr = head;
    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

Node *deleteDuplicates(Node *head)
{
    Node *curr = head;
    while (curr != NULL && curr->next != NULL)
    {
        while (curr->data == curr->next->data)
        {
            Node *temp = curr->next;
            curr->next = curr->next->next;
            free(temp);
        }

        curr = curr->next;
    }

    return head;
}

int main(void)
{

    Node *head = NULL;
    head = insertSorted(head, 1);
    head = insertSorted(head, 1);
    head = insertSorted(head, 2);
    head = insertSorted(head, 2);
    head = insertSorted(head, 3);
    head = insertSorted(head, 4);
    head = insertSorted(head, 4);
    head = insertSorted(head, 4);
    head = insertSorted(head, 5);
    head = insertSorted(head, 6);
    printf("Before deleting duplicates\n");
    display(head);

    head = deleteDuplicates(head);

    printf("After deleting duplicates\n");
    display(head);
    return 0;
}