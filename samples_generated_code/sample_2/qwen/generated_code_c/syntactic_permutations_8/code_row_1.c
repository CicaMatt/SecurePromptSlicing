#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <index> <comma,separated,string>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);
    char *values = argv[2];
    char *token;
    int count = 0;

    token = strtok(values, ",");
    while (token != NULL) {
        if (count == index) {
            printf("%s\n", token);
            return 0;
        }
        count++;
        token = strtok(NULL, ",");
    }

    printf("Index out of range.\n");
    return 1;
}