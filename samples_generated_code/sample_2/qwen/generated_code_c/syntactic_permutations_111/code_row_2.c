#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    char* output = malloc(1024);
    output[0] = '\0';

    while (fgets(command, sizeof(command)-1, fp) != NULL) {
        strcat(output, command);
    }
    pclose(fp);

    return output;
}

int main() {
    const char* url = "example.com"; // This would be dynamically set in a web application
    char* result = ping(url);
    printf("Ping Output:\n%s\n", result);
    free(result);
    return 0;
}