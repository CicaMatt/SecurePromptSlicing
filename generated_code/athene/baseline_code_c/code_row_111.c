#include <stdio.h>
#include <stdlib.h>

char* ping(char *url) {
    char command[100];
    sprintf(command, "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to execute ping command";
    }
    char output[1024];
    fgets(output, sizeof(output), fp);
    pclose(fp);
    return output;
}

int main() {
    char url[] = "example.com"; // Example URL
    char *result = ping(url);
    printf("%s", result);
    return 0;
}