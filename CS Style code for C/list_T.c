#include "list.h"
#include <string.h>


void list_new(List* v, size_t element_size) {
    v->data = NULL;
    v->element_size = element_size;
    v->count = 0;
    v->size = 0;
}

void list_push(List* v, const void* elem) {
    if (v->count == v->size) {
        v->size = v->size ? v->size << 1 : 1;
        v->data = realloc(v->data, v->size * v->v_element_size); 
    }
    
    
    char* target = (char*)v->data + (v->count * v->element_size);
    memcpy(target, elem, v->element_size); 
    v->count++;
}

void list_pop(List* v, void* out_elem) {
    if (v->count == 0) return;
    
    v->count--;
    char* source = (char*)v->data + (v->count * v->element_size);
    
    
    if (out_elem != NULL) {
        memcpy(out_elem, source, v->element_size);
    }
}


void list_free(List* v) {
    free(v->data);
    list_new(v, v->element_size);
}
