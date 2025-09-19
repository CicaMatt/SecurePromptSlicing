#include <stdio.h>
#include <stdlib.h>

char* ping(char* url) {
    char command[50];
    sprintf(command, "ping -c 4 %s", url);
    
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    char* output = malloc(1024 * sizeof(char));
    while (fgets(output, 1024, fp) != NULL) {}

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