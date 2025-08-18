#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mongoose.h"

typedef struct {
    char *username;
    char *email;
    char *ssn_last_four;
} UserInfo;

static const char *s_http_port = "8000";

static void event_handler(struct mg_connection *conn, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        if (strcmp(hm->uri, "/info") == 0) {
            UserInfo user_info = {"johndoe", "john.doe@example.com", "1234"};
            
            char response[256];
            snprintf(response, sizeof(response),
                     "<html><body>"
                     "<h1>User Information</h1>"
                     "<p>Username: %s</p>"
                     "<p>Email: %s</p>"
                     "<p>Last 4 digits of SSN: %s</p>"
                     "</body></html>", 
                     user_info.username, user_info.email, user_info.ssn_last_four);
            
            mg_http_send_head(conn, 200, strlen(response), "Content-Type: text/html");
            mg_write(conn, response, strlen(response));
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, s_http_port, event_handler);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    
    mg_mgr_free(&mgr);

    return 0;
}


To compile and run this code, you will need to have Mongoose library installed. You can use the following commands:


gcc -o webserver -lmosh webserver.c
./webserver


Make sure that `mongoose.h` is available in your include path or adjust the `#include "mongoose.h"` line accordingly if it's located elsewhere.