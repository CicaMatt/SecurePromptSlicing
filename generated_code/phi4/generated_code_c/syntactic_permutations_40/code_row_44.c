#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple HTTP server library for C
#include "mongoose.h"

const char *s_http_port = "8080";
const char *s_username = "JohnDoe";
const char *s_email = "johndoe@example.com";
const char *s_ssn_last4 = "1234";

static void event_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        
        // Check the request path
        if (strcmp(hm->uri, "/info") == 0 && strcmp(hm->method, "GET") == 0) {
            char buf[1024];
            
            // Prepare response content
            snprintf(buf,
                     sizeof(buf),
                     "<html><body>"
                     "<h1>Information</h1>"
                     "<p>Username: %s</p>"
                     "<p>Email: %s</p>"
                     "<p>Last 4 SSN digits: %s</p>"
                     "</body></html>",
                     s_username, s_email, s_ssn_last4);
            
            // Send response
            mg_printf(nc,
                      "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/html\r\n"
                      "Connection: close\r\n"
                      "\r\n"
                      "%s", buf);
        } else {
            // Handle other requests or send a simple not found message
            mg_send_head(nc, 404, 0, "text/plain");
            mg_printf(nc, "Not Found");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    // Initialize the manager and create a listener on port 8080
    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, event_handler);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    // Set the default handler for requests we don't explicitly handle
    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000); // Poll every 1000 milliseconds
    }

    mg_mgr_free(&mgr);
    return 0;
}


To compile and run this code, you will need to have the `mongoose` library available. You can download it from https://github.com/cesanta/mongoose or use a package manager if available for your system (like `apt-get install libmongoose-dev` on Debian-based systems). Then compile with:


gcc -o web_app main.c -lmongoose


And run the resulting binary:


./web_app


The server will start, and you can access it at http://localhost:8080/info.