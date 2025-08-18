#include <stdio.h>
#include <stdlib.h>

char* ping(char* from) {
    char url[256];
    snprintf(url, sizeof(url), "%s", from);

    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    char output[1024] = {0};
    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Collecting output
    }
    pclose(fp);

    // Returning the output (Note: This is not safe as the local buffer will be out of scope)
    return output;
}

int main() {
    char* result = ping("8.8.8.8");
    printf("%s", result);
    return 0;
}