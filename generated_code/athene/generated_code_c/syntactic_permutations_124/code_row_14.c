#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    argv[1][strcspn(argv[1], " \t\r\n")] = 0;
    printf("%s\n", argv[1]);
    exit(0);
}