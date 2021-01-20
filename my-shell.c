#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "core_functions.h"

char* tokenized_user_input[32] = { [0 ... 31] = NULL};

int main() {
    pid_t child;
    int pipe_fds[2], status, error_code;
    size_t buffer_size = 512, user_input_size;
    char* user_input = (char*)malloc(buffer_size * sizeof(char));
    char* current_dir= (char*)malloc(buffer_size * sizeof(char));
    
    while (1)  // main loop
    {   
        getcwd(current_dir, buffer_size); // update current working directory
        printf("please enter a command>(%s) ", current_dir);
        getline(&user_input, &buffer_size, stdin);
        user_input_size = tokenize_user_input(user_input);
        
        if (!strcmp(tokenized_user_input[0], "cd")) // cd command
        {
            if (user_input_size != 2)
                printf("illegal number of argument!\n");
            else
            {
                if (-1 == chdir(tokenized_user_input[1]))
                {
                    printf("can't open directory %s!\n", tokenized_user_input[1]);
                }      
            }  
        }
        else 
        {
                child = fork();
                if (-1 == child) {
                    perror("can't create child!\n");
                }
                else if(0 == child) {  // child process
                    command_handler();
                    return 0;
                }
                else {  // parent process
                    wait(&status);
                }
        }
    }
    
    return 0;
}