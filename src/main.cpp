#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "List.h"

int main()
{
    LIST* list = ListCtor (SIZE);
    if (list == NULL) 
    {
        printf ("pointer list == null\n");
        return 1;
    }

    FILE* file_htm = CreateFileLog();

    INSERT_HEAD  (13, list);

    INSERT_HEAD  (15, list);

    INSERT_HEAD  (21, list);

    INSERT_TAIL (5, list);

    INSERT_TAIL (10, list);

    INSERT_AFTER (42, 3, list);

    INSERT_BEFORE (37, 3, list);

    INSERT_AFTER (23, 5, list);

    DELETE_TAIL (list);

    DELETE_POINT (4, list);

    ListDtor (list);

    fclose (file_htm);
}