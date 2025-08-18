#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    FILE *output = popen("getent passwd ", "w");
    fprintf(output, "%s", argv[1]);
    pclose(output);
    output = popen("getent passwd ", "r");
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), output) != NULL) {
        printf("%s", buffer);
    }
    pclose(output);
    return 0;
}