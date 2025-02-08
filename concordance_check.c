#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "concordancer.h"

#define MAX_CMD_LEN 128

// A helper function to run a concordance on a specific file
// 'file_name': Name of the file to spell check
// 'cord': A concordancer containing valid words
int concordance_file(const char *file_name, concordancer_t *cord) {
    // TODO Not yet implemented
    return 0;
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

    while (1) {
        printf("concordance_check> ");

        if (scanf("%s", cmd) == EOF) {
            printf("\n");
            break;
        }

        if (strcmp("add", cmd) == 0) {
            scanf("%s", cmd);

            if(NULL == cord){
                cord = create_concordancer();
            }         

            if(!cord_query(cord, cmd)){
                int success = cord_insert(cord, cmd);
                if (!success) {                      
                    printf("add failed\n");
                }
                else{
                    printf("added\n");
                }
            }
            else{
                printf("added\n");
            }
        }

        if (strcmp("query", cmd) == 0) {
            scanf("%s", cmd);

            if(NULL == cord){
                cord = create_concordancer();
            }

            if(cord_query(cord, cmd)){
                printf("element exists\n");
            }
            printf("element does not exist\n");
        }

        if (strcmp("print", cmd) == 0) {
            if(NULL == cord){
                cord = create_concordancer();
            }
            cord_print(cord);
        }

        if (strcmp("reset", cmd) == 0) {
            if(NULL == cord){
                cord = create_concordancer();
            }
            cord_reset(cord);
        }

        if (strcmp("load", cmd) == 0) {
            if(NULL != cord){
                cord_free(cord);
            }
        }

        if (strcmp("save", cmd) == 0) {
            
        }

        if (strcmp("concordance", cmd) == 0) {

        }

        if (strcmp("exit", cmd) == 0) {
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
