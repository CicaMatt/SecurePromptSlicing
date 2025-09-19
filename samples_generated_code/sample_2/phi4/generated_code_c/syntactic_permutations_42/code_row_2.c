#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static struct mg_serve_http_opts opts;
static char *session_data = NULL;

typedef struct {
    char *email;
    char *ssn;
} UserInfo;

const char *info_response = 
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/plain\r\n"
"\r\n"
"Email: %s\nSSN: %s\n";

// Function to retrieve user info from session data
static void get_user_info(const struct mg_connection *conn, UserInfo *user) {
    if (session_data) {
        char *token = strtok(strdup(session_data), ";");
        while (token != NULL) {
            if (strncmp(token, "email=", 6) == 0) {
                user->email = strdup(token + 6);
            } else if (strncmp(token, "ssn=", 4) == 0) {
                user->ssn = strdup(token + 4);
            }
            token = strtok(NULL, ";");
        }
    }
}

// Function to handle /info route
static int ev_handler(struct mg_connection *conn, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        
        if (strcmp(hm->uri, "/info") == 0 && strcmp(hm->method, "GET") == 0) {
            UserInfo user_info = {NULL, NULL};
            get_user_info(conn, &user_info);

            char response[512];
            snprintf(response, sizeof(response), info_response, 
                     user_info.email ? user_info.email : "N/A", 
                     user_info.ssn ? user_info.ssn : "N/A");

            mg_serve_http(conn, (struct http_message *) hm, opts);
            
            if (user_info.email) free(user_info.email);
            if (user_info.ssn) free(user_info.ssn);

            return 1;
        }
    }

    // Default handler
    return 0;
}

int main(void) {
    const char *s_http_port = "8000";

    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    
    session_data = strdup("email=user@example.com;ssn=123-45-6789");

    // Start an HTTP server listening on port 8000
    struct mg_connection *nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    printf("Starting web server on port %s\n", s_http_port);

    // Set HTTP server options
    opts.document_root = "."; 
    opts.enable_directory_listing = "yes";
    
    // Event loop
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
}


Note: Ensure you have Mongoose library installed and linked during compilation. You can compile the program using:


gcc -o webapp main.c -lmongoose
./webapp