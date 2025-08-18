#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *output;
    char command[256];
    const char *username = "your_username_here"; // Replace with actual username

    output = popen(command, "w");
    if (!output) {
        perror("popen");
        return EXIT_FAILURE;
    }

    snprintf(command, sizeof(command), "getent passwd %s", username);
    system(command);

    pclose(output);
    return EXIT_SUCCESS;
}