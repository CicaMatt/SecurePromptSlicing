#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* username = "your_username_here"; // Replace with actual username
    FILE *output;
    char command[1024];

    sprintf(command, "getent passwd %s", username);
    output = popen(command, "r");

    if (!output) {
        perror("popen");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), output)) {
        printf("%s", buffer);
    }

    pclose(output);
    return EXIT_SUCCESS;
}