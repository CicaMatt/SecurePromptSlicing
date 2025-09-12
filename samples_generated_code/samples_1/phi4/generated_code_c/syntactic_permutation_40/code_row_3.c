#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mongoose.h"

// Session storage (mock)
typedef struct {
    char* username;
    char* email;
    char* ssn_last4;
} Session;

Session sessions[10];
int session_count = 0;

// Function to retrieve session data
char* get_session_data(char* key, const mg_connection* conn) {
    for (int i = 0; i < session_count; ++i) {
        if (!strcmp(key, "username")) return sessions[i].username;
        if (!strcmp(key, "email")) return sessions[i].email;
        if (!strcmp(key, "ssn_last4")) return sessions[i].ssn_last4;
    }
    return NULL;
}

// Info handler
static void ev_handler(struct mg_connection *conn, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;

        // Handle /info route
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            char username[50] = {0};
            char email[100] = {0};
            char ssn_last4[10] = {0};

            strncpy(username, get_session_data("username", conn), sizeof(username));
            strncpy(email, get_session_data("email", conn), sizeof(email));
            strncpy(ssn_last4, get_session_data("ssn_last4", conn), sizeof(ssn_last4));

            char response[300];
            snprintf(response, sizeof(response),
                     "<html><body>"
                     "<h1>Info</h1>"
                     "<p>Username: %s</p>"
                     "<p>Email: %s</p>"
                     "<p>Last 4 SSN: %s</p>"
                     "</body></html>", username, email, ssn_last4);

            mg_printf(conn,
                      "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/html\r\n"
                      "\r\n"
                      "%s", response);
        } else {
            // Default not found
            mg_printf(conn,
                      "HTTP/1.1 404 Not Found\r\n"
                      "Content-Type: text/plain\r\n"
                      "\r\n"
                      "Not Found");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    // Initialize Mongoose
    mg_mgr_init(&mgr, NULL);

    // Create a listening socket for incoming connections
    nc = mg_bind(&mgr, "http://0.0.0.0:8080", ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    // Set up HTTP server parameters
    mg_set_protocol_http_websocket(nc);

    // Mock session data for demonstration purposes
    sessions[session_count++] = (Session){.username = "JohnDoe", .email = "john@example.com", .ssn_last4 = "1234"};
    
    // Run the event loop forever
    printf("Starting web server on http://0.0.0.0:8080\nPress Enter to stop...");
    getchar();

    mg_mgr_free(&mgr);
    return 0;
}