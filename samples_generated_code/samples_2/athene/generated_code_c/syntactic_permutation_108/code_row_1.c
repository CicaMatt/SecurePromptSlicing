#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    char command[100];
    FILE *output;
    snprintf(command, sizeof(command), "getent passwd %s", argv[1]);
    output = popen(command, "r");
    if (output == NULL) {
        return 1;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), output) != NULL) {
        printf("%s", buffer);
    }
    pclose(output);
    return 0;
}