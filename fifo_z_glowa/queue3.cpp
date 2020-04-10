#include "queue3.h"


FQueue* QFCreate()
{
	FQueue* Que = ( FQueue* )calloc( 1, sizeof( FQueue ) );
	if( !Que )
	{
		perror( "Blad alokacji pamieci" );
		return NULL;
	}
	FQITEM* f_node = ( FQITEM* )calloc( 1, sizeof( FQITEM ) );  //pusty wêze³ który bêdzie zawsze napierwszym miejscu
	if (!f_node)
	{
		free( Que );
		perror( "Blad alokacji pamieci!!!***QFCreate***" );
		return NULL;
	}
	//f_node->pNext = NULL;
	Que->pHead = Que->pTail = f_node;
	return Que;
}


void QFEnqueue( FQueue* q, int x )
{
	FQITEM* node = (FQITEM*)calloc( 1, sizeof( FQITEM ) );
	if (!node)
	{
		perror( "Blad alokacji pamieci!!!***QFEnqueue***" );
		return;
	}
	node->nKey = x;
	node->pNext = NULL;

	/*if (QFEmpty( q ))		//jeœli wstawiam pierwszy element
	{
		q->pHead = node;			//jest to pierwszy element wiêc ustawiam pHead na niego
		q->pTail = node;                //jest to te¿ ostatni element
	}*/
	
	q->pTail->pNext = node;
	q->pTail = node;
	

}

int QFEmpty( FQueue* q )
{
	return(!(q->pHead->pNext));
}

int QFDequeue( FQueue* q ) //bez zwalniania pamieci
{
	if (!QFEmpty( q ))				//jeœli nie jest pusta
	{
		//FQITEM* ret = q->pHead->pNext;				//zapisujemy element ¿eby go zwróciæ
		//q->pHead = q->pHead->pNext;			//przesuwamy head dalej
		int x = q->pHead->pNext->nKey;
		QFDel( q );
		if (QFEmpty( q ))  q->pTail = q->pHead;	//jeœli to by³ ostani element to ustawiamy tail na heada
		return x;
	}
	perror( "Queue is already empty !!QFDequeue!!" );
	return NULL;
}
/*FQITEM* QFDequeue( FQueue* q ) //bez zwalniania pamiêci
{
	FQITEM* temp = q->pHead->pNext;
	if (QFEmpty( q ))
	{
		perror( "Queue is already empty !!QFDequeue!!" );
		return NULL;
	}
	if( q->pHead->pNext == q->pTail )					//jeœli usuwamy ostatni element
	{
		q->pTail = q->pHead;
	}
	q->pHead->pNext = temp->pNext;
	return temp;

}*/


void QFClear( FQueue* q ) //frees memory for queue items
{

	while (!QFEmpty( q ))
		QFDel( q );

}

void QFRemove( FQueue** q )
{
	QFClear( *q );
	free( (*q)->pHead ); //zwalniam wartownika
	free( *q );
	*q = NULL;
}
void QFDel( FQueue* q )
{
	if (!QFEmpty( q ))
	{
		FQITEM* temp = q->pHead->pNext;
		q->pHead->pNext = temp->pNext;
		free( temp );
		if (QFEmpty( q )) q->pTail = q->pHead;
	}
}


/*void QFDel( FQueue* q )
{

	if (QFEmpty( q ))
	{
		perror( "Queue is already empty !!QFDequeue!!" );
		return;
	}
	FQITEM* temp = q->pHead->pNext;

	/*if (q->pHead == q->pTail)
	{
		free( temp );
		q->pHead = NULL;
		q->pTail = NULL;
	}
	q->pHead->pNext = temp->pNext;
	free( temp );
	if (QFEmpty( q ))
	{
		q->pTail = q->pHead;
	}

}*/