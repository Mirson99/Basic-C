// prior.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include "prior.h"
#include "pch.h"
#include <iostream>

int main()
{
	PQueue* Que = PQInit(MAX);
	srand( ( unsigned int )time( NULL ) );
	for( int i = 0; i < 7; i++ )
	{
		QPRIORINFO* x = (QPRIORINFO*)calloc( 1, sizeof( QPRIORINFO ) );
		x->nKey = rand() % MAX;
		//x->nKey = i;
		//int prior = i+5;
		PQEnqueue( Que, x, rand() % MAX );
	}
	PQPrint( Que );
	
	printf( "Przechodze kolejke in-order: \n" );
	inorder( Que, 0 );
	printf( "\n" );
	printf( "Dodaje wezel o priorytecie 5 i wartosci 3 do kolejki\n" );
	QPRIORINFO* x = (QPRIORINFO*)calloc( 1, sizeof( QPRIORINFO ) );
	x->nKey = 3;
	PQEnqueue( Que, x, 5 );
	PQPrint( Que );

	printf( "Zwiekszam priorytet trzeciego elementu na 10\n" );
	IncreaseKey( Que, 2, 10 );
	PQPrint( Que );

	printf( "Usuwam element o najwiekszym priorytecie\n" );
	PQDequeue( Que );
	PQPrint( Que );

	PQClearQueue( Que );
	PQRelease( &Que );
}


