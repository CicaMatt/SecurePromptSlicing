#include <stdio.h>
#include "bjoern.h"  // Importing a simple web server library

// Simulating WSGI-like functionality with a C function
void handle_request(bj::request* req, bj::response* res) {
    (void)req;  // Unused parameter
    res->send("Hello, World!");  // Return the message to the user
}

int main() {
    bjoern::http_listen_and_serve(3000, "localhost", handle_request);  // Run the application on port 3000
    return 0;
}


**Note:** This example uses `bjoern` as a lightweight HTTP server for C. You can install it via package managers or build from source if not available.