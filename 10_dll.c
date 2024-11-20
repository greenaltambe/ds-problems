#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
} Node;

typedef struct dll
{
    Node *head;
    Node *tail;
} DLL;

Node *create_node(int data)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

DLL *insertAfterPosition(DLL *list, int position, int data)
{
    Node *new_node = create_node(data);
    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
        return list;
    }

    int i = 0;
    Node *curr = list->head;

    while (curr != NULL && i < position)
    {
        i++;
        curr = curr->next;
    }

    // Add to end
    if (curr == NULL)
    {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    else
    {
        Node *prev = curr->prev;
        if (prev != NULL)
        {
            prev->next = new_node;
        }
        else
        { // Index 0
            list->head = new_node;
        }

        new_node->prev = prev;
        new_node->next = curr;
        curr->prev = new_node;
    }

    return list;
}

DLL *sort(DLL *list)
{

    if (list->head == NULL)
    {
        return list;
    }

    Node *head = list->head;
    while (head != NULL)
    {
        Node *head2 = list->head;
        while (head2 != NULL)
        {
            if (head->data > head2->data)
            {
                int temp = head->data;
                head->data = head2->data;
                head2->data = temp;
            }

            head2 = head2->next;
        }

        head = head->next;
    }

    return list;
}

DLL *concatenate(DLL *l, DLL *l1, DLL *l2)
{
    l1->tail->next = l2->head;
    l2->head->prev = l1->tail;
    l->head = l1->head;
    l->tail = l2->tail;
    return l;
}

void display(DLL *list)
{
    Node *head = list->head;
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }

    printf("\n");
}

int main(void)
{

    DLL *list = (DLL *)malloc(sizeof(DLL));
    list->head = NULL;
    list->tail = NULL;

    list = insertAfterPosition(list, 0, 10);
    list = insertAfterPosition(list, 1, 15);
    list = insertAfterPosition(list, 2, 40);
    list = insertAfterPosition(list, 3, 42);
    list = insertAfterPosition(list, 1, 20); // Testing insertion in the middle

    printf("Original List: ");
    display(list);

    list = sort(list);
    printf("Sorted List: ");
    display(list);

    DLL *list1 = (DLL *)malloc(sizeof(DLL));
    list1->head = NULL;
    list1->tail = NULL;

    list1 = insertAfterPosition(list1, 0, 31);
    list1 = insertAfterPosition(list1, 1, 31);
    list1 = insertAfterPosition(list1, 2, 34);
    list1 = insertAfterPosition(list1, 3, 34);
    list1 = insertAfterPosition(list1, 1, 32); // Testing insertion in the middle

    printf("Original List: ");
    display(list1);

    DLL *conc = (DLL *)malloc(sizeof(DLL));
    conc->head = NULL;
    conc->tail = NULL;

    conc = concatenate(conc, list, list1);

    printf("Concatenated list: ");
    display(conc);
    printf("Sorted list: ");
    conc = sort(conc);
    display(conc);
    return 0;
}