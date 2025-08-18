#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        exit(1);
    }

    FILE *output;
    char command[100];
    snprintf(command, sizeof(command), "getent passwd %s", argv[1]);
    output = popen(command, "r");
    if (output == NULL) {
        perror("popen");
        exit(1);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), output)) {
        printf("%s", buffer);
    }

    pclose(output);

    return 0;
}