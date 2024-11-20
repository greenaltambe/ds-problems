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

void reverse(char *str)
{

    int first = 0;
    int last = strlen(str) - 1;
    char temp;

    while (first < last)
    {

        temp = str[first];
        str[first] = str[last];
        str[last] = temp;

        first++;
        last--;
    }
}

void swap_parenthesis(char *str)
{

    int i = 0;
    while (str[i] != '\0')
    {

        if (str[i] == '(')
        {
            str[i] = ')';
        }
        else if (str[i] == ')')
        {
            str[i] = '(';
        }

        i++;
    }
}

char *infix_to_prefix(char *infix)
{

    Stack *s = create_stack();
    reverse(infix);
    swap_parenthesis(infix);

    char *prefix = (char *)malloc(strlen(infix) + 1);
    int i = 0;
    int j = 0;

    while (infix[i] != '\0')
    {
        if (!is_operator(infix[i]) && infix[i] != '(' && infix[i] != ')')
        {
            prefix[j] = infix[i];
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
            while (s->top != -1 && s->arr[s->top] != '(')
            {
                prefix[j] = pop(s);
                j++;
            }

            if (s->top != -1 && s->arr[s->top] == '(')
            {
                pop(s);
            }

            i++;
        }
        else if (precedence(infix[i]) <= precedence(s->arr[s->top]))
        {
            while (s->top != -1 && precedence(infix[i]) <= precedence(s->arr[s->top]))
            {
                prefix[j] = pop(s);
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
        prefix[j] = pop(s);
        j++;
    }

    prefix[j] = '\0';

    reverse(prefix);
    return prefix;
}

int main(void)
{
    char infix_str[] = "a+b*(c-a)/e+f";
    char *infix = (char *)malloc(strlen(infix_str) + 1);
    strcpy(infix, infix_str);  // Copy string literal to allocated memory

    char *prefix = infix_to_prefix(infix);
    printf("Prefix Expression: %s\n", prefix);

    free(infix);  // Free allocated memory for infix
    free(prefix); // Free allocated memory for prefix
    return 0;
}
