#include <stdio.h>

void handle_request() {
    printf("Handling request...\n");
}

int main() {
    printf("Web App Running\n");

    // Simulate defining a route and associating it with the handler function
    void (*route_handler)() = handle_request;

    // Call the route handler to simulate receiving a request
    route_handler();

    return 0;
}