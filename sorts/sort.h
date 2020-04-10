#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <iostream>

int* CreateTab( int );					//kreowanie tablicy parametr rozmiar zwracany wskaznik na tablice alokowana dynamicznie
void RandInit( int* pTab, int nSize );	//uzycie generatora liczb pseudolosowych,  inicjujemy tablice , zrobic jakis modulo rozmioar
void FreeTab( int **pTab );				//zwalnia pamiec po tablicy (free()); //zwalnia pamiec po tablicy (free())
void CopyTab( int* pTabTo, int* pTabFrom, int nSize );
void initTab( int *pTab, int nSize, int nVal );

typedef void( *ToSort )(int*, int);

void SelectionSort( int *t, int nSize );
void InsertionSort( int *t, int nSize );
void BubbleSort( int *t, int nSize );
void MixedBubbleSort( int *tab, int nSize );
void HalfInsertionSort( int *pTab, int nSize );
void QuickSort( int *t, int nSize );
void HeapSort( int *pTab, int nSize );
void MergeSort( int* tab, int* tmp, int left, int right );
void BigMergeSort( int* tab, int left, int right, int nSize );


#endif