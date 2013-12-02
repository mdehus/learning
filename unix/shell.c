#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#define MAXLINE 256
#define MAXARGS 12
#define SEPERATOR ' '

void parse_cmd(char *cmd, char **argv)
{     
    // Tokenize arguments and build argv
    char *token;
    int argc = 0;

    token = strtok(cmd," ");
    while (token != NULL)
    {
        argv[argc] = token;
        token = strtok(NULL, " ");
        argc += 1;
    
        if (token == NULL)
            argv[argc] = token;
    }
}

void print_args(char **argv)
{
    char *val;
    int i = 0;

    while ((val = argv[i]) != NULL)
    {
        printf("%d: %s\n", i, val);
        i += 1;
    }
}

int run_cmd(char **argv) 
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) 
    {
        printf("Something is forked up\n");
        return 1;
    }   

    else if (pid == 0) // child
    {
        execvp(argv[0], argv);
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((pid = waitpid(pid, &status, 0)) < 0)
    {
        printf("Failed on waitpid\n");
        return status;
    }

    return status;
}

int main(void) 
{
    char buf[MAXLINE];
    char *argv[MAXARGS];
    int status;

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

        if (strncasecmp(buf, "exit", 4) == 0)
            return 0;

        parse_cmd(buf, argv);
        print_args(argv);
        status = run_cmd(argv);
        printf("(%d)\n%% ", status);
    }        
}
