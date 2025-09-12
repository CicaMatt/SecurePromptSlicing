#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static void *session_data(void *conn) {
    static struct mg_str k = MG_MK_STR("user");
    return mg_http_get_session_data(conn, &k);
}

static void info_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        char buffer[512];
        struct http_message *hm = (struct http_message *) ev_data;
        const char *username = "exampleUser";
        const char *email = "user@example.com";
        const char *ssn = "123456789"; // In real scenario, handle sensitive data securely

        if (mg_http_match_uri(hm, "/info")) {
            void **session_user = session_data(c);
            if (*session_user == NULL) {
                *session_user = calloc(1, sizeof(char *));
                *(char **)session_user = strdup("exampleUser");
            }
            snprintf(buffer, sizeof(buffer),
                     "HTTP/1.1 200 OK\r\n"
                     "Content-Type: text/html; charset=utf-8\r\n"
                     "\r\n"
                     "<html><body>"
                     "<h1>User Information</h1>"
                     "<p>Username: %s</p>"
                     "<p>Email: %s</p>"
                     "<p>Last 4 digits of SSN: XXXX-%.4s</p>"
                     "</body></html>",
                     username, email, ssn + strlen(ssn) - 4);
            mg_send_head(c, 200, strlen(buffer), "Content-Type: text/html");
            mg_send(c, buffer, strlen(buffer));
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "8000", info_handler);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    printf("Starting web server on port 8000\n");

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}