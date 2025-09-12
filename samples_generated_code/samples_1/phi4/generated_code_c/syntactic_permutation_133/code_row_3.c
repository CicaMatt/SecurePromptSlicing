#include <stdio.h>

typedef struct {
    void (*start)(void);
} WSGIApplication;

WSGIApplication app;

int main() {
    app.start = (void (*)(void))start;
    
    printf("Hello, World!\n");

    return 0;
}

void start(void) {
    // This is the function that would be called when a specific URL is visited.
}