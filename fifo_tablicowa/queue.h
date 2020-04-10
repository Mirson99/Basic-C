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
	int nKey;			//wartoœæ 
	//QFIFOItem;
} FQIFOItem;*/


typedef struct {
	FQIFOITEM** pQueue;
	int nHead;			//indeks pierwszej komórki
	int nTail;			//indeks pierwszej wolnej komórki (nastêpnej po ostatniej)
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



