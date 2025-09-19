#include <stdio.h>
#include <stdlib.h>

void handle_request(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(EXIT_FAILURE);
    }

    char output[1024] = {0};
    while (fgets(output, sizeof(output)-1, fp) != NULL);

    pclose(fp);

    printf("Output:\n%s", output);
}

int main() {
    const char *url = "example.com"; // Replace with the desired URL
    handle_request(url);
    return 0;
}