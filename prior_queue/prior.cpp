#include "prior.h"
void UpdateDown( PQueue* PQ, int l, int p );
void UpdateUp( PQueue* PQ, int l, int p );



PQueue* PQInit( int nSize )
{
	PQueue* Quee = ( PQueue* )calloc( 1, sizeof( PQueue ) );			//glowna struktury
	if( !Quee )
	{
		perror( "Blad alokacji pamieci!!!***PQInit***" );
	}
	Quee->PQCurrSize = 0;										
	Quee->PQSize = nSize;
	Quee->Queue = ( PQItem** )calloc(1,  sizeof( PQItem* ) * nSize );  //tablica wksaznikow
	if ( !( Quee->Queue ) )
	{
		perror( "Blad alokacji pamieci!!!***PQInit***" );
	}
	return Quee;
}


int PQisEmpty( PQueue* PQ )
{
	return !( PQ->PQCurrSize );
}


void PQEnqueue( PQueue* PQ, QPRIORINFO* pInfo, int nPrior )
{
	if( PQ->PQCurrSize == MAX )		//sprawdzam czy kolejka nie jest zape�niona
	{
		printf( "Kolejka jest juz pelna, nie mozna dodac!!!***PQEnqueue***" );
		return;
	}
	PQ->Queue[ PQ->PQCurrSize ] = ( PQItem* )calloc( 1, sizeof( PQItem ) ); // alokuje pami�� na strukture PQItem pojedynczo za ka�dym razem
	if (!PQ->Queue[PQ->PQCurrSize])
	{
		perror( "Blad alokacji pamieci" );
		return;
	}
	PQ->Queue[ PQ->PQCurrSize ]->pInfo = pInfo;						  
	PQ->Queue[ PQ->PQCurrSize ] -> nPrior = nPrior;					 //nadaje priorytet
	//PQ->PQCurrSize++;			
	//tak sie psuje									//dodalem element zwiekszam rozmiar
	/***************************************/
	UpdateUp( PQ, 0, PQ->PQCurrSize++ );   //przywracam warunek kopca id�c w g�r�, prawa strona aktualny koniec
}


void UpdateUp( PQueue* PQ, int l, int p )
{
	if( l == p ) return;
	//int child = p; // dziecko (ostatni element bo idziemy w gore)
	int parent = ( p - 1 ) / 2; // rodzic 
	PQItem* temp = PQ->Queue[ p ];				//u�ywam wskaznika pomocniczego zeby go nie stracic
	//przechodz� dop�ki dziecko jest wi�ksze od zera
	while( (p > 0) && (PQ->Queue[parent]->nPrior < temp->nPrior) )
	{
		//if( temp->nPrior < PQ->Queue[parent]->nPrior ) break; // dziecko musi mie� mniejszy priorytet od rodzica
		PQ->Queue[p] = PQ->Queue[parent];		//jesli priorytet dziecka jest wiekszy to rodzic idzie w d�
		//PQ->Queue[parent] = temp;
		p = parent;				//nowe dziecko					
		parent = (p - 1) / 2;	//nowy rodzic
	}
	PQ->Queue[p] = temp;

}



PQItem* PQDequeue( PQueue* PQ )
{
	if( PQisEmpty( PQ ) )
	{
		printf( "Queue is already empty!!!***PQDequeue***" );
		return NULL;
	}
	PQItem* temp = PQ->Queue[0];				//zapisuje korze� kopca aby go zwr�ci�
	
	PQ->PQCurrSize--;							//zmniejszam aktualny rozmiar
	memset( PQ->Queue[0], 0, sizeof( PQItem* ) );
	PQ->Queue[0] = PQ->Queue[PQ->PQCurrSize];	//jako korze� ustawiam ostatni element kopca
	UpdateDown( PQ, 0, PQ->PQCurrSize );		//przywracam warunek kopca id�c w d�
	return temp;								//zwracam usuni�ty element o najwi�kszym priorytecie
}


void UpdateDown( PQueue* PQ, int l, int p )		//przywracanie kopca w d�
{
	if( l == p ) return;
	//int parent = l;			//korze�
	int child = 2 * l + 1;	//lewe dziecko
	PQItem* temp = PQ->Queue[l];
	while( child <= p )				
	{
		if( child < p )					//je�li istnieje prawe dziecko
			if( PQ->Queue[ child ]->nPrior < PQ->Queue[ child + 1 ]->nPrior ) // por�wnujemy prior lewego i prawego dziecka
				child++; 
		//jesli lewe jest mniejsze to przechodzimy na prawe

		if( l > PQ->Queue[child]->nPrior ) 
			break;// prior rodzica musi by� wiekszy niz wiekszego z dzieci
		//jesli nie:
		PQ->Queue[l] = PQ->Queue[child]; // rodzicem staje sie wieksze z dzieci
		PQ->Queue[child] = temp;			//rodzic wchodzi na miejsce dziecka
		l = child; // przechodzimy na indeks dziecka
		child = (2 * l) + 1; // wyliczamy nowe dzieci
	}
}



void PQPrint( PQueue* PQ )
{
	if( PQisEmpty( PQ ) )
	{
		printf( "Kolejka jest pusta!!!***PQPrint***" );
	}
	for( int i = 0; i < PQ->PQCurrSize; i++ )
	{
		printf( "Priorytet: %d Wartosc: %d\n", PQ->Queue[i]->nPrior, PQ->Queue[i]->pInfo->nKey );
	}
	printf( "\n" );
}



void DecreaseKey( PQueue* PQ, int x, int nPrior ) //zmniejszam priorytet wybranego elementu
{
	//!!!
	if (PQ->Queue[x]->nPrior > nPrior)
	{
		PQ->Queue[x]->nPrior = nPrior;					//nadaj� wybranemu priorytetowi now� warto��
		UpdateDown( PQ, x, PQ->PQCurrSize - 1 );		//przywracam warunek kopca w d�
	}
}


void IncreaseKey( PQueue* PQ, int x, int nPrior )
{//!!!
	if (PQ->Queue[x]->nPrior < nPrior)
	{
		PQ->Queue[x]->nPrior = nPrior;					//nadaj� wybranemu priorytetowi now� warto��
		UpdateUp( PQ, 0, x );
	}//przywracam warunek kopca w g�r�
}


//Funkcje czyszcz�ce
void PQClearQueue( PQueue* PQ ) //czy�cimy miejsca w kolejce
{
	while( !PQisEmpty( PQ ) )		//dop�ki nie jest pusta
	{
		PQItem* helper = PQDequeue( PQ );		//zdejmujemy po jednym elemencie z kolejki
		free( helper );							//czyszcz� dany element
	}
}


void PQRelease( PQueue** PQ )	//ca�kowicie usuwam struktur� kolejki
{
	PQClearQueue( *PQ );		//kasuje elementy
	free( (*PQ)->Queue );		//czyszcze ca�� kolejk�
	free( *PQ );				//czyszcz� g��wn� struktur�
	*PQ = NULL;					
}


void inorder( PQueue* PQ, int root )
{
	int left = root * 2 + 1;					//lewe dziecko
	int right = root * 2 + 2;					//prawe dziecko

	if( left < PQ->PQCurrSize )					//dop�ki istnieje lewe dziecko
		inorder( PQ, left );					// przechodzimy do skrajnie lewego dziecka
	printf( "Priorytet: %d Wartosc: %d \n", PQ->Queue[root]->nPrior, PQ->Queue[root]->pInfo->nKey ); //wypisywanie
	if( right < PQ->PQCurrSize )					//gdy przeszli�my w lewo przechodzimy w prawo
		inorder( PQ, right );					//idziemy a� do samego ko�ca
}