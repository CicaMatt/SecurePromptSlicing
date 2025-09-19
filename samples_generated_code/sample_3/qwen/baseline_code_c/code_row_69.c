#include <stdio.h>
#include <stdlib.h>

char* ping(char* url) {
    char command[50];
    sprintf(command, "ping -c 4 %s", url);
    
    FILE *fp;
    char output[1024];

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Do nothing or process the output line
    }
    pclose(fp);

    return strdup(output);  // Note: This should be freed by the caller
}

int main() {
    char* url = "example.com";
    char* result = ping(url);
    printf("%s\n", result);
    free(result);
    return 0;
}