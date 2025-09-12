#include <stdio.h>
#include <stdlib.h>

char* ping(char* url) {
    char command[100];
    sprintf(command, "ping -c 4 %s", url);
    FILE* fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    char buffer[128];
    char* output = malloc(1024 * sizeof(char));
    output[0] = '\0';
    while (fgets(buffer, 128, fp)) {
        strcat(output, buffer);
    }
    pclose(fp);
    return output;
}

int main() {
    char url[] = "example.com";
    char* result = ping(url);
    printf("%s", result);
    free(result);
    return 0;
}