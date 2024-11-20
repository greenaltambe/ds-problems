#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    int exponent;
    struct node *next;
} Node;

Node *createNode(int data, int exponent)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->exponent = exponent;
    new_node->next = NULL;
    return new_node;
}

Node *addSorted(Node *head, int data, int exponent)
{
    if (head == NULL || head->exponent < exponent)
    {
        Node *new_node = createNode(data, exponent);
        new_node->next = head;
        return new_node;
    }

    Node *temp = head;
    while (temp->next != NULL && temp->next->exponent >= exponent)
    {
        if (temp->next->exponent == exponent)
        {
            temp->next->data += data;
            return head;
        }
        temp = temp->next;
    }

    Node *new_node = createNode(data, exponent);
    new_node->next = temp->next;
    temp->next = new_node;

    return head;
}

Node *add(Node *h1, Node *h2)
{
    Node *head = NULL;

    while (h1 != NULL && h2 != NULL)
    {
        if (h1->exponent > h2->exponent)
        {
            head = addSorted(head, h1->data, h1->exponent);
            h1 = h1->next;
        }
        else if (h2->exponent > h1->exponent)
        {
            head = addSorted(head, h2->data, h2->exponent);
            h2 = h2->next;
        }
        else
        {
            head = addSorted(head, h1->data + h2->data, h1->exponent);
            h1 = h1->next;
            h2 = h2->next;
        }
    }

    while (h1 != NULL)
    {
        head = addSorted(head, h1->data, h1->exponent);
        h1 = h1->next;
    }

    while (h2 != NULL)
    {
        head = addSorted(head, h2->data, h2->exponent);
        h2 = h2->next;
    }

    return head;
}

void display(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        printf("%dX^%d", temp->data, temp->exponent);
        if (temp->next != NULL)
        {
            printf(" + ");
        }
        temp = temp->next;
    }
    printf("\n");
}

int main(void)
{
    Node *head1 = createNode(10, 4);
    head1 = addSorted(head1, 5, 3);
    head1 = addSorted(head1, 6, 2);
    head1 = addSorted(head1, 8, 1);

    Node *head2 = createNode(8, 3);
    head2 = addSorted(head2, 2, 2);
    head2 = addSorted(head2, 1, 1);

    Node *head = add(head1, head2);
    printf("Polynomial 1: ");
    display(head1);
    printf("Polynomial 2: ");
    display(head2);
    printf("Sum: ");
    display(head);

    return 0;
}
