#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char command[256];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    int status = system(command);
    
    if (status == -1) {
        perror("System call failed");
        return EXIT_FAILURE;
    }
    
    printf("Exit status: %d\n", WEXITSTATUS(status));
    return 0;
}