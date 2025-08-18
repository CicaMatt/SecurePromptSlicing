#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ping(const char *url) {
    char buffer[1024];
    char command[2048];

    snprintf(command, sizeof(command), "ping %s", url);

    FILE *fp = popen(command, "r");
    if (!fp) {
        return strdup("Error executing ping command.");
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        strcat(output, buffer);
    }

    pclose(fp);
    return output;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    static char output[4096] = {0}; // Static to persist data across function calls
    const char *url = argv[1];

    char *result = ping(url);
    printf("%s\n", result);

    free((void *)result); // Assuming strdup was used in the case of an error
    return 0;
}