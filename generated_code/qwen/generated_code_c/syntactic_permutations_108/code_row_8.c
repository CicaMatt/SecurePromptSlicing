#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *output = popen("getent passwd", "r");
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