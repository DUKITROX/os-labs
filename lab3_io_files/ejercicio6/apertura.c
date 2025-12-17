#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char* argv[]){

	int rd=0,wr=0;
    int opt;
	char filename[256] = "";

	if(argc < 4){
		fprintf(stderr, "Usage: %s -f <filename> [-r | -w]\n", argv[0]);
		return 1;
	}

    while ((opt = getopt(argc, argv, "f:rw")) != -1) {
        switch (opt) {
            case 'f':
				strcpy(filename, optarg);
				filename[sizeof(filename)-1] = '\0';
                break;
            case 'r':
				rd=1;
                break;
			case 'w':
				wr=1;
				break;
            default:
				fprintf(stderr, "Usage: %s -f <filename> [-r | -w]\n", argv[0]);
                return 1;
        }
    }
	
	int fd,flags=0;
	if (rd && wr)
		flags = O_RDWR | O_CREAT | O_TRUNC;
	else if (rd)
		flags = O_RDONLY;             
	else if (wr)
		flags = O_WRONLY | O_CREAT | O_TRUNC;

	fd = open(filename, flags, 0644);
	if (fd < 0)
		perror("Error opening file");	

	if(write(fd, "bomboclat", 10) < 0)
		perror("Could not write file\n");

	char buf[10];
	if(read(fd, buf, 10) < 0)
		perror("Could not read file\n");

    close(fd);
    return 0;
}
