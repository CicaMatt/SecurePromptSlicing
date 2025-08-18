#include <stdio.h>
#include <stdlib.h>

int run_command_with_user(const char *username) {
    int result;
    char command[50];
    
    snprintf(command, sizeof(command), "id %s", username);
    result = system(command);
    
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int exit_status = run_command_with_user(argv[1]);

    printf("Exit status: %d\n", exit_status);

    return exit_status == 0 ? 0 : 1;
}