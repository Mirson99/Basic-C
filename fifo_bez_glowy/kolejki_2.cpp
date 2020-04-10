#include "queue2.h"
#include <iostream>
void Print( FQueue* p );
int main()
{
	FQueue* Queue = QFCreate();
	QFEnqueue( Queue, 1 );
	QFEnqueue( Queue, 2 );
	QFEnqueue( Queue, 3 );
	Print( Queue );
	//printf( "%d\n", Queue->pHead->nKey );
	//printf( "%d\n", Queue->pTail->nKey );
	printf("%d\n", QFDequeue( Queue ));
	Print( Queue );

	printf( "%d\n", QFDequeue( Queue ));
	Print( Queue );
	
	//printf( "%d\n", QFDequeue( Queue )->nKey );

	//QFDel( Queue );
	QFRemove( &Queue );


}

void Print( FQueue* p )
{
	if (QFEmpty( p ))
	{
		printf( "Queue is empty..." );
	}
	FQITEM* temp = p->pHead;
	while (temp)
	{
		printf( "%d ", temp->nKey);
		temp = temp->pNext;
	}
	printf( "\n" );
}