#ifndef LIST_H
#define LIST_H

typedef int Elem_t;

struct LIST
{
    int* data;
    int* next;
    int* prev;
    size_t size;
    int free;
};    

const size_t SIZE = 5;

LIST* ListCtor (size_t SIZE);
void ListDtor  (LIST* list);
int MyRealloc (LIST* list);

int InsertHead   (int value, LIST* list);
int InsertAfter  (int value, int point, LIST* list);
int InsertTail   (int value, LIST* list);
int InsertBefore (int value, int point, LIST* list);

int  FindElement  (int value, LIST* list);

void DeleteHead  (LIST* list);
void DeleteTail  (LIST* list);
void DeletePoint (int point, LIST* list);

void DumpFile (FILE* file, LIST* list);
void CreateDot (FILE* file, LIST* list);
void CreateHtm (FILE* file, int num, LIST* list);

enum ERRORS
{
    ERROR_REALLOC = 1,
    OK            = 2
};

#endif