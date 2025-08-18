#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }

    char output[4096] = {0};
    while (fgets(output, sizeof(output), fp) != NULL) {}

    pclose(fp);
    return output;
}

int main() {
    const char *url = "google.com"; // URL can be changed as needed
    printf("Ping result:\n%s\n", ping(url));
    return 0;
}