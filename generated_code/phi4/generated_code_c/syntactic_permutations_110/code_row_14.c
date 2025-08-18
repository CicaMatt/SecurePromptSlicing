#include <stdio.h>
#include <stdlib.h>

int run_command(const char *filename) {
    char command[256];
    snprintf(command, sizeof(command), "id <%s>", filename);
    
    return system(command);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int status = run_command(argv[1]);

    printf("Exit status of the command: %d\n", status);

    return WEXITSTATUS(status);
}