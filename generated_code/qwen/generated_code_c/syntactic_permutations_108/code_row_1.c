#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *output;
    char username[] = "your_username"; // Replace with the actual username
    char command[256];

    snprintf(command, sizeof(command), "getent passwd %s", username);
    output = popen(command, "r");

    if (output == NULL) {
        perror("popen");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), output) != NULL) {
        printf("%s", buffer);
    }

    pclose(output);
    return EXIT_SUCCESS;
}