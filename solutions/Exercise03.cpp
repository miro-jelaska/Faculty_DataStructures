#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person
{
    char firstName[100];
    char lastName[100];
    int yearOfBirth;

    Person* next;
};
typedef Person* PersonPtr;

typedef struct Head
{
    PersonPtr next;
};
typedef Head* HeadPtr;

PersonPtr CreateNewPerson
(
char* firstName,
char* lastName,
int   yearOfBirth
)
{
    PersonPtr newPerson = (PersonPtr)malloc(sizeof(Person));

    strcpy(newPerson->firstName, firstName);
    strcpy(newPerson->lastName, lastName);
    newPerson->yearOfBirth = yearOfBirth;
    newPerson->next = NULL;

    return newPerson;
}
HeadPtr CreateNewHead
(
)
{
    HeadPtr newHead = (HeadPtr)malloc(sizeof(Head));

    newHead->next = NULL;

    return newHead;
}

bool IsOutOfRange(PersonPtr person)
{
    return person == NULL;
}
bool IsLastElement(PersonPtr person)
{
    return person->next == NULL;
}
bool IsEmptyList(HeadPtr head)
{
    return head->next == NULL;
}


PersonPtr GetLastElement(HeadPtr head)
{
    if (IsEmptyList(head)) { return NULL; }

    PersonPtr currentPerson = NULL;
    for (currentPerson = head->next; !IsLastElement(currentPerson); currentPerson = currentPerson->next);
    return currentPerson;
}

void Prepend(HeadPtr head, PersonPtr element)
{
    element->next = head->next;
    head->next = element;
}
void Append(HeadPtr head, PersonPtr element)
{
    if (IsEmptyList(head))
    {
        head->next = element;
        element->next = NULL;
    }
    else
    {
        PersonPtr lastElement = GetLastElement(head);

        lastElement->next = element;
        element->next = NULL;
    }
}

void PrintPerson(PersonPtr person)
{
    printf("%s %s %d\n", person->firstName, person->lastName, person->yearOfBirth);
}
void PrintPersonsList(HeadPtr head)
{
    if (IsEmptyList(head)) { printf("List is empty.\n"); }
    for (PersonPtr currentPerson = head->next; !IsOutOfRange(currentPerson); currentPerson = currentPerson->next)
    {
        PrintPerson(currentPerson);
    }
}

int CountNumberOfElements(HeadPtr head)
{
    int count = 0;
    PersonPtr currentPerson = NULL;
    for (currentPerson = head->next; !IsOutOfRange(currentPerson); currentPerson = currentPerson->next)
    {
        count = count + 1;
    }
    return count;
}
PersonPtr FindPerson(HeadPtr head, char* lastNameQuery)
{
    if (IsEmptyList(head)) { return NULL; }

    PersonPtr currentPerson = NULL;
    for (currentPerson = head->next; !IsOutOfRange(currentPerson); currentPerson = currentPerson->next)
    {
        if (strcmp(currentPerson->lastName, lastNameQuery) == 0)
        {
            return currentPerson;
        }
    }
    return NULL;
}
PersonPtr FindPrevious(HeadPtr head, char* nextPersonName)
{
    PersonPtr nextPerson = FindPerson(head, nextPersonName);
    if (nextPerson == NULL) { return NULL; }

    if (CountNumberOfElements(head) == 1) { return NULL; }

    PersonPtr previousPerson = head->next;
    if (previousPerson == nextPerson) { return NULL; }
    for (; previousPerson->next != nextPerson; previousPerson = previousPerson->next);

    return previousPerson;
}
void DeletePerson(HeadPtr head, char* lastNameQuery)
{
    if (!IsEmptyList(head))
    {
        PersonPtr result = FindPerson(head, lastNameQuery);
        if (result != NULL)
        {
            PersonPtr previousPerson = FindPrevious(head, lastNameQuery);
            if (previousPerson == NULL && head->next == result)
            {
                head->next = result->next;
                free(result);
            }
            else if (previousPerson == NULL)
            {
                previousPerson->next = result->next;
                free(result);
            }
        }
    }
}
void Swap(HeadPtr head, PersonPtr a, PersonPtr b)
{
    // HACK: Temporarily prepends new person so the first person won't have head as it's previous.
    PersonPtr nullPerson = CreateNewPerson("000", "000", 0);
    Prepend(head, nullPerson);

    if (a->next != b)
    {
        PersonPtr previous_A = FindPrevious(head, a->lastName);
        PersonPtr previous_B = FindPrevious(head, b->lastName);

        previous_A->next = b;
        PersonPtr next_B = b->next;
        b->next = a->next;
        previous_B->next = a;
        a->next = next_B;
    }
    else
    {
        PersonPtr previous_A = FindPrevious(head, a->lastName);
        previous_A->next = b;
        a->next = b->next;
        b->next = a;
    }
    DeletePerson(head, "000");
}
void SwapCursors(PersonPtr* first, PersonPtr* second)
{
    PersonPtr* tmpCursorOfFirst = first;
    *first = *second;
    *second = *tmpCursorOfFirst;
}

bool IsSmallerThan(char* first, char* second)
{
    return strcmp(first, second) < 0;
}

void BubbleSort(HeadPtr head)
{
    for (PersonPtr current = head->next; !IsLastElement(current); current = current->next)
    {
        for (PersonPtr cursor = current->next; !IsOutOfRange(cursor); cursor = cursor->next)
        {
            if (IsSmallerThan(current->lastName, cursor->lastName))
            {
                Swap(head, current, cursor);
                SwapCursors(&current, &cursor);
            }
        }
    }
}

int main()
{
    HeadPtr head = CreateNewHead();

    // Test data
    PersonPtr person1 = CreateNewPerson("Andrija", "A", 1988);
    PersonPtr person2 = CreateNewPerson("Eugen", "C", 1994);
    PersonPtr person3 = CreateNewPerson("Ana", "D", 1990);
    PersonPtr person4 = CreateNewPerson("Matea", "B", 1990);

    Append(head, person1);
    Append(head, person2);
    Append(head, person3);
    Append(head, person4);
    PrintPersonsList(head);

    BubbleSort(head);

    printf("\n\n");

    PrintPersonsList(head);

    /*int menuItemId;
    do
    {
    printf("\n Menu \n");
    printf("1) Unos na pocetak\n");
    printf("2) Ispis cijele list\n");
    printf("3) Unos na kraj\n");
    printf("4) Pronadi\n");
    printf("5) Brisi\n");
    printf("6) Kraj programa\n");

    scanf("%d", &menuItemId);
    if(menuItemId == 1)
    {
    char firstName[100];
    char lastName[100];
    int yearOfBirth = 0;

    scanf("%s %s %d", firstName, lastName, &yearOfBirth);

    PersonPtr newPerson = CreateNewPerson(firstName, lastName, yearOfBirth);

    Prepend(head, newPerson);
    }
    else if(menuItemId == 2)
    {
    PrintPersonsList(head);
    }
    else if(menuItemId == 3)
    {
    char firstName[100];
    char lastName[100];
    int yearOfBirth = 0;

    scanf("%s %s %d", firstName, lastName, &yearOfBirth);

    PersonPtr newPerson = CreateNewPerson(firstName, lastName, yearOfBirth);

    Append(head, newPerson);
    }
    else if(menuItemId == 4)
    {
    printf("Unesite prezime osobe:\n");
    char lastName_query[100];
    scanf("%s", lastName_query);
    PersonPtr searchResult = FindPerson(head, lastName_query);
    PrintPerson(searchResult);
    }
    else if(menuItemId == 5)
    {
    printf("Unesite prezime osobe:\n");
    char lastName_query[100];
    scanf("%s", lastName_query);
    DeletePerson(head, lastName_query);
    }
    else if(menuItemId == 6)
    {
    printf("Program zavrsava \n");
    }

    }while(menuItemId != 6);*/

    return 0;
}