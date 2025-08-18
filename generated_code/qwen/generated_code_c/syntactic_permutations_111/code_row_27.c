#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    char* output = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&output, &len, fp)) != -1) {
        printf("%s", output); // This line is for demonstration purposes
    }

    pclose(fp);
    return output; // Note: Returning a pointer to dynamically allocated memory that needs to be freed.
}

int main() {
    const char* url = "google.com"; // Example URL
    char* result = ping(url);
    free(result); // Free the memory allocated by getline
    return 0;
}