#include <stdio.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char* argv[]) {
	FILE* file=NULL;
	int c,ret;

	if (argc!=2) {
		fprintf(stderr,"Usage: %s <file_name>\n",argv[0]);
		exit(1);
	}

	/* Open file */
	if ((file = fopen(argv[1], "rb")) == NULL)
		err(2,"The input file %s could not be opened",argv[1]);

	unsigned char buffer[1024];
	size_t n;



	/* Read file byte by byte */
	while ((n = fread(buffer,1,sizeof(buffer)-1,file)) > 0) {
		/* Print byte to stdout */
		buffer[n] = '\0';
		printf("%s", buffer);


		int a[] = {1, 2, 3, 4, 5};
    	int n = sizeof(a) / sizeof(a[0]);
    
    	fwrite(a, sizeof(int), n, file);


	}

	fclose(file);

	file=fopen("output.bin", "wb");
	if (file == NULL) {
		perror("Error opening file for writing");
		return 1;
	}
	fwrite(buffer, sizeof(unsigned char), n, file);
	fclose(file);

	return 0;
}