#include <stdio.h>
#include <stdlib.h>

#include <List.h>

LIST* ListCtor (size_t size)
{
    int* data_calloc = (int*) calloc (size, sizeof (int));
    if (data_calloc == NULL) 
        return NULL;
    
    int* next_calloc = (int*) calloc (size, sizeof (int));
    if (next_calloc == NULL) 
        return NULL;
    
    int* prev_calloc = (int*) calloc (size, sizeof (int));
    if (prev_calloc == NULL) 
        return NULL;
    
    LIST* list_calloc = (LIST*) calloc (size, sizeof (LIST));
    if (list_calloc == NULL) 
        return NULL;

    list_calloc->data = data_calloc;
    list_calloc->next = next_calloc;
    list_calloc->prev = prev_calloc;
    list_calloc->size = size;
    list_calloc->free = 1;

    for (int i = 0; i < (int) size; i++)
    {
        list_calloc->next[i] = i + 1;
        list_calloc->prev[i] = 0;
        list_calloc->data[i] = -1;
    }

    list_calloc->next[0] = 0;
    list_calloc->prev[0] = 0;
    list_calloc->next[size - 1] = 0;
    
    return list_calloc;
}

void ListDtor (LIST* list)
{
    free (list->data);
    list->data = NULL;
    free (list->next);
    list->next = NULL;
    free (list->prev);
    list->prev = NULL;
    list->size = 0;    
    free (list);
}

void DumpMassive (int* data, int size)
{
    for (int i = 0; i < size; i++)
        printf ("%4d", i);

    putchar ('\n');

    for (int j = 0; j < size; j++)
        printf ("%4d", data[j]);

    putchar ('\n');
}

void InsertAfter (int value, int point, LIST* list)
{
    list->data[list->free] = value;
    int a = list->next[point];
    int b = list->next[list->free];
    list->next[point] = list->free;
    list->prev[list->free] = point;
    list->next[list->free] = a;
    list->prev[a] = list->free;
    list->free = b;    
}

void InsertBefore (int value, int point, LIST* list)
{
    list->data[list->free] = value;
    int a = list->prev[point];
    int b = list->next[list->free];
    list->prev[point] = list->free;
    list->next[list->free] = point;
    list->prev[list->free] = a;
    list->next[a] = list->free;
    list->free = b;   
}

void InsertHead (int value, LIST* list)
{
    InsertAfter (value, 0, list);
}

void InsertTail (int value, LIST* list)
{
    InsertBefore (value, 0, list);
}


void DeletePoint (int point, LIST* list)
{
    list->data[point] = -1;
    list->prev[list->next[point]] = list->prev[point];
    list->next[list->prev[point]] = list->next[point];
    list->next[point] = list->free;
    list->free = point;
    list->prev[point] = 0;
}

void DeleteHead  (LIST* list)
{
    DeletePoint (list->next[0], list);
}

void DeleteTail (LIST* list)
{
    DeletePoint (list->prev[0], list);
}


int  FindElement (int value, LIST* list)
{
    for (int i = 1; i < (int) list->size; i++)
        if (value == list->data[i]) return i;

    return -1;
}

// сначала по честному расписал все функции потом понял, что DeleteHead & DeleteTail можно свести к 
// DeletePoint, а также InsertHead & InsertTail можно свести к InsertAfter/Before
