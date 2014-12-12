#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

//**************************************//
//               Stack                  //
//**************************************//
typedef struct StackElement
{
    int value;

    StackElement* previous;
    StackElement* next;
};
typedef StackElement* StackElementPtr;

typedef struct Stack
{
    int size;

    StackElementPtr first;
    StackElementPtr last;
};
typedef Stack* StackPtr;

StackPtr CreateEmptyStack()
{
    StackPtr newEmptyStack = (StackPtr)malloc(sizeof(Stack));

    newEmptyStack->size  = 0;
    newEmptyStack->first = NULL;
    newEmptyStack->last  = NULL;

    return newEmptyStack;
}
StackElementPtr CreateStackElement
(
    int value
)
{
    StackElementPtr newStackElement = (StackElementPtr)malloc(sizeof(StackElement));

    newStackElement->value    = value;
    newStackElement->previous = NULL;
    newStackElement->next     = NULL;

    return newStackElement;
}
StackElementPtr CreateStackElement
(
    int value,
    StackElementPtr previous
)
{
    StackElementPtr newStackElement = (StackElementPtr)malloc(sizeof(StackElement));

    newStackElement->value = value;
    newStackElement->previous = previous;
    newStackElement->next = NULL;

    return newStackElement;
}


void IncrementSizeOfStack(StackPtr stack)
{
    stack->size = stack->size + 1;
}
void DecrementSizeOfStack(StackPtr stack)
{
    stack->size = stack->size - 1;
}
void Push(StackPtr stack, int value)
{
    if (stack->size == 0)
    {
        stack->first = CreateStackElement(value);
        stack->last = stack->first;
        IncrementSizeOfStack(stack);
    }
    else
    {
        StackElementPtr newElement = CreateStackElement(value, stack->last);
        stack->last->next = newElement;
        stack->last = newElement;
        IncrementSizeOfStack(stack);
    }
}
int Peek(StackPtr stack)
{
    if (stack->size <= 0)
    {
        printf("\n**** Stack empty, nothing to peek. ****\n");
        return INT_MIN;
    }
    else
    {
        return stack->last->value;
    }
}
int Pop(StackPtr stack)
{
    if (stack->size <= 0)
    {
        printf("\n**** Stack empty, nothing to pop. ****\n");

        return INT_MIN;
    }
    else if (stack->size == 1)
    {
        int value = stack->first->value;
        free(stack->first);
        stack->first = NULL;
        stack->last = NULL;
        DecrementSizeOfStack(stack);

        return value;
    }
    else
    {
        int value = stack->last->value;
        StackElementPtr previousLast = stack->last;
        stack->last = stack->last->previous;
        
        free(previousLast);
        DecrementSizeOfStack(stack);

        return value;
    }
}

//**************************************//
//           PostfixCalculator          //
//**************************************//
bool IsNumeric(char value)
{
    return isdigit(value) != 0;
}
char* ConcatinateStringWithChar(char* string, char symbol)
{
    char* newString        = (char*)malloc((strlen(string) + 2)*sizeof(char));
    char* newStringCurrent = newString;

    for (char* current = string; *current != '\0'; current++)
    {
        *newStringCurrent = *current;
        newStringCurrent++;
    }

    *newStringCurrent = symbol;
    newStringCurrent++;

    *newStringCurrent = '\0';

    return newString;
}

void ExecuteOperation(StackPtr stack, char operation)
{
    int firstValue  = Pop(stack);
    int secondValue = Pop(stack);
    if     (operation == '+') { Push(stack, firstValue + secondValue); }
    else if(operation == '-') { Push(stack, firstValue - secondValue); }
    else if(operation == '*') { Push(stack, firstValue * secondValue); }
    else if(operation == '/') { Push(stack, firstValue / secondValue); }
}


int CalculatePostfixExpression(char* expression)
{
    StackPtr stack = CreateEmptyStack();
    char* tmp = "";
    bool wasLastNumber = false;
    for(char* current = expression; *current != '\0'; current++)
    {
        bool isNumber = IsNumeric(*current);
        bool isOperator = !isNumber && *current != ' ';

        if (isNumber)
        {
            tmp = ConcatinateStringWithChar(tmp, *current);
            wasLastNumber = true;
        }
        else if (isOperator)
        {
            ExecuteOperation(stack, *current);
            wasLastNumber = false;
        }
        else if (wasLastNumber)
        {
            Push(stack, atoi(tmp));
            tmp = "";
        }
    }
    return Pop(stack);
}


int main()
{
    printf("Result: %d\n", CalculatePostfixExpression("5 3 + 7 * 10 -"));
}
