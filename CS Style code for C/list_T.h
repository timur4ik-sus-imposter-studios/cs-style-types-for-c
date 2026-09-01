#ifndef LIST_H
#define LIST_H

#include <stdlib.h> 

typedef struct {
    void* data;          
    size_t element_size;
    size_t count;        
    size_t size;      
} List;

void list_new(List* v, size_t element_size);
void list_push(List* v, const void* elem);
void list_pop(List* v, void* out_elem);
void list_free(List* v);

#endif // LIST_H
