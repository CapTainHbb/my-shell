#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "core_functions.h"

char* tokenized_user_input[32] = { [0 ... 31] = NULL};
char* current_dir;

void strip_string(char** str) {

    int j = 0;
    while (str[j] != NULL)
    {
        char* data = str[j++];
        unsigned long i = 0; /* Scanning index */
        unsigned long x = 0; /* Write back index */
        char c;

        while ((c = data[i++]) != '\0') 
            if (c != '\n' && c != '\r') 
                data[x++] = c;

        data[x] = '\0';
    }
    
}

void ls_command() {
    execv("/bin/ls", tokenized_user_input);

}

void cd_command(int number_of_tokens) {
    if(number_of_tokens > 2){
        printf("illegal number of arguments!\n");
        return;
    }
    char prev_dir[64];
    strcpy(prev_dir, current_dir);
    strcpy(current_dir, tokenized_user_input[1]);
    if(-1 == execv("/bin/bash", (char *[]){ "cd", tokenized_user_input[1], NULL })) {
        strcpy(current_dir, prev_dir);
    }
}

void command_handler(char* user_input) {
    char* p = strtok(user_input,  " ");
    int i = 0;
    while(p != NULL) {
        tokenized_user_input[i++] = p;
        p = strtok(NULL, " "); //  gets the next token from the string it was previously tokenizing.
    }

    tokenized_user_input[i] = NULL;
    
    strip_string(tokenized_user_input);

    // int u = 0;/////////////////////////////////////
    // while (tokenized_user_input[u] != NULL)//////////////////
    //     printf("tok: %s\t\n", tokenized_user_input[u++]);////////////////
    // return;////////////////////////

    if(!strcmp(tokenized_user_input[0], "ls")) {
        ls_command();
    }
    else if(!strcmp(tokenized_user_input[0] , "cd")) {
        cd_command(i);
    }
    else 
    {
        return;
    }
    
    return;
    
}



