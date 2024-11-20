#include <stdio.h>
#include <stdlib.h>

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

int postfixEval(char *postfix)
{
    Stack *s = createStack();

    int i = 0;
    while (postfix[i] != 0)
    {
        if (!isOperator(postfix[i]))
        {
            push(s, postfix[i] - '0');
            i++;
        }
        else
        {
            int y = pop(s);
            int x = pop(s);

            if (postfix[i] == '+')
            {
                push(s, x + y);
            }
            else if (postfix[i] == '-')
            {
                push(s, x - y);
            }
            else if (postfix[i] == '*')
            {
                push(s, x * y);
            }
            else if (postfix[i] == '/')
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
    char postfix[100] = {'\0'};
    printf("Enter : ");
    scanf("%s", postfix);
    int res = postfixEval(postfix);

    printf("Postfix: %s\n", postfix);
    printf("Ans : %d\n", res);
    return 0;
}