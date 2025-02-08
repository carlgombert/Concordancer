#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "concordancer.h"



table_t *create_table() {
    // TODO Not yet implemented
    // malloc table size = length*size of listnode
    table_t *table = malloc(sizeof(table_t));
    table->array = malloc(sizeof(list_node_t)*INITIAL_HASH_TABLE_SIZE);
    table->length = INITIAL_HASH_TABLE_SIZE;
    return table;
}

concordancer_t *create_concordancer() {
    concordancer_t *cord = malloc(sizeof(concordancer_t));
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
    int length = cord->table->length;
    int hash = hash_code(word);

    int index = hash%length;

    list_node_t **array = cord->table->array;
    
    if(NULL == array[index]){
        list_node_t *node = malloc(sizeof(list_node_t));
        strcpy((node->word), word);
        array[index] = node;
        cord->size += 1;
    }
    else{
        list_node_t *curr = array[index];
        while(NULL != curr->next){
            curr = curr->next;
        }
        list_node_t *node = malloc(sizeof(list_node_t));
        strcpy((node->word), word);
        curr->next = node;
        cord->size += 1;
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
