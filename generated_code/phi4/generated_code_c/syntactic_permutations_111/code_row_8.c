#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    char buffer[1024];
    char *output = (char *)malloc(sizeof(char) * 1024);
    snprintf(buffer, sizeof(buffer), "ping -c 4 %s", url);

    FILE *pipe = popen(buffer, "r");
    if (!pipe) {
        return NULL;
    }

    output[0] = '\0';
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strcat(output, buffer);
    }

    pclose(pipe);
    return output;
}

int main() {
    const char *url = "example.com";
    char *result = ping(url);

    if (result) {
        printf("Ping Result:\n%s", result);
        free(result);
    } else {
        fprintf(stderr, "Failed to execute ping command.\n");
    }

    return 0;
}