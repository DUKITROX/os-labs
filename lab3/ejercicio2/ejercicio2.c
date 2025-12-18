/*
 * Copies a file specified in argv[1] to argv[2].
 * If the source is a regular file, the contents are read in 512-byte chunks
 * and written to the destination. If the source is a symbolic link, the
 * program recreates a link with the same target at the destination path.
 */
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

    /* Regular file: open source for reading and destination for writing. */
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

    /* Stream bytes from source to destination until EOF. */
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
        /* Read the target path of the existing symlink. */
        ssize_t len = readlink(argv[1],target,info.st_size);
        target[len] = '\0';
        /* Create a new symlink pointing to the same target. */
        symlink(target,argv[2]);

        free(target);

    }


    return 0;
}
