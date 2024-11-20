#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

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

Node *createNode(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node *insertEnd(Node *head, int data)
{
    if (head == NULL)
    {
        return createNode(data);
    }

    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    Node *new_node = createNode(data);
    temp->next = new_node;
    return head;
}

Node *reverse(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    Node *prev = NULL;
    Node *curr = head;
    while (curr != NULL)
    {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

Node *add(Node *head1, Node *head2)
{
    head1 = reverse(head1);
    head2 = reverse(head2);

    printf("Reversed Linked Lists:\n");
    display(head1);
    display(head2);

    Node *temp1 = head1;
    Node *temp2 = head2;

    Node *sum = NULL;
    int carry = 0;
    int data;
    while (temp1 != NULL && temp2 != NULL)
    {
        data = temp1->data + temp2->data + carry;
        sum = insertEnd(sum, data % 10);
        carry = data / 10;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    while (temp1 != NULL)
    {
        if (carry == 0)
        {
            sum = insertEnd(sum, temp1->data);
        }
        else
        {
            data = temp1->data + carry;
            sum = insertEnd(sum, data % 10);
            carry = data / 10;
        }

        temp1 = temp1->next;
    }

    while (temp2 != NULL)
    {
        if (carry == 0)
        {
            sum = insertEnd(sum, temp2->data);
        }
        else
        {
            data = temp2->data + carry;
            sum = insertEnd(sum, data % 10);
            carry = data / 10;
        }

        temp2 = temp2->next;
    }

    sum = reverse(sum);

    return sum;
}

int main(void)
{
    Node *head1 = createNode(7);
    head1 = insertEnd(head1, 2);
    head1 = insertEnd(head1, 3);
    head1 = insertEnd(head1, 3);

    Node *head2 = createNode(5);
    head2 = insertEnd(head2, 7);
    head2 = insertEnd(head2, 4);

    printf("Original Linked Lists:\n");
    display(head1);
    display(head2);

    printf("Sum of Linked Lists:\n");
    Node *head = add(head1, head2);
    display(head);
    return 0;
}