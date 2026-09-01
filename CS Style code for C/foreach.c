#include "foreach.h"
#include <stdlib.h>

void list_foreach(void* head, foreach_callback callback, void* user_data) {
    Node* current = (Node*)head;
    
    while (current != NULL) {
        Node* next_node = current->next; 
        callback(current, user_data);
        
        current = next_node;
    }
}
