#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

char** parse_arg(char* command)
{

    char *delims = " \t\r\n";
    char *token = strtok(command, delims);

    char **result = malloc(1024);
    while (token != NULL)
    {
        // add token to result which is a char**
        int i = 0;
        // get last index of result
        while (result[i] != NULL)
            i++;

        result[i] = malloc(strlen(token) + 1);
        strcpy(result[i], token);
        result[i + 1] = NULL;

        token = strtok(NULL, delims);
    }
    return result;
}

pid_t launch_command(char **args)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        execvp(args[0], args);
        perror("Error executing command");
        _exit(127);
    }
    return pid;
}


int main(int argc, char **argv)
{

    int opt;
    while ((opt = getopt(argc, argv, "x:s:")) != -1)
    {
        switch (opt)
        {
        case 'x':
            char **res = parse_arg(optarg);
            pid_t pid = launch_command(res);
            if (pid < 0)
            {
                perror("Error launching command");
            }
            int status = 0;
            if (waitpid(pid, &status, 0) < 0)
            {
                perror("Error waiting for command");
            }

            break;

        case 's':

            FILE* file = fopen(optarg, "r");
            if (file == NULL) {
                perror("Error opening script file");
                exit(EXIT_FAILURE);
            }

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("Executing command: %s", buffer);

            char** res2= parse_arg(buffer);
            pid_t pid2 = launch_command(res2);
            if (pid2 < 0)
            {
                perror("Error launching command");
            }
            int status2 = 0;
            if (waitpid(pid2, &status2, 0) < 0)
            {
                perror("Error waiting for command");
            }

        }

            break;

        default:
            break;
        }
    }
}
