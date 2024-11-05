#include <stdio.h>

#include "List.h"

#define ERROR(a, b) {int c = 0; if ((c = a) != b) return c;}
#define DEBUG(file_htm, act, num) {fprintf (file_htm, act); \
                                    FILE* file = fopen ("./file_dot/file_"#num".dot", "w"); \
                                    CreateDot (file, list); \
                                    CreateHtm (file_htm, num, list); \
                                    fclose (file); }

int main()
{
    LIST* list = ListCtor (SIZE);
    if (list == NULL) 
    {
        printf ("pointer list == null\n");
        return 1;
    }
    
    FILE* file_htm = fopen("log.htm", "w");
    fprintf (file_htm, "<pre>\n");

    DEBUG (file_htm, "ListCtor\n", 0);

    ERROR (InsertHead  (13, list), OK);
    DEBUG (file_htm, "InsertHead #13\n", 1);

    ERROR (InsertHead  (15, list), OK);
    DEBUG (file_htm, "InsertHead #15\n", 2);

    ERROR (InsertHead  (21, list), OK);
    DEBUG (file_htm, "InsertHead #21\n", 3);

    ERROR (InsertTail (5, list), OK);
    DEBUG (file_htm, "InsertTail #5\n", 4);

    ERROR (InsertTail (10, list), OK);
    DEBUG (file_htm, "InsertTail #10\n", 5);

    ERROR (InsertAfter (42, 3, list), OK);
    DEBUG (file_htm, "InsertAfter (3) #42\n", 6);

    ERROR (InsertBefore (37, 3, list), OK);
    DEBUG (file_htm, "InsertBefore (3) #37\n", 7);  

    ERROR (InsertAfter (23, 5, list), OK);
    DEBUG (file_htm, "InsertAfter (5) #23\n", 8);

    DeleteTail (list);
    DEBUG (file_htm, "DeleteTail\n", 9);

    DeletePoint (4, list);
    DEBUG (file_htm, "DeletePoint (4)\n", 10);

    fclose (file_htm);
    ListDtor (list);
}