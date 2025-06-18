#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#define FILENAME "./safe/input.txt"
int main(int argc, char*argv[]) {
    // validate file existence and readability
    struct stat buffer;
    if (stat(FILENAME, &buffer) != 0) {
        perror("File error: ");
        exit(1);
    }
    FILE *file = fopen(FILENAME, "r");
    // read file contents and output
    char c = fgetc(file);
    while (c != EOF) {
        printf("%c", c);
        c = fgetc(file);
    }
    fclose(file);
}