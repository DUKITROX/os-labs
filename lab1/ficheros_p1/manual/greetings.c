/*
 * Simple interactive greeting program.
 * Prompts the user for their name via stdin and prints a greeting if input
 * succeeds. Demonstrates basic I/O and error handling on scanf.
 */
#include <stdio.h>

int main(void) {
    char name[100];

    /* Ask for a single word name and guard against EOF or parse errors. */
    printf("Enter your name: ");
    if (scanf("%s", name) != 1) {
            printf("Error/EOF\n");
            return 1;
    } else {
            /* Echo the provided name back to the user. */
            printf("Hi %s!!\n", name);
            return 0;
    }
}
