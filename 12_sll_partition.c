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

Node *partition(Node *head, int x)
{
    Node *lessHead = NULL, *lessPtr = NULL;
    Node *equalHead = NULL, *equalPtr = NULL;
    Node *moreHead = NULL, *morePtr = NULL;

    Node *temp = head;
    while (temp != NULL)
    {
        if (temp->data < x)
        {
            if (lessHead == NULL)
            {
                lessHead = lessPtr = createNode(temp->data);
            }
            else
            {
                lessPtr->next = createNode(temp->data);
                lessPtr = lessPtr->next;
            }
        }
        else if (temp->data == x)
        {
            if (equalHead == NULL)
            {
                equalHead = equalPtr = createNode(temp->data);
            }
            else
            {
                equalPtr->next = createNode(temp->data);
                equalPtr = equalPtr->next;
            }
        }
        else
        {
            if (moreHead == NULL)
            {
                moreHead = morePtr = createNode(temp->data);
            }
            else
            {
                morePtr->next = createNode(temp->data);
                morePtr = morePtr->next;
            }
        }
        temp = temp->next;
    }

    // Combine the lists
    if (lessHead != NULL)
    {
        lessPtr->next = equalHead;
    }
    else
    {
        lessHead = equalHead;
    }

    if (equalHead != NULL)
    {
        equalPtr->next = moreHead;
    }
    else if (lessHead == NULL)
    {
        lessHead = moreHead;
    }

    return lessHead;
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

int main(void)
{

    Node *head = NULL;
    head = insertEnd(head, 1);
    head = insertEnd(head, 4);
    head = insertEnd(head, 3);
    head = insertEnd(head, 2);
    head = insertEnd(head, 5);
    head = insertEnd(head, 2);
    head = insertEnd(head, 3);

    printf("Original linked list: ");
    display(head);

    int x = 3;
    head = partition(head, x);

    printf("Partitioned linked list: ");
    display(head);

    return 0;
}