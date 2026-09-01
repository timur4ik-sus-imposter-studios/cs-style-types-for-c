#include "dict.h"


void dict_new(Dict* d, size_t capacity, size_t key_size, size_t value_size, 
              size_t (*hf)(const void*), bool (*cf)(const void*, const void*)) {
    d->capacity = capacity;
    d->count = 0;
    d->key_size = key_size;
    d->value_size = value_size;
    d->hash_func = hf;
    d->compare_func = cf;
    d->buckets = (dict_node**)calloc(capacity, sizeof(dict_node*));
}


void dict_set(Dict* d, const void* key, const void* value) {
    size_t index = d->hash_func(key) % d->capacity;
    dict_node* curr = d->buckets[index];
    
    
    while (curr != NULL) {
        if (d->compare_func(curr->key, key)) {
            
            memcpy(curr->value, value, d->value_size);
            return;
        }
        curr = curr->next;
    }
    
    
    dict_node* new_node = (dict_node*)malloc(sizeof(dict_node));
    
    
    new_node->key = malloc(d->key_size);
    new_node->value = malloc(d->value_size);
    
    memcpy(new_node->key, key, d->key_size);
    memcpy(new_node->value, value, d->value_size);
    
    
    new_node->next = d->buckets[index];
    d->buckets[index] = new_node;
    d->count++;
}


bool dict_get(Dict* d, const void* key, void* out_value) {
    size_t index = d->hash_func(key) % d->capacity;
    dict_node* curr = d->buckets[index];
    
    while (curr != NULL) {
        if (d->compare_func(curr->key, key)) {
            
            if (out_value != NULL) {
                memcpy(out_value, curr->value, d->value_size);
            }
            return true;
        }
        curr = curr->next;
    }
    return false; 
}


void dict_free(Dict* d) {
    for (size_t i = 0; i < d->capacity; i++) {
        dict_node* curr = d->buckets[i];
        while (curr != NULL) {
            dict_node* temp = curr;
            curr = curr->next;
            
            
            free(temp->key);
            free(temp->value);
            
            free(temp);
        }
    }
    free(d->buckets);
    d->buckets = NULL;
    d->count = d->capacity = 0;
}
