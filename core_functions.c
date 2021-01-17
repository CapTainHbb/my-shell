#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "core_functions.h"

void ls_command() {
    execv("/bin/ls", (char *[]){ "/bin/ls", "-l", NULL });
}

void command_handler(char* user_input) {
    
    char* p = strtok(user_input,  " ");
    while(p != NULL) {
        printf("%s\n", p);
        p = strtok(NULL, " "); //  gets the next token from the string it was previously tokenizing.
    }
    
    ls_command();
}



