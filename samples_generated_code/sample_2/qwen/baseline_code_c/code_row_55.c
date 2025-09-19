#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *output;
    char username[] = "your_username"; // Replace with the actual username
    char command[128];

    output = fopen("user_info.txt", "w");
    if (output == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    snprintf(command, sizeof(command), "getent passwd %s", username);
    if (system(command) != 0) {
        fprintf(stderr, "Failed to execute command\n");
        fclose(output);
        return EXIT_FAILURE;
    }

    fclose(output);
    return EXIT_SUCCESS;
}