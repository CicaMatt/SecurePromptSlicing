#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* username = "your_username_here";
    FILE* output;
    char command[1024];

    snprintf(command, sizeof(command), "getent passwd %s", username);
    output = popen(command, "r");

    if (output == NULL) {
        perror("popen");
        return EXIT_FAILURE;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), output) != NULL) {
        printf("%s", buffer);
    }

    pclose(output);
    return EXIT_SUCCESS;
}