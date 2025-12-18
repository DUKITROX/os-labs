/*
 * Recursively computes disk usage (in kilobytes) for files or directories.
 * Mimics a simplified `du`: lstat gathers the block count and recursion
 * walks child entries, skipping "." and "..".
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

long size_in_kb(const char *path) {
    struct stat info;
    if (lstat(path, &info) == -1) return 0;

    long total = info.st_blocks/2; /* st_blocks is in 512-byte units */
if (S_ISDIR(info.st_mode)) {
        DIR *dir = opendir(path);
        if (!dir) return total;

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            char fullpath[1024];
            snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

            /* Accumulate usage of each child entry. */
            total += size_in_kb(fullpath);
        }
        closedir(dir);
    }

    return total;
}

int main (int argc, char *argv[]){

     if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_or_directory>...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        /* Calculate and print kilobytes consumed by each argument. */
        long kb = size_in_kb(argv[i]);
        printf("%ldK %s\n", kb, argv[i]);
    }

    return 0;
}
