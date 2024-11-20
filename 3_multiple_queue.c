#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
    int *arr;   // Array to store elements of all queues
    int *front; // Array to store front index of all queues
    int *rear;  // Array to store rear index of all queues
    int *next;  // Array to store next free location
    int free;   // Beginning of the free list of queues
    int k, n;   // Number of queues and size of array
} KQueue;

KQueue *createKQueue(int k, int n)
{
    KQueue *q = (KQueue *)malloc(sizeof(KQueue));
    q->k = k;
    q->n = n;
    q->arr = (int *)calloc(n, sizeof(int));
    q->front = (int *)malloc(k * sizeof(int));
    q->rear = (int *)malloc(k * sizeof(int));
    q->next = (int *)malloc(n * sizeof(int));

    // Initialize all queues as empty
    for (int i = 0; i < k; i++)
    {
        q->front[i] = -1;
        q->rear[i] = -1;
    }

    // Initialize all spaces as free and link them together
    for (int i = 0; i < n - 1; i++)
    {
        q->next[i] = i + 1;
    }
    q->next[n - 1] = -1;
    q->free = 0; // Current free slot

    return q;
}

void enqueue(KQueue *q, int val, int qno)
{
    if (qno < 0 || qno >= q->k)
    {
        printf("Invalid queue number\n");
        return;
    }

    if (q->free == -1)
    {
        printf("Queue is full\n");
        return;
    }

    int i = q->free;      // Current free slot
    q->free = q->next[i]; // Update the free slot with next free slot

    if (q->front[qno] == -1)
    {
        q->front[qno] = i; // First element
    }
    else
    {
        q->next[q->rear[qno]] = i; // Link new element
    }

    q->next[i] = -1; // Set next of this ith slot as -1 (this is the last element)
    q->rear[qno] = i;
    q->arr[i] = val;
    printf("Enqueued %d in queue %d\n", val, qno);
}

int dequeue(KQueue *q, int qno)
{
    if (qno < 0 || qno >= q->k)
    {
        printf("Invalid queue number\n");
        return -1;
    }

    if (q->front[qno] == -1)
    {
        printf("Queue %d is empty\n", qno);
        return -1;
    }

    int i = q->front[qno];
    q->front[qno] = q->next[i];

    if (q->front[qno] == -1)
    {                      // If queue becomes empty
        q->rear[qno] = -1; // Set rear of this queue as -1
    }

    q->next[i] = q->free; // Link freed index to free list
    q->free = i;

    printf("Dequeued %d from queue %d\n", q->arr[i], qno);
    return q->arr[i];
}

void display(KQueue *q, int qno)
{
    if (qno < 0 || qno >= q->k)
    {
        printf("Invalid queue number\n");
        return;
    }

    if (q->front[qno] == -1)
    {
        printf("Queue %d is empty\n", qno);
        return;
    }

    printf("Queue %d: ", qno);
    int i = q->front[qno];
    while (i != -1)
    {
        printf("%d ", q->arr[i]);
        i = q->next[i];
    }
    printf("\n");
}

void displayAll(KQueue *q)
{
    for (int i = 0; i < q->k; i++)
    {
        display(q, i);
    }
}

void printKQueue(KQueue *q)
{
    printf("Array: ");
    printf("[");
    for (int i = 0; i < q->n; i++)
    {
        printf("%d ", q->arr[i]);
        if (i < q->n - 1)
            printf(", ");
    }
    printf("]\n");

    printf("Front: ");
    printf("[");

    for (int i = 0; i < q->k; i++)
    {
        printf("%d ", q->front[i]);
        if (i < q->k - 1)
            printf(", ");
    }
    printf("]\n");

    printf("Rear: ");
    printf("[");

    for (int i = 0; i < q->k; i++)
    {
        printf("%d ", q->rear[i]);
        if (i < q->k - 1)
            printf(", ");
    }
    printf("]\n");

    printf("Next: ");
    printf("[");

    for (int i = 0; i < q->n; i++)
    {
        printf("%d ", q->next[i]);
        if (i < q->n - 1)
            printf(", ");
    }
    printf("]\n");

    printf("Free: %d\n", q->free);
}

int main()
{
    int k, n, choice, qno, val;

    printf("Enter the number of queues: ");
    scanf("%d", &k);
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    KQueue *q = createKQueue(k, n);

    while (1)
    {

        printKQueue(q);

        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display a Queue\n");
        printf("4. Display All Queues\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter queue number (0 to %d): ", k - 1);
            scanf("%d", &qno);
            printf("Enter value to enqueue: ");
            scanf("%d", &val);
            enqueue(q, val, qno);
            break;

        case 2:
            printf("Enter queue number (0 to %d): ", k - 1);
            scanf("%d", &qno);
            dequeue(q, qno);
            break;

        case 3:
            printf("Enter queue number (0 to %d): ", k - 1);
            scanf("%d", &qno);
            display(q, qno);
            break;

        case 4:
            displayAll(q);
            break;

        case 5:
            printf("Exiting...\n");
            free(q->arr);
            free(q->front);
            free(q->rear);
            free(q->next);
            free(q);
            exit(0);

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
