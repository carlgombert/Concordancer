#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "concordancer.h"

table_t *create_table() {
    // TODO Not yet implemented
    return NULL;
}

concordancer_t *create_concordancer() {
    // TODO Not yet implemented
    return NULL;
}

int hash_code(const char* word) {
    int sum = 0;
    int i = 0;
    while(word[i] != '\0'){
        sum += word[i] * i;
    }
    return sum;
}

int cord_insert(concordancer_t *cord, const char *word) {
    int length = cord->size;
    int hash = hash_code(word);

    int index = hash%length;

    list_node_t **array = cord->table->array;
    
    if(array[index] == NULL){
        void *ptr = malloc(sizeof(list_node_t));
        struct list_node node;
        node.word = *word;
        ptr = &node;
        array[index] = ptr;
    }
    else{

    }
    return 0;
}

int cord_query(concordancer_t *cord, const char *query) {
    // TODO Not yet implemented
    return 0;
}

void cord_print(const concordancer_t *cord) {
    // TODO Not yet implemented
}

void cord_reset(concordancer_t *cord) {
    // TODO Not yet implemented
}

void cord_free(concordancer_t *cord) {
    // TODO Not yet implemented
}

concordancer_t *read_cord_from_text_file(const char *file_name) {
    // TODO Not yet implemented
    return NULL;
}

int write_cord_to_text_file(const concordancer_t *cord, const char *file_name) {
    // TODO Not yet implemented
    return 0;
}
