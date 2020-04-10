#include "list.h"

ListItem* CreateList()
{
	ListItem* pHead = ( ListItem* )malloc( sizeof( ListItem ) );  //tworzymy pierwszy element na liœcie na razie pusty
	if( !pHead )
	{
		perror( "Blad alokacji pamieci!!!" );
		return NULL;
	}
	pHead->m_pInfo = NULL;
	pHead->m_pNext = NULL;
	return pHead;
}


ListItem* Front( ListItem* p ) //zwraca wskaznik na pierwszy wlasciwy element listy
{
	if (isEmpty( p ))
	{
		perror( "List is empty, unable to return pointer to first element (Front)" );
		return NULL;
	}
	return p->m_pNext;
}

void InsertFront( ListItem* pHead, LISTINFO* pInfo )
{
	Insert( pHead, pInfo ); //nie powielamy kodu

	/*ListItem* temp = ( ListItem* )malloc( sizeof( ListItem ) );	//rezerwujemy miejsce na nowy wêze³
	if( !temp )
	{
		perror( "Blad alokacji pamieci" );
		return;
	}
	temp->m_pInfo = pInfo;										//wpisujemy wartoœæ liczbow¹ do nowego wêz³a
	temp->m_pNext = pHead->m_pNext;							//sprawiamy aby wêze³ wskazywa³ na dotychczasowy pierwszy wêze³, który przesuwa siê na drugie miejsce
	pHead->m_pNext = temp;*/										//sprawiamy aby pHead wskazywa³ na nasz nowy wêze³ który jest teraz pierwszy
}

void RemoveFront( ListItem* pHead )
{
	Remove( pHead ); //nie powielamy kodu
	/*if (!isEmpty( pHead ))
	{
		ListItem* temp = pHead->m_pNext;                          //ustawiamy temp ¿e wskazuje na pierwszy wêze³
		pHead->m_pNext = temp->m_pNext;					//ustawiamy pHead ¿e wskazuje na drugi z kolei wêze³
		free( temp->m_pInfo );                          //kasujemy wartoœæ pierwsz¹
		free( temp );									//sprz¹tamy temp
	}
	else
	{
		perror( "List is empty!" );
	}*/
}

void Insert( ListItem* p, LISTINFO* pInfo )
{
	if (p == NULL)
	{
		perror( "pointer is NULL, propably unable to find element to insert after (Insert)" );
		return;
	}

	ListItem* temp =( ListItem* )malloc( sizeof( ListItem ) );   //rezerwujemy miejsce na nowy wêze³
	if( !temp )
	{
		perror( "B³¹d alokacji pamiêci" );
		return;
	}
	temp->m_pInfo = pInfo;										//wpisujemy wartoœæ liczbow¹ do nowego wêz³a
	temp->m_pNext = p->m_pNext;							//sprawiamy aby wêze³ wskazywa³ na dotychczasowy pierwszy wêze³, który przesuwa siê na drugie miejsce
	p->m_pNext = temp;										//sprawiamy aby pHead wskazywa³ na nasz nowy wêze³ który jest teraz pierwszy
}

void Remove( ListItem* p )
{
	if (isEmpty( p ))
	{
		perror( "Unable to allocate memory for temporary pointer (Remove)" );
		return;
	}
	ListItem* temp = p->m_pNext;                          //ustawiamy temp ¿e wskazuje na pierwszy wêze³
	p->m_pNext = temp->m_pNext;					//ustawiamy pHead ¿e wskazuje na drugi z kolei wêze³
	free( temp->m_pInfo );                          //kasujemy wartoœæ pierwsz¹
	free( temp );
	
	
}

void DelElements( ListItem* pHead )
{
	while( !isEmpty( pHead ))
	{
		RemoveFront( pHead );           //usuwamy po jednym elemencie dopóki nie bêdzie pusta
	}
}

int isEmpty( ListItem* pHead )
{
	return  !( pHead->m_pNext );      //sprawdzamy czy pHead wskazuje na jakiœ element
}

void DelList( ListItem** p )
{
	DelElements( *p );
	free( *p );
	*p = NULL;
}




ListItem* Find( ListItem *pHead, const void* value, ListItem** previous, pointer_to_compare compare )
{
	ListItem* temp = pHead->m_pNext;				//temp bêdzie wskazywa³o na wêze³ z wyszukiwanym elementem	
	*previous = pHead;					//a previous na wêze³ przed wyszukiwanym
	while( temp != NULL )
	{
		if( compare( ( const void* )( temp->m_pInfo ), value ) == 0)
		{
			*previous = temp;
			temp = temp->m_pNext;
			return temp;				//jeœli chcielibyœmy zwrociæ wskaŸnik na szukany wezel
			//return *previous;					//a teraz zwracam element poprzedzaj¹cy wyszukiwany
		}
		temp = temp->m_pNext;

	}
	
	return *previous = NULL;	//jesli nie znaleziono szukanego elementu to zwraca siê NULL
}


void SortList( ListItem* pHead, pointer_to_compare compare )
{
	while( pHead->m_pNext != NULL )
	{
		ListItem* beforemin = pHead;        //domyœlnie ma siê znaleŸæ na strukturze, która jest przed struktur¹ z minimaln¹ wartoœci¹
		ListItem* pTemp = beforemin->m_pNext;			//przechodzi po wszystkich strukturach aby porównaæ z beforemin
		while( ( pTemp->m_pNext ) != NULL )
		{
			if(compare( (const void*)(pTemp->m_pNext->m_pInfo), (const void*)(beforemin->m_pNext->m_pInfo) ) == -1 )
				beforemin = pTemp;			//umieszczamy before na wêŸle przed min
			pTemp = pTemp->m_pNext;			//porównujemy kolejne elementy

		}
		if( pHead != beforemin  )							//pierwszy element nie by³ najmniejszy zatem musimy poprzeplataæ wskaŸniki
		{
			ListItem* min = beforemin->m_pNext;		//wskazuje na wêze³ w którym jest minimum
			beforemin->m_pNext = min->m_pNext;		//przewi¹zujemy wêze³ przed min aby wskazywa³ na wêze³ po min
			min->m_pNext = pHead->m_pNext;			//przewi¹zujemy wêze³ zawieraj¹cy min na pocz¹tek nieposortowanej czêœci
			pHead->m_pNext = min;					//ustawiamy g³owê na ¿eby wskazywa³a na min które jest teraz na pierwszym miejscu
			
		}
		pHead = pHead->m_pNext;				//przechodzimy dalej, wêz³y za nami s¹ ju¿ posortowane
	}
}

void PrintList( ListItem* pHead )
{
	if ((pHead == NULL) || isEmpty( pHead ))
	{
		perror( "List is empty, or pointer is null, can't print (PrintList)" );
		return;
	}
	ListItem* temp = pHead;
	while (temp->m_pNext)
	{
		printf( "%d ", temp->m_pNext->m_pInfo->nKey );
		temp = temp->m_pNext;
	}
	printf( "\n" );
}