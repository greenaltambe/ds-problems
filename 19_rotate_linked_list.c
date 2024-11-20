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
        Node *temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }

    return prev;
}

Node *rotateLinkedList(Node *head, int k)
{
    Node *headSave = head;
    headSave = reverse(headSave);
    display(headSave);

    // Split linked list in two
    int i = 1;
    Node *list1 = headSave;
    while (headSave->next != NULL && i < k)
    {
        headSave = headSave->next;
        i++;
    }
    Node *list2 = headSave->next;
    headSave->next = NULL;

    // Merge linked list
    Node *tempList2 = list2;
    while (tempList2->next != NULL)
    {
        tempList2 = tempList2->next;
    }
    tempList2->next = list1;

    // Reverse linked list
    list2 = reverse(list2);
    return list2;
}

Node *rotate(Node *head, int k)
{
    // Find end of linked list
    Node *end = head;
    while (end->next != NULL)
    {
        end = end->next;
    }

    // Find kth node from start
    Node *rotatedStart = head;
    Node *start = head;
    int i = 1;
    while (i < k)
    {
        start = start->next;
        i++;
    }
    start->next = NULL;

    // Connect end to start
    end->next = rotatedStart;
    return start;
}

int main(void)
{
    Node *head = createNode(1);
    head = insertEnd(head, 2);
    head = insertEnd(head, 3);
    head = insertEnd(head, 4);
    head = insertEnd(head, 5);
    display(head);
    head = rotateLinkedList(head, 2);
    // rotate(head, 2);
    display(head);
    return 0;
}