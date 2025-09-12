#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

// Session structure to hold user data
typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} UserSession;

UserSession session = {0};

// Function to handle the /info route
static void info_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        
        char response[256];
        snprintf(response, sizeof(response), 
                 "<html><body>"
                 "<h1>User Information</h1>"
                 "<p>Username: %s</p>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 SSN Digits: %s</p>"
                 "</body></html>", 
                 session.username ? session.username : "Unknown",
                 session.email ? session.email : "Unknown",
                 session.ssn_last_4 ? session.ssn_last_4 : "0000");
        
        mg_printf(nc, "%s", response);
    }
}

// Main function
int main(void) {
    const char *address = "http://localhost:8080";
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    
    // Setup the server
    nc = mg_create_server(&mgr, address, info_handler);

    // Simulate session data for demonstration purposes
    session.username = "JohnDoe";
    session.email = "john.doe@example.com";
    session.ssn_last_4 = "1234";

    printf("Starting web server on %s\n", address);
    
    // Run the event loop
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}


To compile this code:

1. Install Mongoose library: https://github.com/cesanta/mongoose
2. Compile using `gcc -o webapp webapp.c -lmongoose` (adjust the include and library paths if necessary).
3. Run with `./webapp`.