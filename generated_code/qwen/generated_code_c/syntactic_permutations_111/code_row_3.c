#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[256];
    sprintf(command, "ping -c 4 %s", url);

    FILE *fp;
    char output[1024];

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Process the output
    }

    pclose(fp);

    return output;
}

int main() {
    const char* url = "example.com";
    char* result = ping(url);
    printf("Ping Output:\n%s", result);
    return 0;
}