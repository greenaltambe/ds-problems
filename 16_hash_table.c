#include <stdio.h>
#include <stdlib.h>

void display(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int func1(int data, int n)
{
    return data % n;
}

int func2(int data, int n)
{
    return (7 - (data % 7)) % n;
}

void linearProbing(int *arr, char *status, int data, int n)
{
    int u = func1(data, n);
    for (int i = 0; i < n; i++)
    {
        int index = (u + i) % n;
        if (status[index] == 'E')
        {
            arr[index] == data;
            status[index] = 'O';
            return;
        }
    }
}

void quadraticProbing(int *arr, char *status, int data, int n)
{
    int u = func1(data, n);
    for (int i = 0; i < n; i++)
    {
        int index = (u + i * i) % n;
        if (status[index] == 'E')
        {
            arr[index] == data;
            status[index] = 'O';
            return;
        }
    }
}

void doubleHashing(int *arr, char *status, int data, int n)
{
    int u = func1(data, n);
    int v = func2(data, n);

    for (int i = 0; i < n; i++)
    {
        int index = (u + v * i) % n;
        if (status[index] == 'E')
        {
            arr[index] = data;
            status[index] = 'O';
            return;
        }
    }
}

int main(void)
{
    int n;
    printf("Enter size of hash table : ");
    scanf("%d", &n);
    int *arr1 = calloc(sizeof(int), n);
    int *arr2 = calloc(sizeof(int), n);
    int *arr3 = calloc(sizeof(int), n);
    for (int i = 0; i < n; i++)
    {
        arr1[i] = -1;
        arr2[i] = -1;
        arr3[i] = -1;
    }

    char *status1 = malloc(sizeof(char) * n);
    char *status2 = malloc(sizeof(char) * n);
    char *status3 = malloc(sizeof(char) * n);
    for (int i = 0; i < n; i++)
    {
        status1[i] = 'E';
        status2[i] = 'E';
        status3[i] = 'E';
    }

    printf("Enter number of elements to insert: ");
    int number;
    scanf("%d", &number);

    int *arr = (int *)malloc(sizeof(int) * number);
    for (int i = 0; i < number; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < number; i++)
    {
        linearProbing(arr1, status1, arr[i], n);
    }

    for (int i = 0; i < number; i++)
    {
        quadraticProbing(arr2, status2, arr[i], n);
    }

    for (int i = 0; i < number; i++)
    {
        doubleHashing(arr3, status3, arr[i], n);
    }

    display(arr1, status1);
    display(arr2, status2);
    display(arr3, status3);

    return 0;
}