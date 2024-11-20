#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack
{
    int top;
    int size;
    int *arr;
} Stack;

void push(Stack *s, int val)
{
    if (s->top == s->size - 1)
    {
        printf("Stack overflow\n");
        return;
    }

    s->top++;
    s->arr[s->top] = val;
    printf("Pushed : %d\n", val);
}

int pop(Stack *s)
{
    if (s->top == -1)
    {
        printf("Stack is empty");
        return -1;
    }

    printf("Popped %d\n", s->arr[s->top]);
    s->top--;
    return s->arr[s->top + 1];
}

Stack *createStack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = -1;
    s->size = 10;
    s->arr = (int *)malloc(s->size * sizeof(int));
    return s;
}

int isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
    {
        return 1;
    }
    return 0;
}

char *reverse(char *str) {
    int len = strlen(str);
    char *reverse = (char *) malloc(len + 1);

    for(int i = 0; i<len; i++) {
        reverse[i] = str[len - i - 1];
    }

    reverse[len] = '\0';
    return reverse;
}

int prefixEval(char *str)
{
    Stack *s = createStack();

    char *prefix = reverse(str);

    int i = 0;
    while (prefix[i] != 0)
    {
        if (!isOperator(prefix[i]))
        {
            push(s, prefix[i] - '0');
            i++;
        }
        else
        {
            int x = pop(s);
            int y = pop(s);

            if (prefix[i] == '+')
            {
                push(s, x + y);
            }
            else if (prefix[i] == '-')
            {
                push(s, x - y);
            }
            else if (prefix[i] == '*')
            {
                push(s, x * y);
            }
            else if (prefix[i] == '/')
            {
                push(s, x / y);
            }

            i++;
        }

        printf("\n");
    }

    return pop(s);
}

int main(void)
{
    char prefix[100] = {'\0'};
    printf("Enter : ");
    scanf("%s", prefix);
    int res = prefixEval(prefix);

    printf("prefix: %s\n", prefix);
    printf("Ans : %d\n", res);
    return 0;
}