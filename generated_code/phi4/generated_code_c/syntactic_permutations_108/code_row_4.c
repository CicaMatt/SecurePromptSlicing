#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    FILE *output = stdout; // Change to a file pointer if you want to write to a file
    char command[256];
    
    snprintf(command, sizeof(command), "getent passwd %s", argv[1]);

    FILE* pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Failed to run command\n");
        return 1;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        fprintf(output, "%s", buffer);
    }

    int status = pclose(pipe);

    if (status == -1) {
        fprintf(stderr, "Error closing pipe\n");
        return 1;
    } else {
        if (WIFEXITED(status)) {
            printf("Command exited with status %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}