#include <stdio.h>
#include <stdlib.h>

char* url = "http://example.com";

void run_command() {
    char command[256];
    snprintf(command, sizeof(command), "curl -s %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    pclose(fp);
}

int main() {
    run_command();
    return 0;
}