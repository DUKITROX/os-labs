#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>


int main(int argc, char* argv[]){

    int N=0;
    int end_flag=0;
    int opt;

    while ((opt = getopt(argc, argv, "n:e")) != -1) {
        switch (opt) {
            case 'n':
                N = atoi(optarg);
                break;
            case 'e':
                end_flag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-n N] [-e] <filename>\n", argv[0]);
                return 1;
        }
    }

    int fd = open(argv[optind], O_RDONLY);
    if (fd < 0 ) perror("Error opening file");

    if (end_flag){
        if (lseek(fd, -N, SEEK_END)==-1){
            perror("Error in lseek");
        }
    }
    else{
        if (lseek(fd, N, SEEK_SET)==-1){
            perror("Error in lseek");
        }
    }

    char c;
    ssize_t bytes;
    while ((bytes = read(fd, &c, 1)) > 0) {
        write(STDOUT_FILENO, &c, 1);
    }

    close(fd);

    return 0;



}
