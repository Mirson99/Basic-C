#ifndef DSTACK_H
#define DSTACK_H

#include <stdlib.h>
#include <iostream>


typedef struct tagDStackItem{
	
	char fKey;
	tagDStackItem *pNext;

} DStackItem;


void dmakeEmptyStack ( DStackItem **pStack );
void dpush ( DStackItem **pStack, char c );
char dpop ( DStackItem **pStack ); // parametr we/wy
char dtop ( DStackItem *pStack ); // parametr we
void ddel ( DStackItem **pStack );
int isDEmpty ( DStackItem *pStack );


#endif


