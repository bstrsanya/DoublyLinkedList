#ifndef LIST_H
#define LIST_H

#define LOG_LIST 

#ifdef LOG_LIST
#define LOG_ON(...) __VA_ARGS__
#else
#define LOG_ON(...) ;
#endif

#define INSERT_HEAD(value, list) {list->line = __LINE__; list->file = __FILE__; list->dump = file_htm; InsertHead(value,list);} 
#define INSERT_TAIL(value, list) {list->line = __LINE__; list->file = __FILE__; list->dump = file_htm; InsertTail(value,list);}
#define INSERT_AFTER(value, point, list) {list->line = __LINE__; list->file = __FILE__; list->dump = file_htm; InsertAfter(value, point, list);}
#define INSERT_BEFORE(value, point, list) {list->line = __LINE__; list->file = __FILE__; list->dump = file_htm; InsertBefore(value, point, list);}
#define DELETE_TAIL(list) {list->line = __LINE__; list->file = __FILE__; list->dump = file_htm; DeleteTail(list);}
#define DELETE_POINT(point, list) {list->line = __LINE__; list->file = __FILE__; list->dump = file_htm; DeletePoint(point, list);}
#define ERROR(a, b) {int c = 0; if ((c = a) != b) return c;}

typedef int Elem_t;

struct LIST
{
    Elem_t* data;
    int* next;
    int* prev;
    size_t size;
    int free;

    LOG_ON(
    FILE* dump;
    const char* file;
    int line;
    )

};    

const size_t SIZE = 5;

LIST* ListCtor (size_t SIZE);
void ListDtor  (LIST* list);
int MyRealloc (LIST* list);

int InsertHead   (Elem_t value, LIST* list);
int InsertAfter  (Elem_t value, int point, LIST* list);
int InsertTail   (Elem_t value, LIST* list);
int InsertBefore (Elem_t value, int point, LIST* list);

int  FindElement  (Elem_t value, LIST* list);

void DeleteHead  (LIST* list);
void DeleteTail  (LIST* list);
void DeletePoint (int point, LIST* list);

void DumpFile (FILE* file, LIST* list);
void CreateDot (FILE* file, LIST* list);
void CreateHtm (FILE* file, int num, LIST* list);
void LogFile (char* act, LIST* list);
FILE* CreateFileLog ();

enum ERRORS
{
    ERROR_REALLOC = 1,
    OK            = 2
};

#endif