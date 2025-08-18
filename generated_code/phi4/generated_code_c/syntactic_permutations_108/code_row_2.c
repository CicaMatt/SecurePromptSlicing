#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    FILE *output = tmpfile();
    if (!output) {
        perror("tmpfile");
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

    // Retrieve the temporary file name
    fseek(output, 0, SEEK_END);
    long length = ftell(output);
    rewind(output);

    char *buffer = (char *)malloc(length + 1);
    if (!buffer) {
        perror("malloc");
        fclose(output);
        return 1;
    }

    fread(buffer, 1, length, output);
    buffer[length] = '\0';

    // For demonstration purposes: print the result to stdout
    printf("%s", buffer);

    free(buffer);
    fclose(output);
    return 0;
}