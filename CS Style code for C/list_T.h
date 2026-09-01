#ifndef LIST_H
#define LIST_H
#include <stdlib.h> 
#define DEFINE_LIST(T) \
typedef struct { \
    T* data; \
    size_t count; \
    size_t size; \
} List_##T; \
\
void List_##T##_new(list_##T* v) { \
    v->data = NULL; \
    v->count= v->size = 0; \
} \
\
void Llist_##T##_push(list_##T* v, T elem) { \
    if (v->count == v->size) { \
        v->size = v->size ? v->size << 1 : 1; \
        v->data = (T*)realloc(v->data, v->size * sizeof(T)); \
    } \
    v->data[v->count++] = elem; \
} \
\
T List_##T##_pop(list_##T* v) { \
    return v->data[--v->count]; \
} \
\
void List_##T##_free(list_##T* v) { \
    free(v->data); \
    list_##T##_new(v); \
}

#endif // MY_DLL_H