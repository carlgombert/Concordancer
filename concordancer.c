#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "concordancer.h"



table_t *create_table() {
    // TODO Not yet implemented
    // malloc table size = length*size of listnode
    table_t *table = malloc(sizeof(table_t));
    table->array = malloc(sizeof(list_node_t*)*INITIAL_HASH_TABLE_SIZE);

    for(int i = 0; i < INITIAL_HASH_TABLE_SIZE; i++){
        table->array[i] = NULL;
    }

    table->length = INITIAL_HASH_TABLE_SIZE;
    return table;
}

concordancer_t *create_concordancer() {
    concordancer_t *cord = malloc(sizeof(concordancer_t));
    cord->table = create_table();
    cord->size = 0;
    return cord;
}

int hash_code(const char* word) {
    int sum = 0;
    int i = 0;
    while(word[i] != '\0'){
        sum += word[i] * i;
        i++;
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
        node->next = NULL;
        node->count = 0;
        free(array[index]);
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
        free(curr->next);
        curr->next = node;
        node->count = 0;
        node->next = NULL;
        cord->size += 1;
    }
    return -1;
}

int cord_query(concordancer_t *cord, const char *query) {
    int hash = hash_code(query);
    int index = hash%cord->table->length;

    list_node_t **array = cord->table->array;
    if(NULL == array[index]){
      return 0;
    }
    else {
      	list_node_t *curr = array[index];
      	while(NULL != curr){
          	if(strcmp(query, curr->word) == 0){
                  curr->count += 1;
                  return -1;
          	}
            curr = curr->next;
        }
        return 0;
    }
    return 0;
}

void cord_print(const concordancer_t *cord) {
    list_node_t *nodes[cord->size];
    int count = 0;

    for(int i = 0; i < cord->table->length; i++){
      list_node_t *curr = cord->table->array[i];
      while(NULL != curr){
        nodes[count] = curr;
        curr = curr->next;
        count++;
      }
    }

    //insertion sort of list nodes
    for(int i = 0; i < count; i++){
    	list_node_t *curr = nodes[i];
    	int j = i-1;

    	while(j>=0 && nodes[j]->count < curr->count){
    		nodes[j+1] = nodes[j];
    		j = j-1;
    	}
    	nodes[j+1] = curr;
    }

    for(int i = 0; i < count; i++){
    	printf("%s %d\n", nodes[i]->word, nodes[i]->count);
    }
}

void cord_reset(concordancer_t *cord) {

    for(int i = 0; i < cord->table->length; i++){

      list_node_t *curr = cord->table->array[i];

      while(NULL != curr){
        curr->count = 0;
        curr = curr->next;
      }
    }

}

void cord_free(concordancer_t *cord) {
    if(NULL != cord){
        for(int i = 0; i < cord->table->length; i++){

        list_node_t *curr = cord->table->array[i];

        while(NULL != curr){
            void* temp = curr;
            curr = curr->next;
            free(temp);
        }
        }
        free(cord->table->array);
        free(cord->table);
        free(cord);
    }
}

concordancer_t *read_cord_from_text_file(const char *file_name) {
    void* file = fopen(file_name, "r");
    if(!file){
        return NULL;
    }

    concordancer_t *cord = create_concordancer();

    char word[MAX_WORD_LEN];
    while (fscanf(file, "%s", word) == 1){
        if(!cord_query(cord, word)){
            cord_insert(cord, word);
        }
    }
    fclose(file);
    return cord;
}

int write_cord_to_text_file(const concordancer_t *cord, const char *file_name) {

    list_node_t *nodes[cord->size];
    int count = 0;
    
    for(int i = 0; i < cord->table->length; i++){
      list_node_t *curr = cord->table->array[i];
      while(NULL != curr){
        nodes[count] = curr;
        curr = curr->next;
        count++;
      }
    }

    //insertion sort of list nodes
    for(int i = 0; i < count; i++){
    	list_node_t *curr = nodes[i];
    	int j = i-1;

    	while(j>=0 && nodes[j]->count < curr->count){
    		nodes[j+1] = nodes[j];
    		j = j-1;
    	}
    	nodes[j+1] = curr;
    }

    void* file = fopen(file_name, "w");
    if(!file){
        return 0;
    }

    for(int i = 0; i < count; i++){
    	fprintf(file, "%s %d\n", nodes[i]->word, nodes[i]->count);
    }

    fclose(file);
    return -1;
}
