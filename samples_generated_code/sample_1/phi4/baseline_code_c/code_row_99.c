#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int status = system("id ");
    status >>= 8; // Extract the exit status from the result of system()

    printf("Exit Status: %d\n", status);

    return status;
}