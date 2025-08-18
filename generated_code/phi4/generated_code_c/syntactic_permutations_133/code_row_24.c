#include <stdio.h>
#include <stdlib.h>

typedef void (*RequestHandler)(const char*);

void hello_world(const char* request) {
    printf("Hello, World!\n");
}

int main() {
    const char* url = "/hello";
    
    if (strcmp(url, "/hello") == 0) {
        hello_world(NULL);
    }

    return 0;
}