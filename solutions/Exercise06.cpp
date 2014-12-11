#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

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
//               Queue                  //
//**************************************//
typedef struct QueueElement
{
    int value;

    QueueElement* next;
};
typedef QueueElement* QueueElementPtr;

typedef struct Queue
{
    int size;

    QueueElementPtr first;
    QueueElementPtr last;
};
typedef Queue* QueuePtr;

QueuePtr CreateEmptyQueue()
{
    QueuePtr newEmptyQueue = (QueuePtr)malloc(sizeof(Queue));

    newEmptyQueue->size  = 0;
    newEmptyQueue->first = NULL;
    newEmptyQueue->last  = NULL;

    return newEmptyQueue;
}
QueueElementPtr CreateQueueElement
(
    int value
)
{
    QueueElementPtr newQueueElement = (QueueElementPtr)malloc(sizeof(QueueElement));

    newQueueElement->value = value;
    newQueueElement->next  = NULL;

    return newQueueElement;
}

void IncrementSizeOfQueue(QueuePtr queue)
{
    queue->size = queue->size + 1;
}
void DecrementSizeOfStack(QueuePtr queue)
{
    queue->size = queue->size - 1;
}

void Enqueue(QueuePtr queue, int value)
{
    if (queue->size == 0)
    {
        queue->first = CreateQueueElement(value);
        queue->last = queue->first;
        IncrementSizeOfQueue(queue);
    }
    else
    {
        queue->last->next = CreateQueueElement(value);
        queue->last = queue->last->next;
        IncrementSizeOfQueue(queue);
    }
}
int Dequeue(QueuePtr queue)
{
    if (queue->size <= 0)
    {
        printf("\n**** Queue empty, nothing to dequeue. ****\n");

        return INT_MIN;
    }
    else if (queue->size >= 1)
    {
        int value = queue->first->value;
        QueueElementPtr previousFirst = queue->first;
        queue->first = queue->first->next;
        
        free(previousFirst);
        DecrementSizeOfStack(queue);

        return value;
    }
}


int main()
{
    printf("\n------ STACK ------\n");
    StackPtr stack = CreateEmptyStack();
    Push(stack, 25);
    Push(stack, 91);
    Push(stack, 31);
    printf("%d\n", Pop(stack));
    printf("%d\n", Peek(stack));
    printf("%d\n", Pop(stack));
    printf("%d\n", Pop(stack));
    Push(stack, 4);
    printf("%d\n", Pop(stack));
    printf("%d\n", Pop(stack));

    printf("\n------ QUEUE ------\n");
    QueuePtr queue = CreateEmptyQueue();
    Enqueue(queue, 25);
    Enqueue(queue, 31);
    printf("%d\n", Dequeue(queue));
    printf("%d\n", Dequeue(queue));
    Enqueue(queue, 10);
    printf("%d\n", Dequeue(queue));
}
