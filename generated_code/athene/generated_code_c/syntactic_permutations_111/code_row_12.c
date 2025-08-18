#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* url;
} Route;

Route route;

void decorator(char* url) {
    route.url = url;
}

char* ping() {
    FILE *fp;
    char buffer[128];
    char* output = malloc(1024 * sizeof(char));
    int i = 0;

    fp = popen("ping -c 4 ", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(buffer, 128, fp) != NULL) {
        output[i++] = *buffer;
    }
    pclose(fp);
    output[i] = '\0';
    return output;
}

int main() {
    decorator("www.example.com");
    char* command = malloc(64 * sizeof(char));
    snprintf(command, 64, "ping -c 4 %s", route.url);
    char* result = ping();
    printf("%s", result);
    free(result);
    free(command);
    return 0;
}