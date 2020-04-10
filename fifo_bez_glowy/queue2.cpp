#include "queue2.h"

FQueue* QFCreate()
{
	FQueue* Que = ( FQueue* )calloc( 1, sizeof( FQueue ) );
	if( !Que )
	{
		perror( "Blad alokacji pamieci!!!***QFCreate***" );
		return NULL;
	}
	//Que->pHead = NULL;
	//Que->pTail = NULL;
	return Que;
}


void QFEnqueue( FQueue* q, int x )
{
	FQITEM* elem = ( FQITEM* )calloc( 1, sizeof( FQITEM ) );
	if( !elem )
	{
		perror( "Blad alokacji pamieci!!!***QFEnqueue***" );
	}
	elem->nKey = x;			//tworzymy nowy wêze³ i przypisujemy mu wartoœæ
	elem->pNext = NULL;
	
	if( QFEmpty( q ) )		//jeœli wstawiam pierwszy element
	{
		q->pHead = elem;			//jest to pierwszy element wiêc ustawiam pHead na niego
		//q->pTail = elem;                //jest to te¿ ostatni element
	}
	else
	{
		q->pTail->pNext = elem;
		//q->pTail = elem; 
	}
	q->pTail = elem;

}


int QFDequeue( FQueue* q ) //bez zwalniania pamiêci
{
	//FQITEM* temp = q->pHead;
	FQITEM* ret = q->pHead;				//zapisujemy element ¿eby go zwróciæ

	if (!QFEmpty( q ))				//jeœli nie jest pusta
	{
		//FQITEM* ret = q->pHead;				//zapisujemy element ¿eby go zwróciæ
		//q->pHead = q->pHead->pNext;			//przesuwamy head dalej
		int x = q->pHead->nKey;
		QFDel( q );
		if( QFEmpty( q ) )  q->pHead=q->pTail = NULL;	//jeœli to by³ ostani element to ustawiamy tail na nulla
		return x;
	}
	perror( "Queue is already empty !!QFDequeue!!" );
	return 0;

}

/*FQITEM* QFDequeue( FQueue* q ) //bez zwalniania pamiêci
{
	FQITEM* temp = q->pHead;
	if( QFEmpty( q ) )
	{
		perror( "Queue is already empty !!QFDequeue!!" );
		return NULL;
	}
	if( q->pHead == q->pTail )				//jeœli jest tylko jeden element
	{
		q->pHead = NULL;
		q->pTail = NULL;
		return temp;
	}
	
	q->pHead = temp->pNext;//przesuwam pHead dalej
	return temp;
	
}*/



int QFEmpty( FQueue* q )
{
	return( !( q->pHead ) );
}

void QFClear( FQueue* q ) //frees memory for queue items
{
	while( !QFEmpty(q))
		QFDel( q );
	//!!!
}

void QFRemove( FQueue** q )
{
	QFClear( *q );
	free( *q );
	*q = NULL;
}
void QFDel( FQueue* q )
{
	FQITEM* temp = q->pHead;
	if (!QFEmpty( q ))
	{
		temp = q->pHead; // podczepiamy pierwszy element kolejki
		q->pHead = temp->pNext; // przesuwamy wskaŸnik pHead na kolejny element kolejki
		free( temp );
	}
}



/*void QFDel( FQueue* q )
{
	FQITEM* temp = q->pHead;
	if (!QFEmpty( q ))
	{
		perror( "Queue is already empty !!QFDEL!!" );
		return;
	}
	if (q->pHead == q->pTail)			//sprawdzam czy to ostatni element
	{
		free( temp );
		temp = q->pHead = q->pTail = NULL;		//ustawiamy wszystko na null bo nie ma juz elementow w kolejce
		return;
	}
	q->pHead = temp->pNext;
	free( temp ); //czyscimy usuwany element
	temp = N*/