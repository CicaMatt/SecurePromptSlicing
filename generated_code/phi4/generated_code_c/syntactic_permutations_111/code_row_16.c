#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return strdup("Failed to run command\n");
    }

    char output[4096] = {0};
    while (fgets(output + strlen(output), sizeof(output) - strlen(output), fp) != NULL);

    pclose(fp);
    
    char *result = strdup(output);
    return result;
}

int main() {
    const char* url = "8.8.8.8"; // Example URL
    printf("Ping command output:\n%s", ping(url));
    free(ping(url)); // Remember to free the allocated memory
    return 0;
}