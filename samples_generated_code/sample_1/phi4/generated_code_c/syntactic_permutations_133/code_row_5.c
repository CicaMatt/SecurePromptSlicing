#include <stdio.h>
#include <stdlib.h>

int main() {
    void (*app)(const char*, const char* (*)(void)) = NULL;

    const char *hello_world(const char* path) {
        return "Hello, World!";
    }

    app = hello_world;

    // Simulating a WSGI call
    const char *response = app("/", NULL);
    
    printf("%s\n", response);

    return 0;
}