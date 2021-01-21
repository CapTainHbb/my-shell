#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include "core_functions.h"

extern char* tokenized_user_input[32];
extern size_t user_input_size;
extern pid_t child;
extern int signal_occured;

int get_pipeline_index() {
    int i = 0;
    while (tokenized_user_input[i] != NULL){
        if(!strcmp(tokenized_user_input[i], ">")) 
            return i;
        i++;
    }
        
    return -1;
}

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

void pipe_line_command(int pipe_line_index) {
    pid_t ch;
            int fds[2];
            pipe(fds);
            ch = fork();
            if (-1 == ch)
            {
                printf("can't create child process!\n");
            }
            else if (0 == ch) // in child
            {
                close(fds[0]);
                dup2(fds[1], STDOUT_FILENO);

                char* args[32] = { [0 ... 31] = NULL };
                for (int i = 0; i < pipe_line_index; i++)
                    args[i] = tokenized_user_input[i];
                
                if(!strcmp(tokenized_user_input[0], "ls")) {
                    execv("/bin/ls", args);       
                }
                else if(!strcmp(tokenized_user_input[0], "lsdir")) {
                    if (user_input_size == 3)
                        execl("/bin/find", "find", ".", "-maxdepth",  "1", "-type", "d", "-name", tokenized_user_input[0], NULL);
                    else if(user_input_size == 4)
                        execl("/bin/find", "find", ".", "-maxdepth",  "1", "-type", "d", NULL);
                }
                else if(!strcmp(tokenized_user_input[0], "cat")) {
                    execv("/bin/cat", args);
                }
                else if(!strcmp(tokenized_user_input[0], "head")) {
                   execv("/bin/head", args);
                }
                else if(!strcmp(tokenized_user_input[0], "tail")) {
                    execv("/bin/tail", args);
                }                
            }
            else // in parent
            {
                wait(NULL);
                char* buf = (char*)malloc(4096 * sizeof(char));
                memset(buf, '\0', 4096);
                close(fds[1]);
                dup2(fds[0], STDIN_FILENO);

                FILE* file = fopen(tokenized_user_input[user_input_size - 1], "w");
                while (NULL != fgets(buf, sizeof(buf), stdin))
                {
                    fprintf(file, buf);
                }
                fclose(file);
            }
}

void ls_command() {
    int index = get_pipeline_index();
    if (-1 == index)
    {
        execv("/bin/ls", tokenized_user_input);
    }
    else
    {
        if (index != (user_input_size - 2))
            printf("'>' posistion is wrong!\n");
        else
            pipe_line_command(index);
    }
}

void cd_command() {
    if(user_input_size != 2) {
        printf("illegal number of arguments!\n");
        return;
    }
    chdir(tokenized_user_input[1]);  
}

void clear_screen() {
    if (1 != user_input_size)
    {
        printf("illegal number of arguments!\n");
        return;
    }
    execv("/bin/clear", (char*[]){"clear", NULL});
}

void lsdir_command() {

    int index = get_pipeline_index();
    if (-1 == index)
    {
        if (user_input_size == 2)
            execl("/bin/find", "find", ".", "-maxdepth",  "1", "-type", "d", "-name", tokenized_user_input[1], NULL);
        else if(user_input_size == 1)
            execl("/bin/find", "find", ".", "-maxdepth",  "1", "-type", "d", NULL);
    }
    else
    {
        if (index != (user_input_size - 2))
            printf("'>' posistion is wrong!\n");
        else
            pipe_line_command(index);
    }
    
        
}

void rename_command() {
    if (user_input_size != 3)
    {
        printf("illegal number of arguments!\n");
        return;
    }
    rename(tokenized_user_input[1], tokenized_user_input[2]);    
}

void remove_command() {
    execv("/bin/rm", tokenized_user_input);     
}

void move_command() {
    execv("/bin/mv", tokenized_user_input); 
}

void copy_command() {
    if (user_input_size != 3)
    {
        printf("illegal number of arguments!\n");
        return;
    }
    execl("/bin/cp", "cp", tokenized_user_input[1], tokenized_user_input[2], NULL);
}

void cat_command() {
    int index = get_pipeline_index();
    if (-1 == index)
    {
        execv("/bin/cat", tokenized_user_input);
    }
    else
    {
        if (index != (user_input_size - 2))
            printf("'>' posistion is wrong!\n");
        else
            pipe_line_command(index);
    }
}
        
void head_command(){
    int index = get_pipeline_index();
    if (-1 == index)
    {
        execv("/bin/head", tokenized_user_input);
    }
    else
    {
        if (index != (user_input_size - 2))
            printf("'>' posistion is wrong!\n");
        else
            pipe_line_command(index);
    }
    
}

void tail_command(){
    int index = get_pipeline_index();
    if (-1 == index)
    {
        execv("/bin/tail", tokenized_user_input);
     }
    else
    {
         if (index != (user_input_size - 2))
             printf("'>' posistion is wrong!\n");
         else
             pipe_line_command(index);
    }
}

void command_handler() {
    
    if(!strcmp(tokenized_user_input[0], "ls")) {
        ls_command();        
    }
    else if(!strcmp(tokenized_user_input[0], "clear")) {
        clear_screen();
    }
    else if(!strcmp(tokenized_user_input[0], "lsdir")) {
        lsdir_command();
    }
    else if(!strcmp(tokenized_user_input[0], "rename")) {
        rename_command();
    }
    else if(!strcmp(tokenized_user_input[0], "rm")) {
        remove_command();
    }
    else if(!strcmp(tokenized_user_input[0], "mv")) {
        move_command();
    }
    else if(!strcmp(tokenized_user_input[0], "cp")) {
        copy_command();
    }
    else if(!strcmp(tokenized_user_input[0], "cat")) {
        cat_command();
    }
    else if(!strcmp(tokenized_user_input[0], "head")) {
        head_command();
    }
    else if(!strcmp(tokenized_user_input[0], "tail")) {
        tail_command();
    }
    else
    {
        printf("unkown command!\n");
    }
    
    return;
    
}

void signal_handler(int signum) {
    
    signal_occured = 1;
    if (0 != child) {
        kill(child, SIGKILL);
        printf("\n[*] process with pid: %d terminated\n", child);
    }
    else
    {
        printf("\n[*] nothing to terminate!\n");
    }
}


