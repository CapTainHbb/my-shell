#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include "core_functions.h"

int main() {
    pid_t child;
    int status;
    char* user_input = (char*)malloc(1024 * sizeof(char));
    while (1)  // main loop
    {
        printf("please enter a command> ");
        scanf("%[^\n]",user_input);
        child = fork();
        if (-1 == child)
        {
            perror("can't create child!\n");
        }
        else if(0 == child) {  // child process
            command_handler(user_input);
            return 0;
        }
        else  // parent process
        {
            wait(&status);
            
        }
    }
    
    return 0;
}