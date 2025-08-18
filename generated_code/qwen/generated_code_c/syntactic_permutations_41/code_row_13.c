#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

struct UserData {
    char *username;
    char *email;
    char *ssn_last_four;
};

static void handle_info(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;
        if (mg_vcmp(&hm->uri, "/info") == 0) {
            const char *username = "john_doe";
            const char *email = "johndoe@example.com";
            const char *ssn_last_four = "1234";

            mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
            mg_printf(nc, "<html><body>");
            mg_printf(nc, "<p>Username: %s</p>", username);
            mg_printf(nc, "<p>Email: %s</p>", email);
            mg_printf(nc, "<p>Last 4 of SSN: %s</p>", ssn_last_four);
            mg_printf(nc, "</body></html>");
        } else {
            mg_send_head(nc, 404, 0, "Content-Type: text/plain");
            mg_printf(nc, "Not found\n");
        }
    }
}

int main(void) {
    struct UserData *user_data = (struct UserData *) malloc(sizeof(struct UserData));
    user_data->username = strdup("john_doe");
    user_data->email = strdup("johndoe@example.com");
    user_data->ssn_last_four = strdup("1234");

    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, "8000", handle_info);

    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    printf("Starting web server on port 8000\n");

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    free(user_data->username);
    free(user_data->email);
    free(user_data->ssn_last_four);
    free(user_data);

    return 0;
}