/*
 * Simple file copy utility.
 * Opens a source file (argv[1]) for reading and copies its contents into
 * a destination file (argv[2]) using a 512-byte buffer until EOF.
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>



int main(int argc, char *argv[]){

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

    /* Read and write in fixed-size chunks until no more bytes are available. */
    bytes_read = read(original, buffer, 512);
    while (bytes_read > 0){
        write(destinacion, buffer, bytes_read );
        bytes_read = read(original, buffer, 512);
    }
    close(original);
    close(destinacion);

    return 0;
}
