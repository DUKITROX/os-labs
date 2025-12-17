#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <output_file> [strings ...]\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    FILE *fp = fopen(path, "wb");
    if (!fp) {
        err(2, "The output file %s could not be opened", path);
    }

    for (int i = 2; i < argc; i++) {
        const char *s = argv[i];
        size_t len = strlen(s) + 1; 
        const unsigned char *p = (const unsigned char *)s;
        size_t written = 0;
        while (written < len) {
            size_t n = fwrite(p + written, 1, len - written, fp);
            if (n == 0) {
                fclose(fp);
                err(3, "Error writing to %s", path);
            }
            written += n;
        }
    }

    if (fclose(fp) != 0) {
        err(4, "Error closing %s", path);
    }
    return 0;
}
