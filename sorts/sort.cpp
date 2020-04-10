#include "sort.h"

void RecuSort( int l, int p, int*t );
void Update( int* pTab, int l, int p ); //potrzebne do kopcowania
void Merge( int* tab, int* pom, int left, int middle, int right );
void BigMerge( int* tab, int left, int middle, int right, int nSize );


void CopyTab( int* pTabTo, int* pTabFrom, int nSize )
{
	memcpy( pTabTo, pTabFrom, nSize * sizeof( int ) );
}

void RandInit( int* pTab, int nSize )
{
	srand( ( unsigned int )time( NULL ) );
	                   //wskaŸnik do przechodzenia po komórkach tablicy
	for( int i = 0; i < nSize; i++ )
	{
		*pTab++ = rand() % nSize;			//losujemy liczby z przedzia³u od 0 do 100 i wpisujemy do komórki
								//przechodzimy do nastêpnej komórki tablicy
	}
}

void initTab( int *pTab, int nSize, int nVal )
{
	for( int i = 0; i < nSize; i++ )
	{
		*pTab++ = nVal;
	}
}
int* CreateTab( int nSize )
{
	int *pTab = ( int* )malloc( nSize * sizeof( int ) );				//rezerwuje miejsce dla tablicy
	if( !pTab ) return NULL;										// sprawdzam czy alokacja sie powiodla
	memset( pTab, 0, sizeof( int ) * nSize );						//wype³niam bity zerami
	return pTab;												//zwracam wskaŸnik do utworzonej tablicy
}

void FreeTab( int **pTab )
{
	free( *pTab );
	*pTab = NULL;
}

void SelectionSort( int* t, int nSize )     //sortowanie przez wybieranie
{
	for (int i = 0; i < nSize - 1; i++)
	{
		int k = i;
		int x = t[i];
		for (int j = i + 1; j < nSize; j++)
		{
			if (t[j] < x)
			{
				k = j;
				x = t[j];
			}
		}
		t[k] = t[i];
		t[i] = x;
	}

}

void InsertionSort( int *t, int nSize )  //sortowanie przez wstawianie
{
	for( int i = 1; i < nSize; i++ )
	{
		int x = t[i];				//ten element bêdzie wstawiony w odpowiednie miejsce
		int j = i - 1;
		//t[0] = x;
		while( (j>=0) && (x < t[j]) )
		{
			t[j + 1] = t[j--];
		}
		t[j + 1] = x;
	}
}

void BubbleSort( int *t, int nSize )
{
	for (int i = 0; i < nSize; i++)
		for (int j = 1; j < nSize - i; j++) //pêtla wewnêtrzna
			if (t[j - 1] > t[j])
			{
				int temp = t[j - 1];
				t[j - 1] = t[j];
				t[j] = temp;
			}								//zamiana miejscami

}


void MixedBubbleSort( int *tab, int nSize )
{
	int l = 1;
	int p = nSize - 1;
	int k = nSize;
	int x = 0;
	while (l <= p)
	{
		for (int j = p; j >= l; j--)
		{
			if (tab[j - 1] > tab[j])
			{
				x = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = x;
				k = j;
			}
		}
		l = k + 1;
		for (int j = l; j <= p; j++)
		{
			if (tab[j - 1] > tab[j])
			{
				x = tab[j - 1]; //----------------
				tab[j - 1] = tab[j];
				tab[j] = x;
				k = j;
			}
		}
		p = k - 1;
	}
}

void HalfInsertionSort( int* pTab, int nSize ) // nie dziala
{
	int l, p, m, x;
	for (int i = 0; i < nSize; i++)
	{
		l = 0;
		p = i - 1;
		x = pTab[i];
		while (l <= p)
		{
			m = l + (p - l) / 2;
			if (x < pTab[m]) p = m - 1;
			else l = m + 1;
		}
		for (int j = i - 1; j >= l; j--) pTab[j + 1] = pTab[j];
		pTab[l] = x;
	}
}

void RecuSort( int left, int right, int*t )        //quicksort
{
	if( left >= right ) return;

	int i = left;
	int j = right;
	int pivot = t[left + (right - left) / 2];  //jako pivot wybieram œrodkowy element
	while (i <= j)
	{
		while( t[i] < pivot ) i = i + 1;
		while( t[j] > pivot ) j = j - 1;
		if( i <= j )
		{
			int temp = t[i];
			t[i] = t[j];
			t[j] = temp;
			i = i + 1;
			j = j - 1;
		}
	}
	if( left < j ) RecuSort( left, j, t );
	if( i < right ) RecuSort( i, right, t );
}

void QuickSort( int *t, int nSize )
{
	RecuSort( 0, nSize - 1, t );
}




void Merge( int* tab, int* pom, int left, int middle, int right )
{
	//for( int i = left; i <= right; i++ )   //kopiujemy elementy z lewej i prawej czesci do tablicy pomocniczej
		//pom[i] = tab[i];

	memcpy( pom + left, tab + left, sizeof( int ) * (right - left + 1) );

	int i = left;                 //pierwszy element lewej podtablicy
	int j = middle + 1;			//pierwszy element prawej podtablicy
	int k = left;				//indeks wed³ug którego bêdziemy uk³adaæ uporz¹dkowane elementy w tablicy 

	while( i <= middle && j <= right ) //porownywanie elementow i ³¹czenie podtablic
	{
		if( pom[i] <= pom[j] )
		{
			tab[k++] = pom[i++];
			//i++;
		}
		else
		{
			tab[k++] = pom[j++];
			//j++;
		}
		//k++;
	}
	memcpy( tab + k, pom + i, (middle - i + 1) * sizeof( int ) );

}

void MergeSort( int* tab, int* tmp, int left, int right )
{
	if( left < right )  //jeœli mamy wiêcej ni¿ jeden element, jeœli mamy jeden to nie trzeba sortowaæ
	{
		//m = srodek miedzy l i p
		int middle = left + ( right - left ) / 2;
		MergeSort( tab, tmp, left, middle );       //sortujemy lew¹ czêœæ tablicy
		MergeSort( tab, tmp, middle + 1, right );	 //sortujemy praw¹ czêœæ tablicy
		Merge( tab, tmp, left, middle, right );		 //³¹czymy dwie posortowane ju¿ czêœci
	}
}



/*************************************************************/
//BigMergeSort
void BigMergeSort( int* tab, int left, int right, int nSize )
{
	if( left < right )  //jeœli mamy wiêcej ni¿ jeden element, jeœli mamy jeden to nie trzeba sortowaæ
	{
		//m = srodek miedzy l i p
		int middle = left + ( right - left ) / 2;
		BigMergeSort( tab, left, middle, nSize );       //sortujemy lew¹ czêœæ tablicy
		BigMergeSort( tab, middle + 1, right, nSize );	 //sortujemy praw¹ czêœæ tablicy
		BigMerge( tab, left, middle, right, nSize );		 //³¹czymy dwie posortowane ju¿ czêœci 
	}
}

void BigMerge( int* tab, int left, int middle, int right, int nSize )
{
	memcpy( tab + nSize + left, tab + left, sizeof( int ) * (right - left + 1) );//kopiujemy wartoœci z pierwszej po³owy tablicy do drugiej


	int i = left;										//indeks pocz¹tkowy
	int j = middle + 1;									//indeks pocz¹tkowy w drugiej czêœci pierwszej po³owy tablicy
	int k = left;										//indeks do uk³adania posortowanych wartoœci w tablicy
	//int mr = middle + nSize + 1;
	//middle += nSize;								//indeks œrodkowy te¿ musimy przesun¹æ

	//porównujemy wartoœci i uk³adamy je po kolei w pierwszej po³owie tablicy	
	while( i <= middle && j <= right )
	{
		if( tab[i + nSize] <= tab[j + nSize] )
		{
			tab[k++] = tab[i++ + nSize];
			//i++;
		}
		else
		{
			tab[k++] = tab[j++ + nSize];
			//j++;
		}
		//k++;
	}
	memcpy( tab + k, tab + nSize + i, (middle - i + 1) * sizeof( int ) ); //kopiujemy pozosta³e elementy

}



/*********************************************************************/
//Heap Sort
void Update( int* pTab, int l, int p )
{
	if (l == p) return;
	int i = l;
	int j = 2 * i+1;
	int x = pTab[i];
	while (j <= p)
	{
		if( (j < p) && (pTab[j] < pTab[j + 1])) j++;//jeœli istnieje prawy potomek
							//jeœli wiêksze to zamieniamy
		if (x >= pTab[j]) break;							//rodzic wiekszy niz potomek, przerywamy
		pTab[i] = pTab[j];									//wpisujemy potomek w miejsce rodzica
		i = j;												//
		j = 2 * i + 1;										//zamieniamy indeksy dzieci i rodziców
	}
	pTab[i] = x;											//przypisujemy wartoœæ do rodzica
}

void HeapSort( int* pTab, int nSize )
{
	int l = (nSize / 2);
	int p = nSize -1;

	for (; l > 0; l--)
		Update( pTab, l-1, p );

	for (; p > 0; p--)
	{
		int x = pTab[0]; //---------------------
		pTab[0] = pTab[p];
		pTab[p] = x;
		Update( pTab, l, p - 1 );
	}
}
/*void Update( int* pTab, int l, int p )
{
	int i = l;
	int j = 2 * i;
	int x = pTab[i];

	while( j <= p )
	{
		if( j < p )							//jeœli istnieje prawy potomek
			if( pTab[j] < pTab[j + 1] ) j++;  //jeœli wiêksze to zamieniamy
		if( x >= pTab[j] ) break;			//rodzic wiekszy niz potomek, przerywamy
		pTab[i] = pTab[j];					//wpisujemy potomek w miejsce rodzica
		i = j;								//
		j = 2 * i;							//zamieniamy indeksy dzieci i rodziców
	}
	pTab[i] = x;							//przypisujemy wartoœæ do rodzica
}*/


/*void HeapSort( int *pTab, int nSize )
{
	//MakeHeap( pTab, nSize );

	int l = ( nSize / 2 ) + 1;
	int p = nSize;
	while( l > 0 )
	{
		l--;
		Update( pTab, l, p );
	}

	while( p > 0 )
	{
		int x = pTab[0];		//zamieniamy pierwszy element z ostatnim
		pTab[0] = pTab[p];
		pTab[p] = x;
		p--;					//ucinamy ostatni element
		Update( pTab, l, p );	//budujemy kopiec maksymalny
	}
}*/


