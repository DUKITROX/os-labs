/*
 * Reads NUL-terminated strings from a binary file produced by write_strings.c.
 * loadstr dynamically resizes a buffer to hold each string and returns it to
 * the caller, who prints and frees it. Continues until EOF or read error.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

/** Loads a string from a file.
 *
 * file: pointer to the FILE descriptor
 *
 * The loadstr() function must allocate memory from the heap to store
 * the contents of the string read from the FILE.
 * Once the string has been properly built in memory, the function returns
 * the starting address of the string (pointer returned by malloc())
 *
 * Returns: !=NULL if success, NULL if error
 */
char *loadstr(FILE *file)
{
    if (!file) return NULL;

    size_t cap = 64;
    size_t len = 0;
    char *buf = (char *)malloc(cap);
    if (!buf) return NULL;

    unsigned char ch;
    for (;;) {
        size_t n = fread(&ch, 1, 1, file);
        if (n != 1) {
            free(buf);
            return NULL;
        }
        if (ch == '\0') {
            //space for terminator and finish
            if (len + 1 > cap) {
                char *tmp = (char *)realloc(buf, len + 1);
                if (!tmp) { free(buf); return NULL; }
                 buf = tmp;
            }
            buf[len] = '\0';
            return buf;
        }
        //making a bigger buffer if needed
        if (len + 1 >= cap) {
            size_t ncap = cap * 2;
            char *tmp = (char *)realloc(buf, ncap);
         if (!tmp) { free(buf); return NULL; }
         cap = ncap;
            buf = tmp;
        }
        buf[len++] = (char)ch;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        err(2, "The input file %s could not be opened", argv[1]);
    }

    for (;;) {
        char *str = loadstr(file);
        if (!str) break;
        printf("%s\n", str);
        free(str);
    }

    /* Clean up and exit once all strings have been processed. */
    fclose(file);
    return 0;
}
