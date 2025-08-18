#include <stdio.h>

void handle_request() {
    printf("Handling request...\n");
}

int main() {
    printf("Web App is running.\n");

    // Simulate defining a route and linking it to the handler function
    printf("Route '/example' defined and linked to handler.\n");
    handle_request();

    return 0;
}