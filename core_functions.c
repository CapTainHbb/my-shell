#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "core_functions.h"

char* tokenized_user_input[32];
char* current_dir = "~";

void ls_command() {
    execv("/bin/ls", (char *[]){ "/bin/ls", "-l", NULL });
}

void cd_command(int number_of_tokens) {
    if(number_of_tokens > 2){
        perror("illegal number of arguments!\n");
        return;
    }

    execv("cd", (char *[]){ "cd", tokenized_user_input[1], NULL });
}

void command_handler(char* user_input) {
    
    char* p = strtok(user_input,  " ");
    int i = 0;
    while(p != NULL) {
        tokenized_user_input[i++] = p;
        p = strtok(NULL, " "); //  gets the next token from the string it was previously tokenizing.
    }
    
    if(tokenized_user_input[0] == "ls")
        ls_command();
    else if(tokenized_user_input[0] == "cd")
        cd_command(i);

    return;
    
}



