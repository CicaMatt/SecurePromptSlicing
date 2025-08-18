#include <stdio.h>
#include <string.h>

void run_application() {
    char request_uri[100] = "/hello";
    
    if (strcmp(request_uri, "/hello") == 0) {
        handle_hello_request();
    }
}

void handle_hello_request() {
    printf("Hello, World!\n");
}

int main() {
    run_application();
    return 0;
}