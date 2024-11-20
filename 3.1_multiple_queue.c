#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

# define max 3

void printarray(int *head, int *tail, int arr[]) {
    printf("\nYour queue: ");
    for (int i = *head + 1; i <= *tail; i++) {
        printf("%d ", arr[i]);
    }
}

void display(int front[], int rear[], int arr[]) {
    // Display all three queues
    for (int i = 0; i < max; i++) {
        printf("\nQueue %d: ", i + 1);
        if (front[i] > rear[i]) {
            printf("Empty");
        } else {
            for (int j = front[i]; j <= rear[i]; j++) {
                printf("%d ", arr[j]);
            }
        }
        printf("\n");
    }
}

void enqueue(int front[], int rear[], int data, int arr[], int queue_number) {
    queue_number--; // Adjust for 0-based indexing
    rear[queue_number]++;
    arr[rear[queue_number]] = data;
    printf("\nElement %d inserted into Queue %d.\n", data, queue_number + 1);
    display(front, rear, arr); // Display all queues after enqueue
}

void dequeue(int front[], int rear[], int data, int arr[], int queue_number) {
    queue_number--; // Adjust for 0-based indexing
    if (front[queue_number] > rear[queue_number]) {
        printf("Queue %d is empty\n", queue_number + 1);
        return;
    }
    int remove_element = arr[front[queue_number] + 1];
    front[queue_number]++;
    printf("\nElement %d dequeued from Queue %d.\n", remove_element, queue_number + 1);
    display(front, rear, arr); // Display all queues after dequeue
}

int main() {
    int data, queue_number;
    int choice;
    int arr[max * 100]; // Dynamically allocate memory for the array
    int front[max] = {0, 0, 0}; // Initialize front pointers for each queue
    int rear[max] = {-1, -1, -1}; // Initialize rear pointers for each queue

    while (1) {
        printf("\nEnter queue number (1 to 3): ");
        scanf("%d", &queue_number);

        if (queue_number < 1 || queue_number > 3) {
            printf("\nInvalid queue number. Please enter a number between 1 and 3.\n");
            continue;
        }

        printf("\n1 for enqueue \n2 for dequeue\n3 for exit :");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter element to insert: ");
                scanf("%d", &data);
                enqueue(front, rear, data, arr, queue_number);
                break;

            case 2:
                dequeue(front, rear, data, arr, queue_number);
                break;

            case 3:
                printf("Exiting...\n");
                free(arr); // Free dynamically allocated memory
                return 0;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}