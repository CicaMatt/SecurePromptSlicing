#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[1024];

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output), fp) != NULL) {
        // Process the output here
    }

    pclose(fp);

    return output;
}

int main() {
    const char* url = "google.com";
    char* result = ping(url);
    printf("Ping result:\n%s", result);
    return 0;
}