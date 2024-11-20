#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
    int size;
    int front;
    int rear;
    int *arr;
} Queue;

Queue *createQueue(int size) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->size = size;
    q->front = -1;
    q->rear = -1;
    q->arr = (int *)malloc(sizeof(int) * size);
    return q;
}

int isFull(Queue *q) {
    return ((q->rear + 1) % q->size == q->front);
}

int isEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

void enqueue(Queue *q, int val) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }

    if (isEmpty(q)) {
        q->front = 0;
    }

    q->rear = (q->rear + 1) % q->size;
    q->arr[q->rear] = val;
    printf("Enqueued %d\n", val);
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }

    int data = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % q->size;
    }

    return data;
}

int peek(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->arr[q->front];
}

void displayMenu() {
    printf("Queue Operations:\n");
    printf("1. Enqueue\n");
    printf("2. Dequeue\n");
    printf("3. Peek\n");
    printf("4. Check if Full\n");
    printf("5. Check if Empty\n");
    printf("6. Exit\n");
}

int main(void) {
    int size, choice, value;
    printf("Enter the size of the queue: ");
    scanf("%d", &size);

    Queue *q = createQueue(size);

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(q, value);
                break;
            case 2:
                value = dequeue(q);
                if (value != -1) {
                    printf("Dequeued: %d\n", value);
                }
                break;
            case 3:
                value = peek(q);
                if (value != -1) {
                    printf("Front element: %d\n", value);
                }
                break;
            case 4:
                if (isFull(q)) {
                    printf("Queue is full\n");
                } else {
                    printf("Queue is not full\n");
                }
                break;
            case 5:
                if (isEmpty(q)) {
                    printf("Queue is empty\n");
                } else {
                    printf("Queue is not empty\n");
                }
                break;
            case 6:
                printf("Exiting...\n");
                free(q->arr);
                free(q);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
