#include <stdio.h>
#include <stdlib.h>

#include <List.h>

void CreateDot (FILE* file, LIST* list)
{
    fprintf (file, "digraph {\n");
    fprintf (file, "splines=\"ortho\";\n");
    fprintf (file, "rankdir=LR;\n");

    fprintf (file, "node%d [shape=Mrecord; style = filled; label = \"{#%d} | {data = %d} | {next = %d} | {prev = %d} \"];\n", 0, 0, list->data[0], list->next[0], list->prev[0]);
    for (int i = 1; i < (int) list->size; i++)
        if (list->prev[i] != -1)
            fprintf (file, "node%d [shape=Mrecord; style = filled; color = pink; label = \"{#%d} | {data = %d} | {next = %d} | {prev = %d} \"];\n", i, i, list->data[i], list->next[i], list->prev[i]);
        else
            fprintf (file, "node%d [shape=Mrecord; style = filled; color = \"#bff096\"; label = \"{#%d} | {data = %d} | {next = %d} | {prev = %d} \"];\n", i, i, list->data[i], list->next[i], list->prev[i]);

    for (int i = 0; i < (int) list->size - 1; i++)
        fprintf (file, "node%d -> node%d [weight = 1000; color = white;];\n", i, i + 1);

    fprintf (file, "nodefree [shape=component; style = filled; color = \"#bff096\"; label = \"free\"];\n");
    if (list->free != -1) fprintf (file, "nodefree -> node%d [color = \"#356d06\", constraint = false, style = dashed, arrowhead = vee];\n", list->free);
    
    for (int i = 0; i < (int) list->size; i++)
    {
        if (i == 0 || list->prev[i] != -1)
           fprintf (file, "node%d -> node%d [color = red, constraint = false, style = bold, arrowhead = vee];\n", i, list->next[i]);
        else
        {
            if (list->next[i] != -1)
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

    Verify (list);
}

void LogFile (char* act, LIST* list)
{
    LOG_ON (
    fprintf (list->dump, "%s:%d\n%s", list->file, list->line, act); 

    char name_file[100] = {}; 
    sprintf (name_file, "./file_dot/file_%d.dot", list->line); 

    FILE* file = fopen (name_file, "w"); 

    CreateDot (file, list); 
    CreateHtm (list->dump, list->line, list); 

    fclose (file); 

    char name_comp[100] = {}; 
    sprintf (name_comp, "dot ./file_dot/file_%d.dot -Tpng -o ./file_dot/file_%d.png", list->line, list->line); 
    
    system (name_comp);

    list->line = 0;
    list->file = NULL;
    )
}

FILE* CreateFileLog ()
{
    FILE* file_htm = fopen("log.htm", "w");
    fprintf (file_htm, "<pre>\n");
    return file_htm;
}

void Verify (LIST* list)
{
    int num_error = 0;
    fprintf (list->dump, "Verify: ");
    for (int i = 0; i < (int) list->size; i++)
    {
        if (list->prev[i] != -1)
        {                                                                       
            if (i != list->prev[list->next[i]] || i != list->next[list->prev[i]])
            {
                num_error += 1;
                fprintf (list->dump, "\nviolation of the connection of elements (%d)", i);
            }
            if ((list->next[i] == list->prev[i]) && (i != 0) && (list->next[i] != 0))
            {
                fprintf (list->dump, "\nthe element (%d) points to itself", i);
                num_error += 1;
            }
        }
        else
        {
            if ((list->next[i] != -1) && (list->prev[list->next[i]] != -1))
            {
                fprintf (list->dump, "\ndisruption of the connection of free cells (%d)", i);
                num_error += 1;
            }
        } 
    }  
    if (num_error) 
        fprintf (list->dump, "Unfortunately, there were %d errors", num_error);
    else 
        fprintf (list->dump, "OK\n");
}
