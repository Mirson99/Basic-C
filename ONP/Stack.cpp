#include "stack.h"





StackItem* pHead = NULL; //stos pusty

void push(StackItem** pStack, char c)
{
	StackItem* p = (StackItem*)malloc(sizeof(StackItem));
	if (p) {
		p->cKey = c; //cKey ma wartoœæ nowego operatora
		p->pNext = *pStack; // pNext wskazuje na wczesniejszy operator
		*pStack = p; // pHead wskazuje na aktualny operator
	} else
	{
		cout << "Stack overflow!\n\n'";
	}
}
char pop(StackItem** pStack)
{
	char c = top(*pStack); //sciagamy pierwszy operator ze stosu
	if (c)//!isempty()
		del(pStack);
	else
		cout << "Stack underflow! pop() \n\n";
	return c;
}
char top(StackItem* pStack)	//dla stosu znakowego nie wypisuje bledu gdy stos jest pusty, ale zwracamy znak o kodzie 0 co odpowiada wartosci FALSE
{
	if (!isEmpty(pStack))
		return pStack -> cKey;
	return 0;
}
void del(StackItem** pStack)
{
	if (!isEmpty(*pStack))
	{
		StackItem* p = *pStack;
		*pStack = (*pStack)->pNext;
		free(p);
	}
	else
		cout << "Stack underflow! del() \n\n";
}
int isEmpty(StackItem* pStack)
{
	return !pStack;
}

void makeEmptyStack(StackItem** pStack)
{
	while (!isEmpty(*pStack)) del(pStack);// memset(Stack, 0, MAXSTACK * sizeof(char)); //wypelnia bajty tablicy zerami     |	 (gdzie - nazwa tablicy to adres jej pierwszej komorki, czym, ilezamienic) 
	//nHead = 0;
	pStack = NULL;
}

//