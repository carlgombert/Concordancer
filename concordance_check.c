#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "concordancer.h"

#define MAX_CMD_LEN 128

// A helper function to run a concordance on a specific file
// 'file_name': Name of the file to spell check
// 'cord': A concordancer containing valid words
int concordance_file(const char *file_name, concordancer_t *cord) {
    void* file = fopen(file_name, "r");
    if(!file){
        printf("Concordance check failed\n");
        return 0;
    }
    char word[MAX_WORD_LEN];
    int i = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF){
        if(ch != ' ' && ch != '\n'){
            word[i] = ch;
            i++;
        }
        else{
            word[i] = '\0';
            i = 0;
            printf("%s", word);
            if(!cord_query(cord, word)){
                printf("[X]");
            }
            printf("%c", ch);
        }
    }
    fclose(file);

    return -1;
}

/*
 * This is in general *very* similar to the list_main file seen in lab
 */
int main(int argc, char **argv) {
    char cmd[MAX_CMD_LEN];
    concordancer_t *cord = NULL;
    
    printf("CSCI 2021 Concordancer System\n");
    printf("Commands:\n");
    printf("  add <word>:              adds a new word to concordancer\n");
    printf("  query <word>:            queries for a word\n");
    printf("  print:                   shows all words currently in the concordancer\n");
    printf("  reset:                   resets all word counts to 0 in the concordancer\n");
    printf("  load <file_name>:        reads in word list from a file\n");
    printf("  save <file_name>:        writes concordancer to a file\n");
    printf("  concordance <file_name>: runs a concordance and spell check on the specified file\n");
    printf("  exit:                    exits the program\n");

    if(argc > 1){
        cord = read_cord_from_text_file(argv[1]);
        if(argc > 2){
            concordance_file(argv[2], cord);
        }
    }
    

    while (1) {
        printf("concordance_check> ");

        if (scanf("%s", cmd) == EOF) {
            printf("\n");
            break;
        }

        else if (strcmp("add", cmd) == 0) {
            scanf("%s", cmd);

            if(NULL == cord){
                cord = create_concordancer();
            }         

            if(!cord_query(cord, cmd)){
                int success = cord_insert(cord, cmd);
                if (!success) {                      
                    printf("add failed\n");
                }
            }
            else{
                printf("'%s' present in concordancer\n", cmd);
            }
        }

        else if (strcmp("query", cmd) == 0) {
            scanf("%s", cmd);

            if(NULL == cord){
                cord = create_concordancer();
            }

            if(cord_query(cord, cmd)){
                printf("'%s' present in concordancer\n", cmd);
            }
            else{
                printf("'%s' not found\n", cmd);
            }
        }

        else if (strcmp("print", cmd) == 0) {
            if(NULL == cord){
                cord = create_concordancer();
            }
            cord_print(cord);
        }

        else if (strcmp("reset", cmd) == 0) {
            if(NULL == cord){
                cord = create_concordancer();
            }
            cord_reset(cord);
        }

        else if (strcmp("load", cmd) == 0) {
            scanf("%s", cmd);

            if(NULL != cord){
                cord_free(cord);
                cord = NULL;
            }
            
            cord = read_cord_from_text_file(cmd);
            if(NULL == cord){
                printf("Failed to read word list from text file\n");
            }
            else{
                printf("Word list successfully read from text file\n");
            }
        }

        else if (strcmp("save", cmd) == 0) {
            scanf("%s", cmd);
            if(NULL == cord){
                cord = create_concordancer();
            }
            
            if(!write_cord_to_text_file(cord, cmd)){
                printf("file does not exist");
            }
        }

        else if (strcmp("concordance", cmd) == 0) {
            scanf("%s", cmd);
            
            if(NULL == cord){
                cord = create_concordancer();
            }

            concordance_file(cmd, cord);
        }

        else if (strcmp("exit", cmd) == 0) {
            cord_free(cord);
            return 0;
        }

         // TODO Add cases for the other commands
        // Read in the command and any additional arguments (where needed)

        else {
            printf("Unknown command %s\n", cmd);
        }
    }

    return 0;
}
