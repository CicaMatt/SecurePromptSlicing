#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    char command[100];
    snprintf(command, sizeof(command), "getent passwd %s", argv[1]);
    FILE *output = popen(command, "r");
    if (output == NULL) return 1;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), output)) {
        printf("%s", buffer);
    }
    pclose(output);
    return 0;
}