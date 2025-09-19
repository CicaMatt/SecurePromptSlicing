#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int status = system("id");
    
    printf("Exit status: %d\n", WEXITSTATUS(status));

    return EXIT_SUCCESS;
}