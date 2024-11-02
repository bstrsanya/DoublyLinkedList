#include <stdio.h>

#include "List.h"

int main()
{
    LIST* list = ListCtor (SIZE);
    if (list == NULL) 
    {
        printf ("pointer list == null\n");
        return 1;
    }

    InsertHead  (13, list);
    InsertHead  (15, list);
    InsertHead  (21, list);
//37 21 42 15 13 5 10 23
    InsertTail (5, list);
    InsertTail (10, list);

    InsertAfter (42, 3, list);
    InsertBefore (37, 3, list);
    InsertAfter (23, 5, list);

    DeleteTail (list);

    printf ("DATA\n");
    DumpMassive (list->data, SIZE);
    printf ("NEXT\n");
    DumpMassive (list->next, SIZE);
    printf ("PREV\n");
    DumpMassive (list->prev, SIZE);
    printf ("free: %d\n", list->free);

    ListDtor (list);
}