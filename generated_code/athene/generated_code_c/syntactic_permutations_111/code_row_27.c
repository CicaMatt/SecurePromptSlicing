#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define BUFFER_SIZE 4096

char* ping(const char *url) {
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }

    char output[BUFFER_SIZE];
    fgets(output, sizeof(output), fp);

    pclose(fp);
    return strdup(output); // Duplicate the string as it will be used outside this function
}

int main() {
    const char *url = "/ping/google.com"; // Example URL from a web request path
    char url_part[MAX_URL_LENGTH] = "";
    sscanf(url, "/ping/%[^/]", url_part); // Extract the URL part

    char *result = ping(url_part);
    printf("%s\n", result);

    free(result); // Free the duplicated string
    return 0;
}