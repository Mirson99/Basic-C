
#include "queue3.h"
#include <iostream>

void Print( FQueue* p );

int main()
{
	FQueue* Queue = QFCreate();
	printf( "Is empty: %d\n ", QFEmpty( Queue ) );
	QFEnqueue( Queue, 1 );
	QFEnqueue( Queue, 2 );
	QFEnqueue( Queue, 3 );
	Print( Queue );
	//printf( "%d\n", Queue->pHead->nKey );
	//printf( "%d\n", Queue->pTail->nKey );
	printf("%d\n", QFDequeue( Queue ));
	//QFDel( Queue );
	Print( Queue );
	//QFClear( Queue );
	printf( "%d\n", QFDequeue( Queue ));
	Print( Queue );
	printf( "%d\n", QFDequeue( Queue ));
	Print( Queue );
	QFClear( Queue );
	QFRemove( &Queue );
}




void Print( FQueue* p )
{
	FQItem* temp = p->pHead->pNext;
	while (temp)
	{
		printf( "%d ", temp->nKey );
		temp = temp->pNext;
	}
	printf( "\n" );
}