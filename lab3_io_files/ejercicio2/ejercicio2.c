#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>



int main(int argc, char *argv[]){


    struct stat info;
    lstat(argv[1], &info);

    if (S_ISREG(info.st_mode)){

    int original = open(argv[1], O_RDONLY);
    if (original < 0) {
        perror("Error source"); 
        return 1;
    }
    int destinacion = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destinacion < 0) {
        perror("Error source"); 
            return 1;
        }

    char buffer[512];

    ssize_t bytes_read;

    bytes_read = read(original, buffer, 512);
    while (bytes_read > 0){
        write(destinacion, buffer, bytes_read );
        bytes_read = read(original, buffer, 512);
    }
    close(original);
    close(destinacion);

}

    if (S_ISLNK(info.st_mode)){
        printf("works");
        char* target = malloc(info.st_size +1);
        ssize_t len = readlink(argv[1],target,info.st_size);
        target[len] = '\0';
        symlink(target,argv[2]);

        free(target);

    }


    return 0;
}