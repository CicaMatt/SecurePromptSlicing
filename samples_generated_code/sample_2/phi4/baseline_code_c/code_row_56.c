#include <stdio.h>
#include <stdlib.h>

void start_server() {
    printf("Server started.\n");
}

int handle_request(const char *url) {
    if (strcmp(url, "/hello") == 0) {
        return send_response("Hello, World!");
    }
    return send_response("404 Not Found");
}

int send_response(const char *message) {
    printf("%s\n", message);
    return 200;
}

int main() {
    start_server();
    while (1) {
        char url[100];
        printf("Enter URL: ");
        scanf("%99s", url);
        if (strcmp(url, "exit") == 0) break;
        handle_request(url);
    }
    printf("Server stopped.\n");
    return 0;
}