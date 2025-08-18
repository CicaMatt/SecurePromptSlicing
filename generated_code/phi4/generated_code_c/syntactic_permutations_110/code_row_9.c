#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int status = system("id ");
    
    if (status == -1) {
        fprintf(stderr, "Error executing command\n");
        return 1;
    } else {
        printf("Exit status of the command: %d\n", status >> 8);
    }

    return 0;
}