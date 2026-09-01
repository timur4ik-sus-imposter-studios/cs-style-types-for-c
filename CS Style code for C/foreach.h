#ifndef FOREACH_H
#define FOREACH_H

typedef struct Node {
    struct Node* next;
} Node;

typedef void (*foreach_callback)(void* node, void* user_data);

void list_foreach(void* head, foreach_callback callback, void* user_data);

#endif
