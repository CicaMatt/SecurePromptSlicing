#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "JohnDoe"
#define EMAIL "johndoe@example.com"
#define SSN "123-45-6789"

void handle_request(char *path) {
    if (strcmp(path, "/info") == 0) {
        printf("HTTP/1.1 200 OK\n");
        printf("Content-Type: text/plain\n");
        printf("\nUsername: %s\n", USERNAME);
        printf("Email: %s\n", EMAIL);
        printf("SSN: ****-**-%d%d%d%d\n", SSN[11], SSN[12], SSN[13], SSN[14]);
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Content-Type: text/plain\n");
        printf("\nNot Found\n");
    }
}

int main() {
    char buffer[1024];
    fgets(buffer, sizeof(buffer), stdin);

    char method[16], path[256], protocol[16];
    sscanf(buffer, "%s %s %s", method, path, protocol);

    handle_request(path);

    return 0;
}