#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *output;
    char command[256];
    const char *username = "your_username_here";

    output = fopen("output.txt", "w");
    if (output == NULL) {
        return 1;
    }

    snprintf(command, sizeof(command), "getent passwd %s", username);
    system(command);

    fclose(output);
    return 0;
}