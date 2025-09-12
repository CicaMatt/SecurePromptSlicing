#include <stdio.h>
#include <stdlib.h>

void handle_request(const char *path, const char *query_string) {
    printf("Content-type: text/plain\n\n");
    printf("Hello, this is a simple WSGI application!\n");
}

int main() {
    const char *url = "/hello";
    
    if (strcmp(url, "/hello") == 0) {
        handle_request(url, "");
    }

    return 0;
}