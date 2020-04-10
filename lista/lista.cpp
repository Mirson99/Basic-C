#include "list.h"

#define RAND 101
int compare( const void* p, const void *v );			// funkcja porównuje dwie wartości
int main()
{
	ListItem *pHead = CreateList();   //tworzę listę 

	srand( ( unsigned int )time( NULL ) );

	for( int i = 0; i < 10; i++ )  //dodaje elementy listy
	{
		LISTINFO* data = ( LISTINFO* )malloc( sizeof( LISTINFO ) );
		data->nKey = rand() % RAND;									//losuje elementy do listy
		InsertFront( pHead, data );									//umieszczam je po kolei w liście
	}
	PrintList( pHead );

	SortList( pHead, compare );
	PrintList( pHead );

	LISTINFO* x = ( LISTINFO* )malloc( sizeof( LISTINFO ) );
	x->nKey = 99;											//tworzę nowy węzeł
	Insert( pHead->m_pNext->m_pNext, x );						//wkładam go na trzecie miejsce na liście
	PrintList( pHead );

	ListItem* previous = NULL;

	Find( pHead, x, &previous, compare );
	Remove( previous );									//znajduję element który dodałem i go usuwam
	PrintList( pHead );

	x = NULL;
	previous = NULL;
	DelList( &pHead );


}



int compare( const void* p, const void* v )
{
	//printf( "%d", ((ListItem*)p)->m_pInfo->nKey );
	//printf( "\n" );
	//printf( "%d", ((ListItem*)v)->m_pInfo->nKey );
	//printf( "\n" );
	//if ((((ListItem*)p)->m_pInfo->nKey) == (((ListItem*)v)->m_pInfo->nKey))
		//return 0;
	//else if ((((ListItem*)p)->m_pInfo->nKey) > (((ListItem*)v)->m_pInfo->nKey))
		//return 1;
	//else return -1;
	if( ( ( ( LISTINFO* )p )->nKey ) == ( ( ( LISTINFO* )v )->nKey ) )
		return 0;
	else if( ( ( ( LISTINFO* )p )->nKey ) > ( ( ( LISTINFO* )v )->nKey ) )
		return 1;
	else return -1;
}




