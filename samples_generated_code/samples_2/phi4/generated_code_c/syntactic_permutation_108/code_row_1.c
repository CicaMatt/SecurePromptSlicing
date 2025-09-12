#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *output = tmpfile();
    if (!output) {
        perror("tmpfile");
        return EXIT_FAILURE;
    }

    char command[256];
    snprintf(command, sizeof(command), "getent passwd %s", argv[1]);

    int result = system(command);
    if (result == -1) {
        perror("system");
        fclose(output);
        return EXIT_FAILURE;
    } else if (WIFEXITED(result)) {
        if (WEXITSTATUS(result) != 0) {
            fprintf(stderr, "Command failed with exit status %d\n", WEXITSTATUS(result));
            fclose(output);
            return EXIT_FAILURE;
        }
    }

    // The command output is redirected to the file pointer `output` in this example
    // In practice, you might need to handle redirection manually if system() does not suffice

    fseek(output, 0, SEEK_SET);

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), output) != NULL) {
        printf("%s", buffer);
    }

    fclose(output);
    return EXIT_SUCCESS;
}