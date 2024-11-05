#include <stdio.h>
#include <stdlib.h>

#include <List.h>

#define ERROR(a, b) {int c = 0; if ((c = a) != b) return c;}

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

    list_calloc->next[0]        = 0;
    list_calloc->prev[0]        = 0;
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
    list = 0;
}

int InsertAfter (int value, int point, LIST* list)
{
    if (list->free == 0)
        ERROR (MyRealloc (list), OK);

    int next_free = list->next[list->free];

    list->data[list->free] = value;
    list->next[list->free] = list->next[point];
    list->prev[list->free] = point;

    list->prev[list->next[point]] = list->free;
    list->next[point] = list->free;
    list->free = next_free;  
    
    return OK;
}

int InsertBefore (int value, int point, LIST* list)
{
    if (list->free == 0)
        ERROR (MyRealloc (list), OK);

    int next_free = list->next[list->free];
    
    list->data[list->free] = value;
    list->next[list->free] = point;
    list->prev[list->free] = list->prev[point];

    list->next[list->prev[point]] = list->free;
    list->prev[point] = list->free;
    list->free = next_free;   

    return OK;
}

int InsertHead (int value, LIST* list)
{
    ERROR (InsertAfter (value, 0, list), OK);

    return OK;
}

int InsertTail (int value, LIST* list)
{
    ERROR (InsertBefore (value, 0, list), OK);

    return OK;
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

int MyRealloc (LIST* list)
{
    int* new_data = (int*) realloc (list->data, (size_t) (list->size) * 2 * sizeof (int));
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
        list->prev[i] = 0;
    }

    list->next[list->size - 1] = 0;
    list->free = (int) list->size / 2;
    return OK;
}

// ----------------------------------------FOR DEBAG----------------------------------------

void CreateDot (FILE* file, LIST* list)
{
    fprintf (file, "digraph {\n");
    fprintf (file, "splines=\"ortho\";\n");
    fprintf (file, "rankdir=LR;\n");

    fprintf (file, "node%d [shape=Mrecord; style = filled; label = \"{#%d} | {data = %d} | {next = %d} | {prev = %d} \"];\n", 0, 0, list->data[0], list->next[0], list->prev[0]);
    for (int i = 1; i < (int) list->size; i++)
        if (list->data[i] != -1)
            fprintf (file, "node%d [shape=Mrecord; style = filled; color = pink; label = \"{#%d} | {data = %d} | {next = %d} | {prev = %d} \"];\n", i, i, list->data[i], list->next[i], list->prev[i]);
        else
            fprintf (file, "node%d [shape=Mrecord; style = filled; color = \"#bff096\"; label = \"{#%d} | {data = %d} | {next = %d} | {prev = %d} \"];\n", i, i, list->data[i], list->next[i], list->prev[i]);

    for (int i = 0; i < (int) list->size - 1; i++)
        fprintf (file, "node%d -> node%d [weight = 1000; color = white;];\n", i, i + 1);

    fprintf (file, "nodefree [shape=component; style = filled; color = \"#bff096\"; label = \"free\"];\n");
    fprintf (file, "nodefree -> node%d [color = \"#356d06\", constraint = false, style = dashed, arrowhead = vee];\n", list->free);
    
    for (int i = 0; i < (int) list->size; i++)
    {
        if (i == 0 || list->data[i] != -1)
           fprintf (file, "node%d -> node%d [color = red, constraint = false, style = bold, arrowhead = vee];\n", i, list->next[i]);
        else
        {
            if (list->next[i] != 0)
                fprintf (file, "node%d -> node%d [color = \"#356d06\"; constraint = false; style = dashed, arrowhead = vee];\n", i, list->next[i]);
        }
    }
    fprintf (file, "}\n");
}

void CreateHtm (FILE* file, int num, LIST* list)
{
    DumpFile (file, list);
    fputc ('\n', file);
    fprintf (file, "<img src=\"./file_dot/file_%d.png\" width = 700 >\n", num);
    fputc ('\n', file);
}

void DumpFile (FILE* file, LIST* list)
{
    fprintf (file, "data [%p]:", &list->data);
    for (int i = 0; i < (int) list->size; i++)
        fprintf (file, "%5d", list->data[i]);
    fprintf (file, "\n");

    fprintf (file, "next [%p]:", &list->next);
    for (int i = 0; i < (int) list->size; i++)
        fprintf (file, "%5d", list->next[i]);
    fprintf (file, "\n");

    fprintf (file, "prev [%p]:", &list->prev);
    for (int i = 0; i < (int) list->size; i++)
        fprintf (file, "%5d", list->prev[i]);
    fprintf (file, "\n");
}

