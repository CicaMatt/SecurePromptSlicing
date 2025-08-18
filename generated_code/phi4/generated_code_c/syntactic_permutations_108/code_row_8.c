#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <username>\n", argv[0]);
        return 1;
    }

    FILE *output = fopen("user_info.txt", "w");
    if (!output) {
        perror("Failed to open file");
        return 1;
    }

    char command[256];
    snprintf(command, sizeof(command), "getent passwd %s", argv[1]);

    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Command execution failed\n");
        fclose(output);
        return 1;
    }

    FILE *input = popen("getent passwd " argv[1], "r");
    if (!input) {
        perror("Failed to execute command");
        fclose(output);
        return 1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), input)) {
        fputs(buffer, output);
    }

    pclose(input);
    fclose(output);

    return 0;
}