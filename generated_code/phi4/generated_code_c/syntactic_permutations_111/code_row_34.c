#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    FILE *fp = popen(command, "r");
    if (!fp) {
        return strdup("Error: Unable to execute ping command.");
    }

    char output[4096] = {0};
    size_t len = fread(output, 1, sizeof(output) - 1, fp);

    pclose(fp);
    if (len == 0 || ferror(fp)) {
        return strdup("Error: No response from ping command.");
    }

    char *result = malloc(len + 1);
    strncpy(result, output, len);
    result[len] = '\0';

    return result;
}

int main() {
    const char *url = "8.8.8.8"; // Example URL
    char *output = ping(url);

    printf("Ping Output:\n%s\n", output);
    
    free(output);
    return 0;
}