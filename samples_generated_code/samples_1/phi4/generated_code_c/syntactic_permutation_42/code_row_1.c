#include <stdio.h>
#include <string.h>
#include "mongoose.h"

static struct mg_serve_http_opts http_server_opts;

typedef struct {
    char *username;
    char *email;
    char *ssn;
} UserSession;

void handle_request(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        
        // Extract session data
        const char *session_key = "session";
        UserSession user_session;
        memset(&user_session, 0, sizeof(UserSession));
        
        mg_get_header(session_key, hm->body.len, (const unsigned char **) &hm->body.p, &user_session.username);
        mg_get_header("email", hm->body.len, (const unsigned char **) &hm->body.p, &user_session.email);
        mg_get_header("ssn", hm->body.len, (const unsigned char **) &hm->body.p, &user_session.ssn);

        if (strcmp(hm->uri, "/info") == 0) {
            char response[256];
            snprintf(response, sizeof(response),
                     "Username: %s\nEmail: %s\nSSN: %s",
                     user_session.username ? user_session.username : "Not set",
                     user_session.email ? user_session.email : "Not set",
                     user_session.ssn ? user_session.ssn : "Not set");

            mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n"
                                "Connection: close\r\n"
                                "\r\n%s", response);
        } else {
            mg_send_head(nc, 404, 0, "text/plain");
            mg_printf(nc, "Not Found");
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "8080", handle_request);
    http_server_opts.document_root = "."; // Serve current directory
    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on port %d\n", 8080);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}


To run this code:

1. Install Mongoose: `https://github.com/cesanta/mongoose`
2. Compile with: `gcc -o webapp your_file.c -lmongoose`
3. Run the compiled program.
4. Access `http://localhost:8080/info` with appropriate session headers set for `username`, `email`, and `ssn`.