#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

#include <List.h>

#define ERROR(a, b) {int c = 0; if ((c = a) != b) return c;}

LIST* ListCtor (size_t size, ...)
{
    Elem_t* data_calloc = (Elem_t*) calloc (size, sizeof (Elem_t));
    if (data_calloc == NULL) 
        return NULL;
    
    int* next_calloc = (int*) calloc (size, sizeof (int));
    if (next_calloc == NULL) 
        return NULL;
    
    int* prev_calloc = (int*) calloc (size, sizeof (int));
    if (prev_calloc == NULL) 
        return NULL;
    
    LIST* list_calloc = (LIST*) calloc (1, sizeof (LIST));
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
        list_calloc->prev[i] = -1;
        list_calloc->data[i] = -1;
    }

    list_calloc->next[0]        = 0;
    list_calloc->prev[0]        = 0;
    list_calloc->next[size - 1] = -1;

    LOG_ON (
    list_calloc->dump = CreateFileLog();
    va_list factor;         
    va_start(factor, size);
    list_calloc->line = va_arg(factor, int);
    list_calloc->file = va_arg(factor, const char*);
    va_end(factor);
    char str[] = "Created list\n";
    LogFile (str, list_calloc); )
    
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

    list->dump = NULL;
    list->file = NULL;
    list->free = 0;
    list->line = 0;
    list->size = 0;  

    free (list);
    list = 0;
}

int InsertAfter (Elem_t value, int point, LIST* list)
{
    if (list->free == -1)
        ERROR (MyRealloc (list), OK);

    int next_free = list->next[list->free];

    list->data[list->free] = value;
    list->next[list->free] = list->next[point];
    list->prev[list->free] = point;

    list->prev[list->next[point]] = list->free;
    list->next[point] = list->free;
    list->free = next_free; 

    LOG_ON (
        if (list->line)
        {
            char str[100] = {};
            sprintf (str, "InsertAfter: point #%d, value #%d\n", point, value);
            LogFile (str, list);
        })

    return OK;
}

int InsertBefore (Elem_t value, int point, LIST* list)
{
    if (list->free == -1)
        ERROR (MyRealloc (list), OK);

    int next_free = list->next[list->free];
    
    list->data[list->free] = value;
    list->next[list->free] = point;
    list->prev[list->free] = list->prev[point];

    list->next[list->prev[point]] = list->free;
    list->prev[point] = list->free;
    list->free = next_free;   

    LOG_ON(
        if (list->line)
        {
            char str[100] = {};
            sprintf (str, "InsertBefore: point #%d, value #%d\n", point, value);
            LogFile (str, list);
        })

    return OK;
}

int InsertHead (Elem_t value, LIST* list)
{
    ERROR (InsertAfter (value, 0, list), OK);

    return OK;
}

int InsertTail (Elem_t value, LIST* list)
{
    ERROR (InsertBefore (value, 0, list), OK);

    return OK;
}

//TODO:
// #define VERIFY(stk, ending)
// {
//     log_file    fopen("LOG.txt")
//     int x = 0; 00000000
//     if (stk == NULL)
//     {

//     }
//     StackAssert(stk, x, __FILE__);
//     StackPrint();

// }

void DeletePoint (int point, LIST* list)
{
    //TODO: 
    // VERIFY(list, abort());

    list->data[point] = -1;
    list->prev[list->next[point]] = list->prev[point];
    list->next[list->prev[point]] = list->next[point];
    list->next[point] = list->free;
    list->free = point;
    list->prev[point] = -1;

    LOG_ON (
        if (list->line)
        {
            char str[100] = {};
            sprintf (str, "DeletePoint: point #%d\n", point);
            LogFile (str, list);
        })
}

void DeleteHead  (LIST* list)
{
    DeletePoint (list->next[0], list);
}

void DeleteTail (LIST* list)
{
    DeletePoint (list->prev[0], list);
}


int  FindElement (Elem_t value, LIST* list)
{
    for (int i = 1; i < (int) list->size; i++)
        if (value == list->data[i]) return i;

    return -1;
}

int MyRealloc (LIST* list)
{
    Elem_t* new_data = (Elem_t*) realloc (list->data, (size_t) (list->size) * 2 * sizeof (Elem_t));
    if (new_data == 0) 
        return ERROR_REALLOC;
    list->data = new_data;

    int* new_next = (int*) realloc (list->next, (size_t) (list->size) * 2 * sizeof (int));
    if (new_next == 0) 
        return ERROR_REALLOC;
    list->next = new_next;

    int* new_prev = (int*) realloc (list->prev, (size_t) (list->size) * 2 * sizeof (int));
    if (new_prev == 0) 
        return ERROR_REALLOC;
    list->prev = new_prev;

    list->size *= 2;

    for (int i = (int) list->size / 2; i < (int) list->size; i++) 
    {
        list->next[i] = i + 1;
        list->data[i] = -1;
        list->prev[i] = -1;
    }

    list->next[list->size - 1] = -1;
    list->free = (int) list->size / 2;
    return OK;
}


