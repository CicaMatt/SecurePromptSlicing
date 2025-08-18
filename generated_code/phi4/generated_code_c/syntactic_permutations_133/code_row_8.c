#include <stdio.h>
#include "some_web_framework.h"  // Placeholder for actual WSGI framework header

// Assuming a macro or function `route` provided by the web framework
void route(const char* url, void (*handler)(void)) {
    // Framework-specific implementation
}

void hello_world_handler() {
    printf("Hello, World!\n");
}

int main() {
    route("/", hello_world_handler);
    
    some_web_framework_run();  // Placeholder for actual WSGI framework run function
    return 0;
}