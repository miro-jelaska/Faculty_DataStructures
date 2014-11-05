#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Note
// Powers decrease as furher they are from head
// p------>
// *-+-+-+

typedef struct Monomial
{
    int coefficient;
    int power;

    Monomial* next;
};
typedef Monomial* MonomialPtr;

typedef struct PolynomialHead
{
    int count;
    
    MonomialPtr next;
};
typedef PolynomialHead* PolynomialHeadPtr;

PolynomialHeadPtr CreateZeroPolynomial()
{
    PolynomialHeadPtr newZeroPolynomial = (PolynomialHeadPtr)malloc(sizeof(PolynomialHead));

    newZeroPolynomial->count = 0;
    newZeroPolynomial->next  = NULL;

    return newZeroPolynomial;
}
MonomialPtr CreateMonomial
(
    int coefficient,
    int power
)
{
    MonomialPtr newMonomial = (MonomialPtr)malloc(sizeof(Monomial));

    newMonomial->coefficient = coefficient;
    newMonomial->power       = power;
    newMonomial->next        = NULL;

    return newMonomial;
}
MonomialPtr CloneMonomial_withoutNext
(
    MonomialPtr monomial
)
{
    return CreateMonomial(monomial->coefficient, monomial->power);
}

bool IsOutOfRange(MonomialPtr monomial)
{
    return monomial == NULL;
}
bool IsLastElement(MonomialPtr monomial)
{
    return monomial->next == NULL;
}
bool IsLargerPowerThan(MonomialPtr first, MonomialPtr second)
{
    return first->power > second->power;
}
bool IsZeroPolynomial(PolynomialHeadPtr polynomial)
{
    return polynomial->next == NULL;
}
bool IsEmptyOrNull(PolynomialHeadPtr polynomial)
{
    return (polynomial == NULL || polynomial->count == 0);
}

MonomialPtr GetMonomialWithPower(PolynomialHeadPtr polynomial, int power)
{
    if (IsEmptyOrNull(polynomial)) { return NULL; }

    for (MonomialPtr current = polynomial->next; !IsOutOfRange(current); current = current->next)
    {
        if (current->power == power)
        {
            return current;
        }
    }
    return NULL;
}

void SetToNext(MonomialPtr* monomial)
{
    *monomial = (*monomial)->next;
}
void AddMonomialToPolynomial(PolynomialHeadPtr head, MonomialPtr monomial)
{
    MonomialPtr current = head->next;

    if (!IsOutOfRange(current) && IsLargerPowerThan(current, monomial))
    {
        for (; !IsLastElement(current) && IsLargerPowerThan(current->next, monomial); SetToNext(&current));

        monomial->next = current->next;
        current ->next = monomial;
    }
    else
    {
        monomial->next = head->next;
        head    ->next = monomial;
    }

    head->count = head->count + 1;
}
void SumMonomialWithMonomial(MonomialPtr destination, MonomialPtr source)
{
    destination->coefficient = destination->coefficient + source->coefficient;
}
void SumPolynomialWithMonomial(PolynomialHeadPtr head, MonomialPtr monomial)
{
    MonomialPtr monomialWithSamePower = GetMonomialWithPower(head, monomial->power);
    if (monomialWithSamePower != NULL)
    {
        SumMonomialWithMonomial(monomialWithSamePower, monomial);
    }
    else
    {
        AddMonomialToPolynomial(head, monomial);
    }
}
MonomialPtr MultiplyMonomialWithMonomial(MonomialPtr first, MonomialPtr second)
{
    int coefficient = first->coefficient * second->coefficient;
    int power       = first->power       * second->power;

    return CreateMonomial(coefficient, power);
}

PolynomialHeadPtr Sum(const PolynomialHeadPtr firstHead, const PolynomialHeadPtr secondHead)
{
    PolynomialHeadPtr newPolynomialHead = CreateZeroPolynomial();

    MonomialPtr firstMonomial  = firstHead->next;
    MonomialPtr secondMonomial = secondHead->next;
    while (!IsOutOfRange(firstMonomial) || !IsOutOfRange(secondMonomial))
    {
        if (!IsOutOfRange(firstMonomial))
        {
            SumPolynomialWithMonomial(newPolynomialHead, CloneMonomial_withoutNext(firstMonomial));
            SetToNext(&firstMonomial);
        }
        else 
        {
            SumPolynomialWithMonomial(newPolynomialHead, CloneMonomial_withoutNext(secondMonomial));
            SetToNext(&secondMonomial);
        }
    }

    return newPolynomialHead;
}
PolynomialHeadPtr Multiply(const PolynomialHeadPtr firstHead, const PolynomialHeadPtr secondHead)
{
    PolynomialHeadPtr newPolynomialHead = CreateZeroPolynomial();
    
    for (MonomialPtr current_first = firstHead->next; !IsOutOfRange(current_first); SetToNext(&current_first))
    {
        for (MonomialPtr current_second = secondHead->next; !IsOutOfRange(current_second); SetToNext(&current_second))
        {
            SumPolynomialWithMonomial(newPolynomialHead, MultiplyMonomialWithMonomial(current_first, current_second));
        }
    }

    return newPolynomialHead;
}

int main()
{
    PolynomialHeadPtr polynomial_1 = CreateZeroPolynomial();
    AddMonomialToPolynomial(polynomial_1, CreateMonomial(10, 4));
    AddMonomialToPolynomial(polynomial_1, CreateMonomial(6,  2));
    AddMonomialToPolynomial(polynomial_1, CreateMonomial(2,  1));
    AddMonomialToPolynomial(polynomial_1, CreateMonomial(7,  6));

    PolynomialHeadPtr polynomial_2 = CreateZeroPolynomial();
    AddMonomialToPolynomial(polynomial_2, CreateMonomial(9,  3));
    AddMonomialToPolynomial(polynomial_2, CreateMonomial(1,  1));
    AddMonomialToPolynomial(polynomial_2, CreateMonomial(-5, 9));

    PolynomialHeadPtr polynomial = Sum(polynomial_1, polynomial_2);
    PolynomialHeadPtr polyMulti = Multiply(polynomial_1, polynomial_2);
}
