#include "list.h"

ListItem* CreateList()
{
	ListItem* pHead = ( ListItem* )malloc( sizeof( ListItem ) );  //tworzymy pierwszy element na li�cie na razie pusty
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

	/*ListItem* temp = ( ListItem* )malloc( sizeof( ListItem ) );	//rezerwujemy miejsce na nowy w�ze�
	if( !temp )
	{
		perror( "Blad alokacji pamieci" );
		return;
	}
	temp->m_pInfo = pInfo;										//wpisujemy warto�� liczbow� do nowego w�z�a
	temp->m_pNext = pHead->m_pNext;							//sprawiamy aby w�ze� wskazywa� na dotychczasowy pierwszy w�ze�, kt�ry przesuwa si� na drugie miejsce
	pHead->m_pNext = temp;*/										//sprawiamy aby pHead wskazywa� na nasz nowy w�ze� kt�ry jest teraz pierwszy
}

void RemoveFront( ListItem* pHead )
{
	Remove( pHead ); //nie powielamy kodu
	/*if (!isEmpty( pHead ))
	{
		ListItem* temp = pHead->m_pNext;                          //ustawiamy temp �e wskazuje na pierwszy w�ze�
		pHead->m_pNext = temp->m_pNext;					//ustawiamy pHead �e wskazuje na drugi z kolei w�ze�
		free( temp->m_pInfo );                          //kasujemy warto�� pierwsz�
		free( temp );									//sprz�tamy temp
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

	ListItem* temp =( ListItem* )malloc( sizeof( ListItem ) );   //rezerwujemy miejsce na nowy w�ze�
	if( !temp )
	{
		perror( "B��d alokacji pami�ci" );
		return;
	}
	temp->m_pInfo = pInfo;										//wpisujemy warto�� liczbow� do nowego w�z�a
	temp->m_pNext = p->m_pNext;							//sprawiamy aby w�ze� wskazywa� na dotychczasowy pierwszy w�ze�, kt�ry przesuwa si� na drugie miejsce
	p->m_pNext = temp;										//sprawiamy aby pHead wskazywa� na nasz nowy w�ze� kt�ry jest teraz pierwszy
}

void Remove( ListItem* p )
{
	if (isEmpty( p ))
	{
		perror( "Unable to allocate memory for temporary pointer (Remove)" );
		return;
	}
	ListItem* temp = p->m_pNext;                          //ustawiamy temp �e wskazuje na pierwszy w�ze�
	p->m_pNext = temp->m_pNext;					//ustawiamy pHead �e wskazuje na drugi z kolei w�ze�
	free( temp->m_pInfo );                          //kasujemy warto�� pierwsz�
	free( temp );
	
	
}

void DelElements( ListItem* pHead )
{
	while( !isEmpty( pHead ))
	{
		RemoveFront( pHead );           //usuwamy po jednym elemencie dop�ki nie b�dzie pusta
	}
}

int isEmpty( ListItem* pHead )
{
	return  !( pHead->m_pNext );      //sprawdzamy czy pHead wskazuje na jaki� element
}

void DelList( ListItem** p )
{
	DelElements( *p );
	free( *p );
	*p = NULL;
}




ListItem* Find( ListItem *pHead, const void* value, ListItem** previous, pointer_to_compare compare )
{
	ListItem* temp = pHead->m_pNext;				//temp b�dzie wskazywa�o na w�ze� z wyszukiwanym elementem	
	*previous = pHead;					//a previous na w�ze� przed wyszukiwanym
	while( temp != NULL )
	{
		if( compare( ( const void* )( temp->m_pInfo ), value ) == 0)
		{
			*previous = temp;
			temp = temp->m_pNext;
			return temp;				//je�li chcieliby�my zwroci� wska�nik na szukany wezel
			//return *previous;					//a teraz zwracam element poprzedzaj�cy wyszukiwany
		}
		temp = temp->m_pNext;

	}
	
	return *previous = NULL;	//jesli nie znaleziono szukanego elementu to zwraca si� NULL
}


void SortList( ListItem* pHead, pointer_to_compare compare )
{
	while( pHead->m_pNext != NULL )
	{
		ListItem* beforemin = pHead;        //domy�lnie ma si� znale�� na strukturze, kt�ra jest przed struktur� z minimaln� warto�ci�
		ListItem* pTemp = beforemin->m_pNext;			//przechodzi po wszystkich strukturach aby por�wna� z beforemin
		while( ( pTemp->m_pNext ) != NULL )
		{
			if(compare( (const void*)(pTemp->m_pNext->m_pInfo), (const void*)(beforemin->m_pNext->m_pInfo) ) == -1 )
				beforemin = pTemp;			//umieszczamy before na w�le przed min
			pTemp = pTemp->m_pNext;			//por�wnujemy kolejne elementy

		}
		if( pHead != beforemin  )							//pierwszy element nie by� najmniejszy zatem musimy poprzeplata� wska�niki
		{
			ListItem* min = beforemin->m_pNext;		//wskazuje na w�ze� w kt�rym jest minimum
			beforemin->m_pNext = min->m_pNext;		//przewi�zujemy w�ze� przed min aby wskazywa� na w�ze� po min
			min->m_pNext = pHead->m_pNext;			//przewi�zujemy w�ze� zawieraj�cy min na pocz�tek nieposortowanej cz�ci
			pHead->m_pNext = min;					//ustawiamy g�ow� na �eby wskazywa�a na min kt�re jest teraz na pierwszym miejscu
			
		}
		pHead = pHead->m_pNext;				//przechodzimy dalej, w�z�y za nami s� ju� posortowane
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