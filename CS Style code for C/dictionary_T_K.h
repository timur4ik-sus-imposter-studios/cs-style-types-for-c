#ifndef DICT_H
#define DICT_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct dict_node {
    void* key;               
    void* value;             
    struct dict_node* next;  
} dict_node;


typedef struct {
    dict_node** buckets;     
    size_t capacity;         
    size_t count;            
    size_t key_size;         
    size_t value_size;       
    size_t (*hash_func)(const void* key);                  
    bool (*compare_func)(const void* key1, const void* key2); 
} Dict;


void dict_new(Dict* d, size_t capacity, size_t key_size, size_t value_size, 
              size_t (*hf)(const void*), bool (*cf)(const void*, const void*));

void dict_set(Dict* d, const void* key, const void* value);
bool dict_get(Dict* d, const void* key, void* out_value);
void dict_free(Dict* d);

#endif 
