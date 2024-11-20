#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node *insertEnd(Node *head, int data)
{

    if (head == NULL)
        return create_node(data);

    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = create_node(data);
    return head;
}

typedef struct queue
{
    int size;
    int front;
    int rear;
    int *arr;
} Queue;

Queue *create_queue(int size)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->size = size;
    q->front = -1;
    q->rear = -1;
    q->arr = (int *)malloc(sizeof(int) * size);
    return q;
}

int isFull(Queue *q)
{
    if (q->rear == q->size - 1)
    {
        return 1;
    }
    return 0;
}

int isEmpty(Queue *q)
{
    if (q->front == q->rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enqueue(Queue *q, int val)
{
    if (isFull(q))
    {
        printf("Queue is full\n");
        return;
    }

    q->rear++;
    q->arr[q->rear] = val;
}

int dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }

    q->front++;
    return q->arr[q->front];
}

void printBFS(Node **graph, int n, int start)
{
    Queue *q = create_queue(n);

    int *visited = (int *)calloc(n, sizeof(int));
    visited[start] = 1;
    enqueue(q, start);

    while (!isEmpty(q))
    {
        int curr = dequeue(q);
        printf("%d ", curr);
        Node *temp = graph[curr];
        while (temp != NULL)
        {
            if (!visited[temp->data])
            {
                visited[temp->data] = 1;
                enqueue(q, temp->data);
            }

            temp = temp->next;
        }
    }
}

int main(void)
{
    int n, e;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &e);

    Node **graph = (Node **)malloc(sizeof(Node *) * n);
    for (int i = 0; i < n; i++)
    {
        graph[i] = NULL;
    }

    for (int i = 0; i < e; i++)
    {
        int u, v;
        printf("Enter edge pairs: ");
        scanf("%d %d", &u, &v);
        graph[u] = insertEnd(graph[u], v);
        graph[v] = insertEnd(graph[v], u);
    }

    printBFS(graph, n, 1);

    return 0;
}