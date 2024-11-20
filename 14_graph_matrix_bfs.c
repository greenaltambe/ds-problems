#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
    int size;
    int front;
    int rear;
    int *arr;
} Queue;

Queue *createQueue(int size)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->size = size;
    q->front = -1;
    q->rear = -1;
    q->arr = (int *)calloc(sizeof(int), size);
    return q;
}

int isFull(Queue *q)
{
    return q->rear == q->size - 1;
}

int isEmpty(Queue *q)
{
    return q->front == q->rear;
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
    int val = q->arr[q->front];
    return val;
}
void printBFS(int n, int matrix[][n + 1], int source)
{
    Queue *q = createQueue(n);
    int *visited = (int *)calloc((n + 1), sizeof(int));

    visited[source] = 1;
    enqueue(q, source);

    while (!isEmpty(q))
    {
        int val = dequeue(q);
        printf("%d ", val);
        for (int i = 0; i < n; i++)
        {
            if (matrix[val][i] == 1 && !visited[i])
            {
                visited[i] = 1;
                enqueue(q, i);
            }
        }
    }
}

int main(void)
{
    int n, e;
    printf("Enter vertices number: ");
    scanf("%d", &n);
    printf("Enter edges number: ");
    scanf("%d", &e);

    int matrix[n + 1][n + 1];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            matrix[i][j] = 0;

    printf("===============Enter edge pair===============\n");
    for (int i = 0; i < e; i++)
    {
        printf("Enter edge pairs: ");
        int v, u;
        scanf("%d %d", &v, &u);
        matrix[v][u] = 1;
        matrix[u][v] = 1;
    }

    printf("===============Adjacency Matrix===============\n");
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }

    printf("Enter source: ");
    int source;
    scanf("%d", &source);

    printf("===============BFS===============\n");
    printBFS(n, matrix, source);
    return 0;
}