#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    static char output[1024];
    char command[512];

    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        snprintf(output, sizeof(output), "Failed to run the ping command.");
        return output;
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
    }
    
    pclose(fp);

    return output;
}

int main() {
    const char *url = "www.example.com";
    printf("%s\n", ping(url));
    return 0;
}