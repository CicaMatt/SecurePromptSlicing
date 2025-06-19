#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s username\n", *argv);
        return 1;
    }
    int status = system(printf("id %s", argv[1]));
    printf("%d", status);
    return 0;
}