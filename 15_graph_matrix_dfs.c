#include <stdlib.h>
#include <stdio.h>

typedef struct stack
{
    int size;
    int top;
    int *arr;
} Stack;

Stack *createStack(int size)
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->size = size;
    s->top = -1;
    s->arr = (int *)malloc(sizeof(int) * size);
    return s;
}

void push(Stack *s, int val)
{
    if (s->top == s->size - 1)
    {
        printf("Stack Overflow\n");
        return;
    }

    s->top++;
    s->arr[s->top] = val;
}

int pop(Stack *s)
{
    if (s->top == -1)
    {
        printf("Stack Underflow\n");
        return -1;
    }

    int val = s->arr[s->top];
    s->top--;
    return val;
}

void printDFS(int n, int matrix[n + 1][n + 1], int source)
{
    Stack *s = createStack(n + 1);
    int visited[n + 1];

    // Initialize visited array
    for (int i = 0; i <= n; i++)
        visited[i] = 0;

    // Push initial node and mark it visited
    push(s, source);
    visited[source] = 1;
    printf("%d ", source);

    while (s->top != -1)
    {                                 // While stack is not empty
        int current = s->arr[s->top]; // Get current node (peek)
        int foundUnvisited = 0;

        // Try to find an unvisited neighbor
        for (int j = 0; j <= n; j++)
        {
            if (matrix[current][j] == 1 && !visited[j])
            {
                push(s, j);
                visited[j] = 1;
                printf("%d ", j);
                foundUnvisited = 1;
                break;
            }
        }

        // If no unvisited neighbor found, backtrack by popping
        if (!foundUnvisited)
        {
            pop(s);
        }
    }
    printf("\n");
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

    printf("===============DFS===============\n");
    printf("Enter source: ");
    int source;
    scanf("%d", &source);
    printDFS(n, matrix, source);
    return 0;
}