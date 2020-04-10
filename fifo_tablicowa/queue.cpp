#include "queue.h"
void QFDel( FQueue* q );  //usuwa pierwszy element

FQueue* QFCreate( int Max )
{
	FQueue* Que = ( FQueue* )calloc( 1, sizeof( FQueue ) );
	if( !Que )
	{
		perror( "Blad alokacji pamieci!!!***QFCreate" );
	}
	Que->pQueue =( FQIFOITEM** )calloc( Max, sizeof( FQIFOITEM* ) ); //tworzymy tablice wskaznikow na strukture z wartoscia
	if( !Que->pQueue )
	{
		free( Que );
		perror( "Blad alokacji pamieci!!!***QFCreate" );
		return;
	}
	Que->MaxSize = Max;
	return Que;
}

void QFEnqueue( FQueue* q, FQIFOITEM* pInfo )
{
	if( q->actSize== q->MaxSize)			//sprawdzamy czy jest miejsce w kolejce
	{
		perror( "ERROR queue is overflow (QFEnqueue)" );
		return;
	}

	//q->pQueue += (q-> nTail + MAX - 1) % MAX;
	//q->pQueue[x]->nKey = pInfo->nKey;
	q->pQueue[ q->nTail ] = pInfo;				//wstawiamy element na ostatnie miejsce
	q->nTail = ( q->nTail + 1 ) % q->MaxSize;			//przestawiamy nTail
	q->actSize++;								//zwiekszamy aktualny rozmiar

}

FQIFOITEM* QFDequeue( FQueue* q )
{
	if( QFEmpty( q ) )							//sprawdzamy czy kolejka nie jest pusta
	{
		perror( "Queue is empty (QFDequeue)" );
		return NULL;
	}
	q->actSize--;
	FQIFOITEM* deleted_el = q->pQueue[q->nHead];	//zapisuje aby miec co zwrocic
	q->pQueue[ q->nHead ] = NULL;				
	q->nHead = ( q->nHead +1 ) % q->MaxSize;			//przestawiamy nHead na kolejny indeks
	//q->actSize--;								//zmniejszamy rozmiar
	//return ((q->pQueue) + ((q->nHead)-1))->;		
	return deleted_el;
}


int QFEmpty( FQueue* q )
{
	return !( q->actSize );
}



void QFClear( FQueue* q )
{
	//free( q->pQueue );
	//memset( q, 0, sizeof( FQueue ) );
	while (!QFEmpty( q ))
		QFDel( q );
	q->nHead = q->nTail = 0;
}

void QFRemove( FQueue** q )
{
	QFClear( *q );
	free( (*q)->pQueue );
	//q->pQueue = NULL;
	free( *q );
	*q = NULL;

}


void QFDel( FQueue* q ) //usuwanie pierwszego elementu
{
	free( q->pQueue[ q->nHead ] );
	q->pQueue[q->nHead] = NULL;
	//memset( q->pQueue[ q->nHead ], 0, sizeof( FQIFOITEM ) );
	q->nHead = ( q->nHead + 1 ) % q->MaxSize;		//zwiekszam head
	q->actSize--;							//zmniejszam rozmiar
}
