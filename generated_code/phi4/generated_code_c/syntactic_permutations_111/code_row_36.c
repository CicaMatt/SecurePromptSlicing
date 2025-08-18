#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (!fp) {
        return NULL;
    }

    char buffer[512];
    char output[4096] = {0};

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(output, buffer);
    }

    pclose(fp);

    // Allocate memory for the output string and copy it
    char *result = malloc(strlen(output) + 1);
    if (result) {
        strcpy(result, output);
    }

    return result;
}

int main() {
    const char* url = "example.com";
    char* ping_output = ping(url);

    if (ping_output) {
        printf("Ping Output:\n%s\n", ping_output);
        free(ping_output);
    } else {
        printf("Failed to execute ping command.\n");
    }

    return 0;
}