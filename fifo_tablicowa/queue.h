#pragma once
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include "global.h"


/*typedef struct {
	int nKey;			//warto�� 
	//QFIFOItem;
} FQIFOItem;*/


typedef struct {
	FQIFOITEM** pQueue;
	int nHead;			//indeks pierwszej kom�rki
	int nTail;			//indeks pierwszej wolnej kom�rki (nast�pnej po ostatniej)
	int actSize;		//aktualny rozmiar tablicy
	int MaxSize;
}FQueue;

//#define MAX 10

FQueue* QFCreate(int); //NULL fail
void QFEnqueue( FQueue* q, FQIFOITEM* pInfo );
int QFEmpty( FQueue* q );
FQIFOITEM* QFDequeue( FQueue* q );
void QFClear( FQueue* q );			//czysci pamiec	
void QFRemove( FQueue** q );			



