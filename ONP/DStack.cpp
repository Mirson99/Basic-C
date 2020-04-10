#include "DStack.h"
#include <stdlib.h>
using namespace std;

void dmakeEmptyStack ( DStackItem **pStack )
{
	while( !isDEmpty(*pStack) ) ddel( pStack );
	*pStack = NULL;

}
/*void dpush ( DStackItem **pStack,  double x )
{
	DStackItem* p = ( DStackItem* ) malloc ( sizeof ( DStackItem ) ); // malloc rezerwuje nam nowy obszar
	if( p )   													// w pamiêci na który zwraca nam adres 
	{
		p->fKey = x;
		p->pNext = *pStack;}//przypisujemy do pNext wskaŸnik pHead który wskazuje na wczeœniejszy element na stosie
		*pStack = p; // teraz pHead bêdzie wskazywa³ na nowo utworzony element
	}
	*/
void dpush(DStackItem** pStack, char c)
{
	DStackItem* p = (DStackItem*)malloc(sizeof(DStackItem));
	if (p) {
		p->fKey = c; //cKey ma wartoœæ nowego operatora
		p->pNext = *pStack; // pNext wskazuje na wczesniejszy operator
		*pStack = p; // pHead wskazuje na aktualny operator
	}
	else
	{

		cout << "Stack overflow!\n\n'";
	}
}

/*double dpop ( DStackItem **pStack ) // parametr we/wy
{
	double x = dtop ( *pStack ); // bierzemy wartosc pHead (pierwszy element na stosie)
	if( !isDEmpty( *pStack ) )
		ddel ( pStack ); // usuwamy orygina³ (pHead)
	else
		cout << "\n\n *!* Stack underflow!! (dpop) \n\n";
	return x; //zrzucilismy x ze stosu
}*/
char dpop(DStackItem** pStack)
{
	char c = dtop(*pStack); //sciagamy pierwszy operator ze stosu
	if (c)//!isempty()
		ddel(pStack);
	else
		cout << "Stack underflow! pop() \n\n";
	return c;
}
/*double dtop ( DStackItem *pStack ) // parametr we
{
	if( !isDEmpty ( pStack ) )
		return pStack->fKey;
	cout << "\n\n *!* Stack underflow!! (dtop) \n\n";
	return 0;
}*/

char dtop(DStackItem* pStack)	//dla stosu znakowego nie wypisuje bledu gdy stos jest pusty, ale zwracamy znak o kodzie 0 co odpowiada wartosci FALSE
{
	if (!isDEmpty(pStack))
		return pStack->fKey;
	return 0;
}
void ddel ( DStackItem **pStack )
{
	if( !isDEmpty ( *pStack ) )
	{
		DStackItem *p = *pStack; // przypisujemy to co chcemy usun¹æ
		*pStack = p->pNext; // przekierowujemy pHead na element wczeœniejszy
		free ( p ); // zwalniamy miejsce w pamiêci
	}
	else
		cout << "\n *!* Stack underflow!! ( ddel )\n\n";
}
int isDEmpty ( DStackItem *pStack )
{
	return !pStack;
}