#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void execute_command(char* cmd) {
    int result = system(cmd);
    if (result != 0) {
        fprintf(stderr, "failed to execute command\n");
        exit(1);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "no username specified\n");
        return 1;
    }
    int username_length = strlen(argv[1]);
    char* cmd = malloc((username_length + 25) * sizeof(char));
    if (cmd == NULL) {
        fprintf(stderr, "failed to allocate memory\n");
        return 1;
    }
    sprintf(cmd, "cat /etc/passwd | grep %s", argv[1]);
    execute_command(cmd);
    free(cmd);
    return 0;
}