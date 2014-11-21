#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Element
{
    int value;

    Element* next;
};
typedef Element* ElementPtr;

typedef struct SetHead
{
    ElementPtr next;
};
typedef SetHead* SetHeadPtr;

SetHeadPtr CreateEmptySet()
{
    SetHeadPtr emptySet = (SetHeadPtr)malloc(sizeof(SetHead));

    emptySet->next  = NULL;

    return emptySet;
}
ElementPtr CreateElement
(
    int value
)
{
    ElementPtr newElement = (ElementPtr)malloc(sizeof(Element));

    newElement->value = value;
    newElement->next  = NULL;

    return newElement;
}
ElementPtr CloneElement_withoutNext(ElementPtr element)
{
    return CreateElement(element->value);
}

void SetToNext(ElementPtr* element)
{
    *element = (*element)->next;
}

bool IsOutOfRange(ElementPtr element)
{
    return element == NULL;
}
bool IsLastElement(ElementPtr element)
{
    return element->next == NULL;
}
bool IsLargerPowerThan(ElementPtr first, ElementPtr second)
{
    return first->value > second->value;
}
bool IsZeroPolynomial(SetHeadPtr set)
{
    return set->next == NULL;
}
bool IsEmptyOrNull(SetHeadPtr set)
{
    return (set == NULL || set->next == NULL);
}
bool ElementExists(SetHeadPtr head, ElementPtr element)
{
    for(ElementPtr current = head->next; !IsOutOfRange(current); SetToNext(&current))
    {
        if(current->value == element->value)
        {
            return true;
        }
    }
    return false;
}


void AddElementToSet(SetHeadPtr head, ElementPtr element)
{
    if(!ElementExists(head, element))
    {
        ElementPtr current = head->next;

        if (!IsOutOfRange(current) && IsLargerPowerThan(current, element))
        {
            for (; !IsLastElement(current) && IsLargerPowerThan(current->next, element); SetToNext(&current));

            element ->next = current->next;
            current ->next = element;
        }
        else
        {
            element ->next = head->next;
            head    ->next = element;
        }
    }
}


SetHeadPtr Union(SetHeadPtr firstHead, SetHeadPtr secondHead)
{
    SetHeadPtr newSetHead = CreateEmptySet();

    ElementPtr firstElement  = firstHead->next;
    ElementPtr secondElement = secondHead->next;
    while (!IsOutOfRange(firstElement) || !IsOutOfRange(secondElement))
    {
        if (!IsOutOfRange(firstElement))
        {
            AddElementToSet(newSetHead, CloneElement_withoutNext(firstElement));
            SetToNext(&firstElement);
        }
        else 
        {
            AddElementToSet(newSetHead, CloneElement_withoutNext(secondElement));
            SetToNext(&secondElement);
        }
    }

    return newSetHead;
}
SetHeadPtr Intersections(SetHeadPtr firstHead, SetHeadPtr secondHead)
{
    SetHeadPtr newSetHead = CreateEmptySet();

    for(ElementPtr current = firstHead->next; !IsOutOfRange(current); SetToNext(&current))
    {
        if(ElementExists(secondHead, current))
        {
            AddElementToSet(newSetHead, CloneElement_withoutNext(current));
        }
    }

    return newSetHead;
}
void PrintSet(SetHeadPtr head)
{
    if(!IsEmptyOrNull(head))
    {
        printf("\n");
        for(ElementPtr current = head->next; !IsOutOfRange(current); SetToNext(&current))
        {
            printf("Value: %d\n", current->value);
        }
    }
    else
    {
        printf("\n Polynomial empty or null");
    }
}

SetHeadPtr ReadSetFromFile(char* relativePath)
{
    FILE* file = fopen(relativePath, "r");

    if(file != NULL)
    {
        SetHeadPtr newSetHead = CreateEmptySet();

        while(!feof(file))
        {
            int value;

            if(EOF != fscanf_s(file, "%d", &value))
            {
                AddElementToSet(newSetHead, CreateElement(value));
            }
        }

        fclose(file);

        return newSetHead;
    }
    else
    {
        printf("Error occurred while opening file");
        return NULL;
    }
}

int main()
{
    SetHeadPtr set_1 = CreateEmptySet();
    AddElementToSet(set_1, CreateElement(10));
    AddElementToSet(set_1, CreateElement(6));
    AddElementToSet(set_1, CreateElement(2));
    AddElementToSet(set_1, CreateElement(7));
    AddElementToSet(set_1, CreateElement(9));
    
    SetHeadPtr set_2 = CreateEmptySet();
    AddElementToSet(set_2, CreateElement(9));
    AddElementToSet(set_2, CreateElement(1));
    AddElementToSet(set_2, CreateElement(2));
    AddElementToSet(set_2, CreateElement(-5));

    //SetHeadPtr set_1 = ReadSetFromFile("Set1.txt");
    //SetHeadPtr set_2 = ReadSetFromFile("Set2.txt");


    PrintSet(set_1);
    PrintSet(set_2);
    PrintSet(Union(set_1, set_2));
    PrintSet(Intersections(set_1, set_2));
}
