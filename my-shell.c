#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include "core_functions.h"

extern char* tokenized_user_input[32];
extern char* current_dir;


int main() {
    pid_t child;
    int status;
    int error_code;
    size_t buffer_size = 512;
    char* user_input = (char*)malloc(buffer_size * sizeof(char));

    while (1)  // main loop
    {
        printf("please enter a command>(%s) ", current_dir);
        getline(&user_input, &buffer_size,stdin);
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
            error_code = errno;
            switch (error_code)
            {
            case EPERM:         /* Permission denied.  */ 
                perror("permission denied!\n");
                break;
            case EROFS:         /* PATH is on a read-only file system.  */ 
                perror("read only!\n");
                break;
            case ENOENT:        /* PATH does not exists.  */ 
                perror("path does not exists!\n");
                break;
            default:
                break;
            }
            
        }
    }
    
    return 0;
}