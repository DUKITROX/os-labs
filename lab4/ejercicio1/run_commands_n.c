#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_SIZE 100

pid_t launch_command(char** argv){//Asumiendo q le mando argv+2
    pid_t pid;
    pid=fork();
    if(pid==0){
	execvp(argv[0], argv); 
	perror("exec failed"); 
	exit(1); 
    }
    
    return pid;
}

char **parse_command(const char *cmd, int* argc) {
    // Allocate space for the argv array (initially with space for 10 args)
    size_t argv_size = 10;
    const char *end;
    size_t arg_len; 
    int arg_count = 0;
    const char *start = cmd;
    char **argv = malloc(argv_size * sizeof(char *));

    if (argv == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (*start && isspace(*start)) start++; // Skip leading spaces

    while (*start) {
        // Reallocate more space if needed
        if (arg_count >= argv_size - 1) {  // Reserve space for the NULL at the end
            argv_size *= 2;
            argv = realloc(argv, argv_size * sizeof(char *));
            if (argv == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        // Find the start of the next argument
        end = start;
        while (*end && !isspace(*end)) end++;

        // Allocate space and copy the argument
        arg_len = end - start;
	/*
	  -s <fichero>: Esta opción permitirá al usuario indicar como argumento la ruta de un fichero con comandos a ejecutar. Este fichero será interpretado por líneas, tomando cada línea como un comando a ejecutar con la función launch_command(). Los comandos se ejecutarán de forma secuencial, esperando a que un comando termine antes de ejecutar el siguiente. Sugerencia: usar fgets() para leer del fichero por líneas. Consultar man 3 fgets
	*/
	
      argv[arg_count] = malloc(arg_len + 1);

        if (argv[arg_count] == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        strncpy(argv[arg_count], start, arg_len);
        argv[arg_count][arg_len] = '\0';  // Null-terminate the argument
        arg_count++;

        // Move to the next argument, skipping spaces
        start = end;
        while (*start && isspace(*start)) start++;
    }

    argv[arg_count] = NULL; // Null-terminate the array

    (*argc)=arg_count; // Return argc

    return argv;
}


int main(int argc, char *argv[]) {
    char **cmd_argv;
    int cmd_argc;
    int i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s \"command\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    //cmd_argv=parse_command(argv[1],&cmd_argc);
    /* Parse command-line options */
    int opt;
    while((opt = getopt(argc, argv, "x:s:")) != -1) {
          switch(opt) {
                case 'x':
                         
			cmd_argv = parse_command(optarg, &cmd_argc); 
			pid_t pid = launch_command(cmd_argv); 
			if(pid < 0) exit(1); 
			int status; 
			while(wait(&status) == pid); 
                        free(cmd_argv); 
			break;
                case 's':
			//abrir el fichero: 
			FILE * input_file = fopen(optarg, "r"); 
			//leer el fichero línea a línea; 
			char buf [MAX_SIZE]; 
			int counter = 0; 
			while(fgets(buf, MAX_SIZE, input_file) != NULL) {
				printf("@@ Running command #%d: %s \n", counter, buf); 
				cmd_argv = parse_command(buf, &cmd_argc);
	                        pid_t pid = launch_command(cmd_argv);
        	                if(pid < 0) exit(1);
                	        int status;
	                        while(wait(&status) == pid); 
				printf("@@ Comand #%d: terminated (pid: %d, status:%d)\n",counter ++, pid, status);  
			}	free(cmd_argv); 

                       

			fclose(input_file); 
                                                               
                       break; 
                case 'b':
                       
                        break;

                default:
                        exit(EXIT_FAILURE);
                }
        }
    ////////////////////////////////////////////////
    ///Use the parsed arguments 

   

    return EXIT_SUCCESS;
}

