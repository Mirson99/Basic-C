#pragma once
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#define FQITEM FQItem

typedef struct tagFQItem {
	int nKey;
	tagFQItem *pNext;
} FQItem;


typedef struct {
	FQITEM* pHead;			//first item
	FQITEM* pTail;			//last item
} FQueue;

FQueue* QFCreate(); //NULL fail
int QFEmpty( FQueue* q );
void QFEnqueue( FQueue* q, int x ); //new item at the end
int QFDequeue( FQueue* q ); //bez zwalniania pamiêci
void QFClear( FQueue* q ); //frees memory for queue items
void QFRemove( FQueue** q ); // clears the queue (=QFClear()) and removes
void QFDel( FQueue* q ); //removes only first item
