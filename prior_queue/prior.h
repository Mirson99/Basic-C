#pragma once
#include "global.h"
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#define MAX 12
typedef struct
{
	QPRIORINFO* pInfo;
	int nPrior;
} PQItem;


typedef struct
{
	PQItem** Queue;		// kolejka realizowana w postaci stogu elementów PQItem
	int PQSize;			// rozmiar kolejki priorytetowej
	int PQCurrSize;		// iloœæ elementów w kolejce
} PQueue;


PQueue* PQInit( int nSize );
int PQisEmpty( PQueue* PQ );

void PQEnqueue( PQueue* PQ, QPRIORINFO* pInfo, int nPrior );			//wstawianie do kolejki
PQItem* PQDequeue( PQueue* PQ );

void PQClearQueue( PQueue* PQ );
void PQRelease( PQueue** PQ );
void PQPrint( PQueue* PQ );												//drukowanie kolejki

void DecreaseKey( PQueue* PQ, int x, int nPrior );
void IncreaseKey( PQueue* PQ, int x, int nPrior );

void inorder( PQueue* PQ, int root );

