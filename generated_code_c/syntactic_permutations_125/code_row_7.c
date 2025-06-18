#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define MAX_LEN 1024
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid arguments\n");
        return -1;
    }
    char buffer[MAX_LEN];
    strcpy(buffer, argv[1]);
    int i = strlen(buffer) - 1;
    while (isspace(buffer[i])) {
        buffer[i] = '\0';
        i--;
    }
    printf("%s\n", buffer);
    return 0;
}