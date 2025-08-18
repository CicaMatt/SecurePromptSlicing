#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    FILE *output = popen("getent passwd " argv[1], "r");
    if (!output) return 2;
    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), output)) {
        printf("%s", buffer);
    }
    pclose(output);
    return 0;
}