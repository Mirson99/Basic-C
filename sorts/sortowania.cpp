#include "sort.h"
#define _DEBUG_

//void DoHeapSort( int* pTab, int nSize );
void DoBigMergeSort( int* pTab, int nSize );
void DoMergeSort( int* pTab, int nSize );

int main( int argc, char** argv )
{
	if( argc != 2 )
	{
		perror( "Nie podano rozmiaru" );
		return 1;
	}
	int nSize = atoi( argv[1] );          //zamieniamy kod ASCII na int

#ifdef _DEBUG_ 
	nSize = 10;
#endif

	int *pTab = NULL;					//tablica do której będziemy wpisywać losowe liczby
	if( !( pTab = CreateTab( nSize ) ) )
	{
		perror( "Nie udało się utworzyć tablicy" );
		return 1;
	}

	RandInit( pTab, nSize );				//wypełniam tablicę losowymi liczbami
#ifdef _DEBUG_ 
	for (int i = 0; i < nSize; i++)
		printf( "%d ", pTab[i] );
	printf( "\n" );
#endif

	int *pNewTab = NULL;                //tablica która będzie kopią pTab
	if( !( pNewTab = CreateTab( nSize ) ) )
	{
		perror( "Nie udało się utworzyć tablicy" );
		return 1;
	}

	ToSort pSort[] = { BubbleSort, MixedBubbleSort, QuickSort, HeapSort, SelectionSort, InsertionSort, HalfInsertionSort, DoMergeSort };
	int Size = sizeof( pSort ) / sizeof( ToSort );   //zmienna przechowująca liczbe sortowań w tablicy
	const char* names[] = { "BubbleSort", "MixedBubbleSort", "QuickSort", "HeapSort", "SelectionSort", "InsertionSort", "HalfInsertionSort", "MergeSort" };

	clock_t start = 0;
	clock_t stop = 0;
	double czas = 0;

	for( int i = 0; i < Size; i++ )
	{
		CopyTab( pNewTab, pTab, nSize );               //kopiujemy oryginał tablicy	i przekazujemy funkcji
		start = clock();								//punkt oznaczający start pomiaru czasu
		pSort[i]( pNewTab, nSize );						//wywołujemy funkcję
		stop = clock();									//punkt oznaczający koniec pomiaru czasu
		czas = ( double )( stop - start ) / CLOCKS_PER_SEC;
		printf( "%s: %lf s \n", names[i], czas );
#ifdef _DEBUG_ 
		for (int i = 0; i < nSize; i++)
			printf( "%d ", pNewTab[i] );
		printf( "\n" );
#endif
	}

	//**********************************************************
	//Testuje szybkość MergeSort
	/*int *pTempTab = NULL;		//tablica pomocnicza do MergeSort
	if( !( pTempTab = CreateTab( nSize ) ) )
	{
		perror( "Nie udało się utworzyć tablicy" );
		return 1;
	}
	CopyTab( pNewTab, pTab, nSize );
	start = clock();
	MergeSort( pNewTab, pTempTab, 0, nSize - 1 );
	stop = clock();
	czas = ( double )( stop - start ) / CLOCKS_PER_SEC;
	printf( "MergeSort: %lf s \n", czas );

#ifdef _DEBUG_ 
	for ( int i = 0; i < nSize; i++ )
		printf( "%d ", pNewTab[i] );
	printf( "\n" );
#endif

	FreeTab( pTempTab );
	*/

	/*************************************************************************/
	//Testuje szybkość BigMergeSort
	int *pBigTab = NULL;		//tablica pomocnicza do MergeSort
	if( !( pBigTab = CreateTab( nSize * 2 ) ) )
	{
		perror( "Nie udało się utworzyć tablicy" );
		return 1;
	}
	CopyTab( pBigTab, pTab, nSize );
	start = clock();
	//BigMergeSort( pTab, 0, nSize - 1, nSize );
	DoBigMergeSort( pBigTab, nSize );
	stop = clock();
	czas = ( double )( stop - start ) / CLOCKS_PER_SEC;
	printf( "BigMergeSort: %lf s \n", czas );

#ifdef _DEBUG_ 
	for( int i = 0; i < nSize; i++ )
		printf( "%d ", pBigTab[i] );
	printf( "\n" );
#endif

	FreeTab( &pBigTab );
	FreeTab( &pTab );
	FreeTab( &pNewTab );
	return 0;
}




void DoBigMergeSort( int* pTab, int nSize )		//tak działa
{
	BigMergeSort( pTab, 0, nSize - 1, nSize );
}

void DoMergeSort( int* pTab, int nSize )
{
	int* pTab2 = CreateTab( nSize );
	MergeSort( pTab, pTab2, 0, nSize - 1);
	FreeTab( &pTab2 );
}



