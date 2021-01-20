#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "core_functions.h"

extern char* tokenized_user_input[32];
extern size_t user_input_size;

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
        printf("illegal number of arguments!\n");
        return;
    }
    if(chdir(tokenized_user_input[1]) != -1) {

    }  
}

void clear_screen() {
    execv("/bin/clear", (char*[]){"clear", NULL});
}

void lsdir_command() {
    if (user_input_size > 2)
    {
        printf("illegar number of arguments!\n");
        return;
    }
    else if (user_input_size == 2)
        execl("/bin/find", "find", ".", "-maxdepth",  "1", "-type", "d", "-name", tokenized_user_input[1], NULL);
    else if(user_input_size == 1)
        execl("/bin/find", "find", ".", "-maxdepth",  "1", "-type", "d", NULL);
}

void rename_command() {
    if (user_input_size != 3)
    {
        printf("illegal number of arguments!\n");
        return;
    }
    if(-1 == rename(tokenized_user_input[1], tokenized_user_input[2])) {
        switch (errno)
        {
            case ENOENT:
                printf("one or two of input files does not exist!\n");
                break;
            case EPERM:
                printf("permission denied!!\n");
                break;
            default:
                printf("cant perform this task\n");
                break;
        }
    }     
}

void remove_command() {
    if (user_input_size != 2)
    {
        printf("illegal number of arguments!\n");
        return;
    }
    if(-1 == remove(tokenized_user_input[1])) {
        switch (errno)
        {
            case ENOENT:
                printf("file %s does not exist!\n", tokenized_user_input[1]);
                break;
            case EPERM:
                printf("permission denied!!\n");
                break;
            default:
                printf("cant perform this task\n");
                break;
        }
    }     
}

void move_command() {
    if (user_input_size != 3)
    {
        printf("illegal number of arguments!\n");
        return;
    }
    if(-1 == execl("/bin/mv", "mv", tokenized_user_input[1], tokenized_user_input[2], NULL)) {
        switch (errno)
        {
            case ENOENT:
                printf("one provided file does not exist!\n");
                break;
            case EPERM:
                printf("permission denied!!\n");
                break;
            default:
                printf("cant perform this task\n");
                break;
        }
    } 
}

void copy_command(){
    if (user_input_size != 3)
    {
        printf("illegal number of arguments!\n");
        return;
    }
    if(-1 == execl("/bin/cp", "cp", tokenized_user_input[1], tokenized_user_input[2], NULL)) {
        switch (errno)
        {
            case ENOENT:
                printf("one provided file does not exist!\n");
                break;
            case EPERM:
                printf("permission denied!!\n");
                break;
            default:
                printf("cant perform this task\n");
                break;
        }
    } 
}

void cat_command() {
    if (user_input_size != 2)
    {
        printf("illegal number of arguments!\n");
        return;
    }
    if(-1 == execl("/bin/cat", "cat", tokenized_user_input[1], NULL)) {
        switch (errno)
        {
            case ENOENT:
                printf("file %s does not exist!\n", tokenized_user_input[1]);
                break;
            case EPERM:
                printf("permission denied!!\n");
                break;
            default:
                printf("cant perform this task\n");
                break;
        }
    } 
}

void head_command(){
    if (user_input_size != 2)
    {
        printf("illegal number of arguments!\n");
        return;
    }
    if(-1 == execl("/bin/head", "head", tokenized_user_input[1], NULL)) {
        switch (errno)
        {
            case ENOENT:
                printf("file %s does not exist!\n", tokenized_user_input[1]);
                break;
            case EPERM:
                printf("permission denied!!\n");
                break;
            default:
                printf("cant perform this task\n");
                break;
        }
    } 
}

void tail_command(){
    if (user_input_size != 2)
    {
        printf("illegal number of arguments!\n");
        return;
    }
    if(-1 == execl("/bin/tail", "tail", tokenized_user_input[1], NULL)) {
        switch (errno)
        {
            case ENOENT:
                printf("file %s does not exist!\n", tokenized_user_input[1]);
                break;
            case EPERM:
                printf("permission denied!!\n");
                break;
            default:
                printf("cant perform this task\n");
                break;
        }
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



