#ifndef LIST_H
#define LIST_H

struct LIST
{
    int* data;
    int* next;
    int* prev;
    size_t size;
    int free;
};    

const size_t SIZE = 10;

LIST* ListCtor (size_t SIZE);
void ListDtor  (LIST* list);

void DumpMassive (int* data, int size);

void InsertHead   (int value, LIST* list);
void InsertAfter  (int value, int point, LIST* list);
void InsertTail   (int value, LIST* list);
void InsertBefore (int value, int point, LIST* list);

int  FindElement  (int value, LIST* list);

void DeleteHead  (LIST* list);
void DeleteTail  (LIST* list);
void DeletePoint (int point, LIST* list);

#endif