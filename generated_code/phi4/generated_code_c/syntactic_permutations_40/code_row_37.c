#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mongoose.h"

#define PORT "8000"
#define MAX_BUFFER_SIZE 4096

typedef struct {
    char *username;
    char *email;
    char *ssn_last_four;
} session_data;

static const char *s_http_port = PORT;
static mg_serve_http_opts s_http_server_opts;

session_data* get_session_data(mg_connection *conn) {
    static session_data session;
    if (session.username == NULL && session.email == NULL && session.ssn_last_four == NULL) {
        session.username = strdup("JohnDoe");
        session.email = strdup("john.doe@example.com");
        session.ssn_last_four = strdup("1234");
    }
    return &session;
}

static int handle_http_request(struct mg_connection *conn, enum mg_event ev) {
    if (ev == MG_EV_HTTP_REQUEST) {
        const struct mg_http_message *hm = mg_get_http_message(conn);

        if (mg_vcmp(&hm->uri, "/info") == 0 && hm->method_number == MGHTTP_METHOD_GET) {
            session_data* data = get_session_data(conn);
            
            char response[MAX_BUFFER_SIZE];
            snprintf(response, sizeof(response),
                     "<html><head><title>User Info</title></head>"
                     "<body><h1>UserInfo</h1>"
                     "<p>Username: %s</p>"
                     "<p>Email: %s</p>"
                     "<p>Last 4 digits of SSN: %s</p>"
                     "</body></html>", 
                     data->username, data->email, data->ssn_last_four);

            mg_printf(conn, "HTTP/1.1 200 OK\r\n"
                         "Content-Type: text/html\r\n"
                         "Connection: close\r\n"
                         "\r\n%s", response);
        } else {
            mg_serve_http(conn, hm, s_http_server_opts);
        }
    }

    return 0;
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);

    const char *address = (const char *)"http://0.0.0.0:";
    struct mg_connection *nc = mg_bind(&mgr, address, s_http_port,
                                       handle_http_request);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = "."; // Serve current directory
    s_http_server_opts.enable_directory_listing = "yes";

    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    return 0;
}


To compile and run this code, you will need the Mongoose library. You can typically install it via your package manager or download it from its website at https://github.com/cesanta/mongoose. Then link against the library when compiling:


gcc -o web_app main.c -lmongoose
./web_app


This code sets up a simple HTTP server that serves an HTML page with user information on visiting `/info`. It uses Mongoose, a lightweight web server and networking library in C, to handle HTTP requests. The session data is hardcoded for this example but would typically come from a real session management system.