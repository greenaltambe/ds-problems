#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack
{
    int top;
    int size;
    char *arr;
} Stack;

void push(Stack *s, char val)
{
    if (s->top == s->size - 1)
    {
        printf("Stack Overflow\n");
        return;
    }

    s->top++;
    s->arr[s->top] = val;
}

char pop(Stack *s)
{
    if (s->top == -1)
    {
        printf("Stack Underflow\n");
        return '\0';
    }

    char ch = s->arr[s->top];
    s->top--;
    return ch;
}

Stack *create_stack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = -1;
    s->size = 100;
    s->arr = (char *)malloc(sizeof(char) * s->size);
    return s;
}

int is_operator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
    {
        return 1;
    }

    return 0;
}

int precedence(char ch)
{
    if (ch == '*' || ch == '/')
    {
        return 2;
    }
    else if (ch == '+' || ch == '-')
    {
        return 1;
    }

    return 0;
}

char *infix_to_postfix(char *infix)
{
    Stack *s = create_stack();
    char *postfix = (char *)malloc(strlen(infix) + 1);

    int i = 0;
    int j = 0;
    while (infix[i] != '\0')
    {
        if (!is_operator(infix[i]) && infix[i] != '(' && infix[i] != ')')
        {
            postfix[j] = infix[i];
            i++;
            j++;
        }
        else if (infix[i] == '(')
        {
            push(s, infix[i]);
            i++;
        }
        else if (infix[i] == ')')
        {
            while (s->arr[s->top] != '(' && s->top != -1)
            {
                postfix[j] = pop(s);
                j++;
            }

            if (s->top != -1 && s->arr[s->top] == '(')
            {
                pop(s);
            }
            i++;
        }
        else if (s->top != -1 && precedence(infix[i]) <= precedence(s->arr[s->top]))
        {
            while (precedence(infix[i]) <= precedence(s->arr[s->top]))
            {
                postfix[j] = pop(s);
                j++;
            }

            push(s, infix[i]);
            i++;
        }
        else
        {
            push(s, infix[i]);
            i++;
        }
    }

    while (s->top != -1)
    {
        postfix[j] = pop(s);
        j++;
    }

    postfix[j] = '\0';

    return postfix;
}

int main(void)
{

    char *infix = "a+b*(c-a)/e+f";
    char *postfix = infix_to_postfix(infix);

    int i = 0;
    while (postfix[i] != '\0')
    {
        printf("%c", postfix[i]);
        i++;
    }

    return 0;
}