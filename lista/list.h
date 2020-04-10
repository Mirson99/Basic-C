#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "global.h"



typedef int( *pointer_to_compare )( const void *, const void * );
typedef struct tagListItem
{
	LISTINFO* m_pInfo;									//wskazuje na wartoœæ wêz³a    	
	tagListItem* m_pNext;								//zawiera adres nastêpnego wêz³a
} ListItem;



ListItem* CreateList();									//tworzy liste
void PrintList( ListItem* pHead );
void InsertFront( ListItem* p, LISTINFO* pInfo );		//wk³ada element na pierwsze miejsce na liscie
void RemoveFront( ListItem* pHead );					// usuwanie pierwszego elementu
void Insert( ListItem* pAfter, LISTINFO* pInfo );		// wstawianie elementu w wybrane miejsce(przekazujemy wskaznik elementu po ktorym chcemy wstawic)
void Remove( ListItem* pAfter );						// funkcja usuwa element po wybranym
void DelElements( ListItem* pHead );					// usuwanie elementów z listy oprócz pHead
int isEmpty( ListItem* p );								//sprawdzenie czy lista zawiera elementy
void DelList( ListItem** p );							//usuwanie wszystkich elementow wraz z glowa
ListItem* Front( ListItem* p );							//zwraca pierwszy element
ListItem* Find( ListItem *pHead, const void* value, ListItem** previous, pointer_to_compare compare ); 
void SortList( ListItem* pHead, pointer_to_compare compare ); 
#endif