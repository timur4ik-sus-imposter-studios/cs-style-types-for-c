#ifndef DICT_H
#define DICT_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DEFINE_DICT(Name, K, V) \
\
typedef struct dict_node_##Name { \
    K key; \
    V value; \
    struct dict_node_##Name* next; \
} dict_node_##Name; \
\
typedef struct { \
    dict_node_##Name** buckets; \
    size_t capacity; \
    size_t count; \
    size_t (*hash_func)(K); \
    bool (*compare_func)(K, K); \
} dict_##Name; \
\
void dict_##Name##_new(dict_##Name* d, size_t capacity, size_t (*hf)(K), bool (*cf)(K, K)); \
void dict_##Name##_set(dict_##Name* d, K key, V value); \
bool dict_##Name##_get(dict_##Name* d, K key, V* out_value); \
void dict_##Name##_free(dict_##Name* d);\
\
void dict_##Name##_new(dict_##Name* d, size_t capacity, size_t (*hf)(K), bool (*cf)(K, K)) { \
    d->capacity = capacity; \
    d->count = 0; \
    d->hash_func = hf; \
    d->compare_func = cf; \
    d->buckets = (dict_node_##Name**)calloc(capacity, sizeof(dict_node_##Name*)); \
} \
\
void dict_##Name##_set(dict_##Name* d, K key, V value) { \
    size_t index = d->hash_func(key) % d->capacity; \
    dict_node_##Name* curr = d->buckets[index]; \
    while (curr != NULL) { \
        if (d->compare_func(curr->key, key)) { \
            curr->value = value; \
            return; \
        } \
        curr = curr->next; \
    } \
    dict_node_##Name* new_node = (dict_node_##Name*)malloc(sizeof(dict_node_##Name)); \
    new_node->key = key; \
    new_node->value = value; \
    new_node->next = d->buckets[index]; \
    d->buckets[index] = new_node; \
    d->count++; \
} \
\
bool dict_##Name##_get(dict_##Name* d, K key, V* out_value) { \
    size_t index = d->hash_func(key) % d->capacity; \
    dict_node_##Name* curr = d->buckets[index]; \
    while (curr != NULL) { \
        if (d->compare_func(curr->key, key)) { \
            if (out_value) *out_value = curr->value; \
            return true; \
        } \
        curr = curr->next; \
    } \
    return false; \
} \
\
void dict_##Name##_free(dict_##Name* d) { \
    for (size_t i = 0; i < d->capacity; i++) { \
        dict_node_##Name* curr = d->buckets[i]; \
        while (curr != NULL) { \
            dict_node_##Name* temp = curr; \
            curr = curr->next; \
            free(temp); \
        } \
    } \
    free(d->buckets); \
    d->buckets = NULL; \
    d->count = d->capacity = 0; \
}

#endif // DICT_H
