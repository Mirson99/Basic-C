#include "pch.h"
#include "queue.h"
#include <iostream>

void PrintQueue( FQueue* q );
int main()
{
	FQueue* Que = QFCreate(10);
	for (int i = 0; i < Que->MaxSize; i++)			//wypelniamy kolejke
	{
		FQIFOITEM* y = ( FQIFOITEM* )calloc( 1, sizeof( FQIFOITEM ) );
		y->nKey = i;
		QFEnqueue( Que, y );
	}				//wypelniam kolejke
	PrintQueue( Que );
	
	FQIFOITEM* ret = ( FQIFOITEM* )calloc( 1, sizeof( FQIFOITEM ) );
	ret = QFDequeue( Que );
	printf( "Usuwam wartosc: %d\n", ret->nKey );
	PrintQueue( Que );
	
	FQIFOITEM* w = ( FQIFOITEM* )calloc( 1, sizeof( FQIFOITEM ) );
	w = QFDequeue( Que );
	printf( "Usuwam wartosc: %d\n", w->nKey );
	PrintQueue( Que );

	FQIFOITEM* z = ( FQIFOITEM* )calloc( 1, sizeof( FQIFOITEM ) );
	z->nKey = 12;
	QFEnqueue( Que, z );
	PrintQueue( Que );
	//printf( "%d ", Que->nTail );
	//printf( "%d", Que->nHead );
	//PrintQueue( Que );
	
	QFClear( Que );
	QFRemove( &Que );

	free( ret );
}


void PrintQueue( FQueue* q )
{
	printf( "Rozmiar tablicy: %d\n", q->actSize );
	/*for (int i = q->nHead, j = q ->actSize; j>0; --j, i = ((i+1) % MAX))
	{
		FQIFOITEM* temp = q->pQueue + i;					//czytamy wartosci za pomoca wskaznika pomocniczego
		printf( "%d ", temp->nKey );
	}*/
	for( int i = q->nHead, j= q->actSize ; j>0 ; --j, i=( ( i+1 )%q->MaxSize ) )
	{
		printf( "%d ", q->pQueue[i]->nKey );
	}
	printf( "\n" );

}