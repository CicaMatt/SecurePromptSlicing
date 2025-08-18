#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("%s\n", argv[2]);
    } else {
        printf("Not enough arguments provided.\n");
    }
    return 0;
}