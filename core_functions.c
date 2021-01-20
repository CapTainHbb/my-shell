#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "core_functions.h"

extern char* tokenized_user_input[32];

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

int tokenize_user_input(char* user_input) {
    char* p = strtok(user_input,  " ");
    int i = 0;
    while(p != NULL) {
        tokenized_user_input[i++] = p;
        p = strtok(NULL, " "); //  gets the next token from the string it was previously tokenizing.
    }
    
    tokenized_user_input[i] = NULL;
    
    strip_string(tokenized_user_input);
    
    return i;
}

void ls_command() {
    execv("/bin/ls", tokenized_user_input);
}

void cd_command(int number_of_tokens) {
    if(number_of_tokens != 2){
        perror("illegal number of arguments!\n");
        return;
    }
    if(chdir(tokenized_user_input[1]) != -1) {

    }  
}

void clear_screen() {
    execv("/bin/clear", (char*[]){"clear", NULL});
}

void command_handler() {
    
    if(!strcmp(tokenized_user_input[0], "ls")) {
        ls_command();
    }
    else if(!strcmp(tokenized_user_input[0], "clear")) {
        clear_screen();
    }
    return;
    
}



