#include <stdio.h>
#include <string.h>

int main() {
    char filename[] = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    char username[256];
    if (fgets(username, sizeof(username), file) != NULL) {
        // Remove newline character from the end of the username
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }

        char response[256];
        snprintf(response, sizeof(response), "hello %s", username);

        printf("%s\n", response); // Simulating sending the response back to the client
    } else {
        fprintf(stderr, "Failed to read from file\n");
    }

    fclose(file);
    return 0;
}