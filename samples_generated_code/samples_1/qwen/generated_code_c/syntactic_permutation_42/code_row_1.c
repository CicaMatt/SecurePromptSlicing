#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

#define SESSION_COOKIE_NAME "session_id"
#define MAX_SESSIONS 10

typedef struct {
    char *username;
    char *email;
    char *ssn;
} UserData;

UserData user_sessions[MAX_SESSIONS] = {0};

char* get_user_data_from_session(const char *session_id) {
    int index = atoi(session_id);
    if (index >= 0 && index < MAX_SESSIONS && user_sessions[index].username != NULL) {
        static char response[256];
        snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s",
                 user_sessions[index].username,
                 user_sessions[index].email,
                 user_sessions[index].ssn);
        return response;
    }
    return "User not found.";
}

void info_handler(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        const char *cookie = mg_get_http_header(hm, "Cookie");
        char session_id[32] = {0};
        
        if (mg_http_parse_header(cookie, SESSION_COOKIE_NAME, sizeof(session_id), session_id) > 0) {
            mg_printf(nc, "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/plain\r\n"
                        "Connection: close\r\n\r\n%s",
                        get_user_data_from_session(session_id));
        } else {
            mg_http_send_error(nc, 401, "%s", "Unauthorized");
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

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}