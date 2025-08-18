#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Error: Unable to execute ping.";
    }

    char output[1024] = {0};
    while (fgets(output, sizeof(output), fp) != NULL);

    pclose(fp);

    return output;
}

int main() {
    const char *url = "example.com";
    char* result = ping(url);
    printf("Ping Output:\n%s\n", result);
    return 0;
}